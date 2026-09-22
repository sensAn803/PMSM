/**
  ******************************************************************************
  * @file    motor_struct.h
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

#ifndef MOTOR_STRUCT_H
#define MOTOR_STRUCT_H

#include "stm32g4xx_hal.h"

#include "FOC_Model.h"

#define UART_BUFFER_SIZE 256
#define PI					3.14159265358979f

typedef enum
{
	STOP = 0x00U,
	START = 0x01U,
	FAULT = 0x03U,
}Motor_State_t;

typedef struct
{
	Motor_State_t State;
	int16_t SpdRef;
	float PosRef;
	float SpdKp;
	float SpdKi;
	float CurrKp;
	float CurrKi;
	uint8_t CtlMode;
}UART_Cmd_t;

typedef struct
{
	float Ia;
	float Ib;
	float Ic;
	float Iq_ref;
	float Iq;
	float Id;
	float VBus;
	float ElAngle;
	float Position;
	int16_t Speed;
	uint16_t IaOffset;
	uint16_t IbOffset;
	uint16_t IcOffset;
}FOCVars_t;

typedef struct
{
	uint8_t UartRxBuffer[UART_BUFFER_SIZE];
	uint8_t UartRxComplete;
	uint8_t DataDecodingState;
}UART_RxBuff_t;

typedef struct
{
	uint16_t Encoder_cnt;
	float Theta;
}Encoder_t;

typedef struct
{
	UART_Cmd_t UART_Cmd;
	FOCVars_t FOCVars;
	UART_RxBuff_t UART_RxBuff;
	Encoder_t Encoder;
}Motor_App_t;

typedef struct{
	uint16_t	sample_data;	
	uint16_t	angle;
	uint16_t	align_data;
	uint8_t		no_mag_flag;	
	uint8_t		pc_flag;			
}Encoder_SPI_t;

extern Motor_App_t m_app;
extern Encoder_SPI_t	Encoder_SPI;
void m_app_init(void);

 #endif /*MOTOR_STRUCT_H*/