#ifndef __MOTOR_Encoder_H
#define __MOTOR_Encoder_H
//#include <stdbool.h>	
//#include <string.h>		
//#include <stdlib.h>		
#include <stdio.h>		
#include <spi.h>		
#include <main.h>		

#define MT6816_SPI_CS_H()	     HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,1) 
#define MT6816_SPI_CS_L()		 	 HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,0) 	


void REIN_MT6816_SPI_Signal_Init(void);		
void RINE_MT6816_SPI_Get_AngleData(void);	
					
float Get_Encoder_Angle(void);

#endif /*__MOTOR_Encoder_H*/
