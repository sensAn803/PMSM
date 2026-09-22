/**
  ******************************************************************************
  * @file    motor_board_func.c
  * @author  Motor Control Team, Euler[https://space.bilibili.com/458115745?spm_id_from=333.337.0.0]
  * @brief   Motor Control can communicarion functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) [2024] [Euler].
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Euler.
  *
  ******************************************************************************
  */

#include "Motor_Task_func.h"
#include "adc.h"
#include "tim.h"
#include "opamp.h"
#include "dac.h"
#include "comp.h"
#include "math.h"
#include "Motor_Encoder.h"

void Motor_StartTSK(void);
void Motor_StopTSK(void);
void LED_MediumFreqToggle(void);
void LED_HighFreqToggle(void);
float Get_Vbus(void);

void FOC_MediumFrequencyTask(void)
{
	static uint8_t MotorState = 0;
	Motor_Load_UART_Tx_Buff();
	Motor_UART_Rx_Data_Decoding();
	if(MotorState != m_app.UART_Cmd.State)
	{
		if(m_app.UART_Cmd.State == START)
		{
			Motor_StartTSK();
		}
		else
		{
			Motor_StopTSK();
		}
	}
	MotorState = m_app.UART_Cmd.State;
	if(__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_BREAK))
	{
		m_app.UART_Cmd.State = FAULT;
		__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_BREAK);
	}
	m_app.FOCVars.VBus = Get_Vbus();
	rtU.v_bus = m_app.FOCVars.VBus;
	rtU.PosRef = m_app.UART_Cmd.PosRef;
	LED_MediumFreqToggle();
	LED_HighFreqToggle();
}

void FOC_HighFrequencyTask(void)
{
  static uint8_t cnt;
  static uint8_t OffsetCalibration = 0;
  static uint16_t IaU16, IbU16, IcU16;
	static float Encoder_ThetaLast;
  if (OffsetCalibration == 0)
  {
    cnt++;
    m_app.FOCVars.IaOffset += hadc1.Instance->JDR1;
    m_app.FOCVars.IbOffset += hadc2.Instance->JDR1;
    m_app.FOCVars.IcOffset += hadc1.Instance->JDR2;
    if (cnt >= 10)
    {
      OffsetCalibration = 1;
      m_app.FOCVars.IaOffset = m_app.FOCVars.IaOffset / 10;
      m_app.FOCVars.IbOffset = m_app.FOCVars.IbOffset / 10;
      m_app.FOCVars.IcOffset = m_app.FOCVars.IcOffset / 10;
    }
  }
  else
  {
    IaU16 = hadc1.Instance->JDR1;
    IbU16 = hadc2.Instance->JDR1;
    IcU16 = hadc1.Instance->JDR2;
    m_app.FOCVars.Ia = (IaU16 - m_app.FOCVars.IaOffset) * 0.02197265625f;
    m_app.FOCVars.Ib = (IbU16 - m_app.FOCVars.IbOffset) * 0.02197265625f;
    m_app.FOCVars.Ic = (IcU16 - m_app.FOCVars.IcOffset) * 0.02197265625f;
		m_app.FOCVars.ElAngle = 4 * Get_Encoder_Angle();
		rtU.Encoder_Theta = fmod(m_app.FOCVars.ElAngle, 2.0f*PI);
		rtU.ia = m_app.FOCVars.Ia;
		rtU.ib = m_app.FOCVars.Ib;
		rtU.ic = m_app.FOCVars.Ic;
		FOC_Model_step();
		if(Motor_state == 2)
		{
			Encoder_SPI.align_data = Encoder_SPI.angle;
		}
		if(Motor_state >= 3)
		{
			if(rtU.Encoder_Theta - Encoder_ThetaLast <-6.0f)
			{
				m_app.Encoder.NumTurns++;
			}
			else if(rtU.Encoder_Theta - Encoder_ThetaLast >6.0f)
			{
				m_app.Encoder.NumTurns--;
			}
		}
		rtU.Encoder_Cnt = m_app.Encoder.NumTurns;
		TIM1->CCR1 = rtY.tABC[0];
    TIM1->CCR2 = rtY.tABC[1];
    TIM1->CCR3 = rtY.tABC[2];
		TIM1->CCR5 = rtY.tABC[2];
		Encoder_ThetaLast = rtU.Encoder_Theta;
  }
}
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  if (hadc == &hadc1)
  {
    FOC_HighFrequencyTask();
  }
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADCEx_InjectedConvCpltCallback must be implemented in the user file.
  */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  if (Button3_Pin == GPIO_Pin)				
  {
    m_app.UART_Cmd.State = ~m_app.UART_Cmd.State & START;
  }
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  UNUSED(Size);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)&m_app.UART_RxBuff, 14);
	m_app.UART_RxBuff.DataDecodingState = 1;
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UARTEx_RxEventCallback can be implemented in the user file.
   */
}

void Motor_StopTSK(void)
{
	rtU.Motor_OnOff = 0;
	memset(&rtDW,0,sizeof(rtDW));
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
}

void Motor_StartTSK(void)
{
	rtU.Motor_OnOff = 1;
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
}

void BSP_Init(void)
{
	HAL_OPAMP_Start(&hopamp1);
	HAL_OPAMP_Start(&hopamp2);
	HAL_OPAMP_Start(&hopamp3);
	HAL_ADCEx_Calibration_Start( &hadc1, ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start( &hadc2, ADC_SINGLE_ENDED);
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_JEOC);
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_EOC);
	__HAL_ADC_CLEAR_FLAG( &hadc2, ADC_FLAG_JEOC);
	HAL_ADCEx_InjectedStart_IT(&hadc1);
	HAL_ADCEx_InjectedStart(&hadc2);
	HAL_TIM_Base_Start( &htim1);
	HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_4);
	__HAL_UART_CLEAR_FLAG(&huart3, UART_CLEAR_IDLEF);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)&m_app.UART_RxBuff, 14);
	HAL_DAC_SetValue(&hdac3, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2958);
	HAL_DAC_Start(&hdac3,DAC_CHANNEL_1);
	HAL_COMP_Start(&hcomp1);
	HAL_TIM_Base_Start( &htim4);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}
void LED_MediumFreqToggle(void)
{
	static uint16_t LED_Cnt = 0;
	LED_Cnt++;
	if(LED_Cnt >= 500)
	{
		LED_Cnt = 0;
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	}
}

void LED_HighFreqToggle(void)
{
	static uint16_t LED_Cnt = 0;
	if(m_app.UART_Cmd.State == START)
	{
		LED_Cnt++;
		if(LED_Cnt >= 250)
		{
			LED_Cnt = 0;
			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		}
	}
	else if(m_app.UART_Cmd.State == FAULT)
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	}
}

float Get_Vbus(void)
{
	uint16_t VBusU16 = 0;
	float VBus = 0;
	HAL_ADC_Start(&hadc2);
	VBusU16 = HAL_ADC_GetValue(&hadc2);
	VBus = VBusU16*3.3f/4096*26;
	return VBus;
}
