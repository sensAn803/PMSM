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

#define FOC_MODEL_TPWM_S        (5.0e-5f)
#define FOC_VBUS_MIN_VALID_V    (18.0f)
#define FOC_VBUS_MAX_VALID_V    (28.0f)

void Motor_StartTSK(void);
void Motor_StopTSK(void);
void LED_MediumFreqToggle(void);
void LED_HighFreqToggle(void);
float Get_Vbus(void);

static uint8_t FOC_VbusIsValid(float vbus);
static uint32_t FOC_TcmToCcr(real32_T tcm);
static uint8_t FOC_UpdatePwmCompare(void);
static void FOC_ResetAll(void);
static void Motor_PwmDisable(void);
static void Motor_PwmEnable(void);

static uint8_t FOC_VbusIsValid(float vbus)
{
	return (uint8_t)((vbus >= FOC_VBUS_MIN_VALID_V) &&
	                 (vbus <= FOC_VBUS_MAX_VALID_V));
}

/*
 * The model compares carrier >= Tcm, while TIM1 CH1..CH3 use PWM mode 1.
 * Therefore the equivalent active-high duty is 1 - Tcm/(Tpwm/2).
 */
static uint32_t FOC_TcmToCcr(real32_T tcm)
{
	real32_T carrier_peak = FOC_MODEL_TPWM_S * 0.5f;
	real32_T duty;

	if (tcm <= 0.0f)
	{
		return TIM1->ARR;
	}
	if (tcm >= carrier_peak)
	{
		return 0U;
	}

	duty = 1.0f - tcm / carrier_peak;
	return (uint32_t)(duty * (real32_T)TIM1->ARR + 0.5f);
}

static uint8_t FOC_UpdatePwmCompare(void)
{
	uint32_t ccr1;
	uint32_t ccr2;
	uint32_t ccr3;
	real32_T tcm1 = (real32_T)rtY.Tcm1;
	real32_T tcm2 = (real32_T)rtY.Tcm2;
	real32_T tcm3 = (real32_T)rtY.Tcm3;

	/* These comparisons also reject NaN and infinity. */
	if (!((tcm1 >= -FOC_MODEL_TPWM_S) &&
	      (tcm1 <=  FOC_MODEL_TPWM_S) &&
	      (tcm2 >= -FOC_MODEL_TPWM_S) &&
	      (tcm2 <=  FOC_MODEL_TPWM_S) &&
	      (tcm3 >= -FOC_MODEL_TPWM_S) &&
	      (tcm3 <=  FOC_MODEL_TPWM_S)))
	{
		return 0U;
	}

	ccr1 = FOC_TcmToCcr(tcm1);
	ccr2 = FOC_TcmToCcr(tcm2);
	ccr3 = FOC_TcmToCcr(tcm3);

	TIM1->CCR1 = ccr1;
	TIM1->CCR2 = ccr2;
	TIM1->CCR3 = ccr3;
	/* TIM1 OC5 is used as the COMP1 blanking source. */
	TIM1->CCR5 = ccr3;
	return 1U;
}

static void FOC_ResetAll(void)
{
	uint32_t primask = __get_PRIMASK();

	__disable_irq();
	memset(&rtDW, 0, sizeof(rtDW));
	memset(&rtU, 0, sizeof(rtU));
	memset(&rtY, 0, sizeof(rtY));
	rtM->Timing.TaskCounters.TID[0] = 0U;
	rtM->Timing.TaskCounters.TID[1] = 0U;
	FOC_Model_initialize();
	rtU.Tpwm = FOC_MODEL_TPWM_S;
	rtU.Reset = 1.0f;
	if (primask == 0U)
	{
		__enable_irq();
	}
}

static void Motor_PwmDisable(void)
{
	/* Disable all advanced-timer outputs immediately, then stop the channels. */
	__HAL_TIM_MOE_DISABLE(&htim1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
}

static void Motor_PwmEnable(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
}

void FOC_MediumFrequencyTask(void)
{
	static uint8_t MotorState = 0;
	Motor_Load_UART_Tx_Buff();
	Motor_UART_Rx_Data_Decoding();
	if(__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_BREAK))
	{
		m_app.UART_Cmd.State = FAULT;
		__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_BREAK);
	}
	m_app.FOCVars.VBus = Get_Vbus();
	rtU.v_bus = m_app.FOCVars.VBus;
	rtU.speedref = m_app.UART_Cmd.SpdRef;
	if ((m_app.UART_Cmd.State == START) &&
	    (FOC_VbusIsValid(m_app.FOCVars.VBus) == 0U))
	{
		m_app.UART_Cmd.State = FAULT;
	}
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
	LED_MediumFreqToggle();
	LED_HighFreqToggle();
}

void FOC_HighFrequencyTask(void)
{
  static uint8_t cnt;
  static uint8_t OffsetCalibration = 0;
  static uint16_t IaU16, IbU16, IcU16;
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
		rtU.ia = m_app.FOCVars.Ia;
		rtU.ib = m_app.FOCVars.Ib;
		rtU.ic = m_app.FOCVars.Ic;
		rtU.v_bus = m_app.FOCVars.VBus;
		rtU.speedref = m_app.UART_Cmd.SpdRef;
		if (FOC_VbusIsValid(rtU.v_bus) == 0U)
		{
			if (m_app.UART_Cmd.State == START)
			{
				__HAL_TIM_MOE_DISABLE(&htim1);
				rtU.ControlEnable = 0.0f;
				rtU.Reset = 1.0f;
				rtU.FaultActive = 1.0f;
				m_app.UART_Cmd.State = FAULT;
			}
			return;
		}

		rtU.FaultActive = (m_app.UART_Cmd.State == FAULT) ? 1.0f : 0.0f;
		FOC_Model_step();
//		if(Motor_state == 2)
//		{
//			Encoder_SPI.align_data = Encoder_SPI.angle;
//		}
		if ((rtU.ControlEnable > 0.5f) &&
		    (m_app.UART_Cmd.State == START) &&
		    (FOC_UpdatePwmCompare() == 0U))
		{
			__HAL_TIM_MOE_DISABLE(&htim1);
			rtU.ControlEnable = 0.0f;
			rtU.Reset = 1.0f;
			rtU.FaultActive = 1.0f;
			m_app.UART_Cmd.State = FAULT;
		}
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
	uint8_t fault_active = (m_app.UART_Cmd.State == FAULT) ? 1U : 0U;

	rtU.ControlEnable = 0.0f;
	rtU.Reset = 1.0f;
	rtU.FaultActive = (real32_T)fault_active;
	Motor_PwmDisable();
	FOC_ResetAll();
	rtU.v_bus = m_app.FOCVars.VBus;
	rtU.speedref = m_app.UART_Cmd.SpdRef;
	rtU.FaultActive = (real32_T)fault_active;
}

void Motor_StartTSK(void)
{
	Motor_PwmDisable();
	FOC_ResetAll();

	if (FOC_VbusIsValid(m_app.FOCVars.VBus) == 0U)
	{
		rtU.FaultActive = 1.0f;
		m_app.UART_Cmd.State = FAULT;
		return;
	}

	rtU.v_bus = m_app.FOCVars.VBus;
	rtU.speedref = m_app.UART_Cmd.SpdRef;
	rtU.FaultActive = 0.0f;
	rtU.Reset = 0.0f;
	rtU.ControlEnable = 1.0f;
	TIM1->CCR1 = TIM1->ARR / 2U;
	TIM1->CCR2 = TIM1->ARR / 2U;
	TIM1->CCR3 = TIM1->ARR / 2U;
	TIM1->CCR5 = TIM1->ARR / 2U;
	Motor_PwmEnable();
}

void BSP_Init(void)
{
	FOC_ResetAll();
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
	rtU.speedref = 0.0f;
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
