#include "Motor_Encoder.h"
#include "Motor_Struct.h"
#include "stdio.h"

uint8_t errcode = 0;
void REIN_Encoder_SPI_Signal_Init(void)
{
	Encoder_SPI.sample_data = 0;
	Encoder_SPI.angle = 0;
}

void RINE_Encoder_SPI_Get_AngleData(void)
{
	uint16_t data_t[2];
	uint16_t data_r[2];
	uint8_t h_count;
	data_t[0] = (0x80 | 0x03) << 8;
	data_t[1] = (0x80 | 0x04) << 8;
	for(uint8_t i=0; i<3; i++){
		MT6816_SPI_CS_L();
		errcode = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&data_t[0], (uint8_t*)&data_r[0], 1, HAL_MAX_DELAY);
		MT6816_SPI_CS_H();
		MT6816_SPI_CS_L();
		errcode = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&data_t[1], (uint8_t*)&data_r[1], 1, HAL_MAX_DELAY);
		MT6816_SPI_CS_H();
		Encoder_SPI.sample_data = ((data_r[0] & 0x00FF) << 8) | (data_r[1] & 0x00FF);
		h_count = 0;
		for(uint8_t j=0; j<16; j++){
			if(Encoder_SPI.sample_data & (0x0001 << j))
				h_count++;
		}
		if(h_count & 0x01){
			Encoder_SPI.pc_flag = 0x00;
		}
		else{
			Encoder_SPI.pc_flag = 0x01;
			break;
		}
	}
	if(Encoder_SPI.pc_flag){
		Encoder_SPI.angle = Encoder_SPI.sample_data >> 2;
		Encoder_SPI.no_mag_flag = (uint8_t)(Encoder_SPI.sample_data & (0x0001 << 1));
	}
}

float Get_Encoder_Angle(void)
{
	float Encoder_Angle;
	RINE_Encoder_SPI_Get_AngleData();
	Encoder_Angle = 2 * PI * (Encoder_SPI.angle - Encoder_SPI.align_data) / 16384;
	if(Encoder_Angle < 0)
	{
		Encoder_Angle += 2 * PI;
	}
	else if(Encoder_Angle >= 2 * PI)
	{
		Encoder_Angle -= 2 * PI;
	}
	return Encoder_Angle;
}
