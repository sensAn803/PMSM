/**
  ******************************************************************************
  * @file    motor_struct.c
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

#include "Motor_Struct.h"

Motor_App_t m_app;
Encoder_SPI_t	Encoder_SPI;

void m_app_init(void)
{
  m_app.UART_Cmd.State = STOP;
  m_app.UART_Cmd.SpdRef = 0;
  m_app.UART_Cmd.PosRef = 0;

  m_app.UART_RxBuff.UartRxComplete = 0;
  m_app.UART_RxBuff.DataDecodingState = 0;
}
