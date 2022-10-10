/*
 * AdcHardw.cpp
 *
 *  Created on: Oct 8, 2022
 *      Author: t_pro
 */

#include "stdio.h"
//#include "stm32l1xx_hal.h"
#include "main.h"
#include "string.h"
#include "dataAquisition.h"
//-------------------------------------------------------------------
extern ADC_HandleTypeDef hadc1;
dataAquisition DataAquisition{&hadc1};
//-------------------------------------------------------------------
extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	//TogglePinTest2();
	DataAquisition.SetSecondtBuf();
	DataAquisition.Stat.unCompleteDmaCnt++;
}

extern "C" void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{

	DataAquisition.SetFirstBuf();
	DataAquisition.Stat.unHalfDmaCnt++;
}


