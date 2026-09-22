/**
  ******************************************************************************
  * @file    motor_board_func.h
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

#ifndef MOTOR_BOARD_FUNC_H
#define MOTOR_BOARD_FUNC_H

#include "Motor_Comm_func.h"

void FOC_HighFrequencyTask(void);
void FOC_MediumFrequencyTask(void);
void BSP_Init(void);
#endif /*MOTOR_BOARD_FUNC_H*/