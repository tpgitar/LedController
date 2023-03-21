/*
 * WS2812_hardw.cpp
 *
 *  Created on: 09.10.2020
 *      Author: Laptop
 */

#include "stdio.h"
//#include "stm32l1xx_hal.h"
#include "main.h"
#include "./LedRgb.h"

//----------------------------------------------------------------------------------
extern class TLedRgb Led[];
extern  SPI_HandleTypeDef hspi1;
//----------------------------------------------------------------------------------
#define CO_WS2118_SPI_L 0xc0 //1100 0000
#define CO_WS2118_SPI_H 0xf8 //1111 1000



#define CO_WS2812_DMA_BUF_LEN (48)
uint8_t aunWS2812DmaBuf[CO_WS2812_DMA_BUF_LEN];


//-----------------------------------------------------------------------------------
const uint32_t ulTable[16] = {


		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//0
		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24),	//1
		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//2
		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24),	//3
		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//4
		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24),	//5
		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//6
		( ((uint32_t) CO_WS2118_SPI_L) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24),	//7
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//8
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24),	//0
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//10
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_L) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24),	//11
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//12
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_L) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24),	//13
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_L) << 24),	//14
		( ((uint32_t) CO_WS2118_SPI_H) <<  0) | ( ((uint32_t) CO_WS2118_SPI_H) <<  8) | ( ((uint32_t) CO_WS2118_SPI_H) << 16) |  ( ((uint32_t) CO_WS2118_SPI_H) << 24)	//15
};
//----------------------------------------------------------------------------

inline void TranferInterrupt(uint8_t* pOutData);
void TranferInterrupt(uint8_t* pOutData)
{
	static uint16_t unLedIdx = 0;



	class TLedRgb* pLed;


	uint32_t unBufIdx;
	uint8_t ucBuf;
	uint32_t* pOutData32;


	if(unLedIdx >= CO_WS2812_NUMB_OF_LEDS + 1)
	{

		HAL_SPI_DMAStop(&hspi1);
		for(unBufIdx = 0; unBufIdx < CO_WS2812_DMA_BUF_LEN/2; unBufIdx++)
		{
			*pOutData++ = 0;
		}
		unLedIdx = 0;
	}
	else
	{

		if(unLedIdx >= CO_WS2812_NUMB_OF_LEDS)
		{
			for(unBufIdx = 0; unBufIdx < CO_WS2812_DMA_BUF_LEN/2; unBufIdx++)
			{
				*pOutData++ = 0;
			}
		}
		else
		{
			pOutData32 = (uint32_t*) pOutData;
			pLed = &Led[unLedIdx];


			ucBuf = (pLed->ucGreen >> 4);
			*pOutData32++ = ulTable[ucBuf];

			ucBuf = (pLed->ucGreen & 0x0f);
			*pOutData32++ = ulTable[ucBuf];
			//----

			ucBuf = (pLed->ucRed >> 4);
			*pOutData32++ = ulTable[ucBuf];

			ucBuf = (pLed->ucRed & 0x0f);
			*pOutData32++ = ulTable[ucBuf];
			//---

			ucBuf = (pLed->ucBlue >> 4);
			*pOutData32++ = ulTable[ucBuf];

			ucBuf = (pLed->ucBlue & 0x0f);
			*pOutData32++ = ulTable[ucBuf];
		}
		unLedIdx++;
	}

}


//---------------------------------------------------------------------------------------------
extern "C" void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	//TogglePinTest2();
	TranferInterrupt(&aunWS2812DmaBuf[0]);

}

extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	//TogglePinTest1();
	TranferInterrupt(&aunWS2812DmaBuf[24]);

}

void fvRunDmaTransfer()
{

	HAL_SPI_Transmit_DMA(&hspi1,&aunWS2812DmaBuf[0],CO_WS2812_DMA_BUF_LEN);
}

//---------------------------------------------------------------------------------------------
void ObsWS2812_100ms_1()
{

	static uint8_t ucStart = 0;
	static uint16_t unTime = 0;


		if (ucStart == 0)
		{

			for(uint16_t i = 0; i < CO_WS2812_NUMB_OF_LEDS;i++)
			{
				Led[i].ucBrightness = 20;
				Led[i].ucSaturation = 100;

				Led[i].unHue = i * (360/CO_WS2812_NUMB_OF_LEDS);
			}

			ucStart = 1;
		}


		unTime++;
		if(unTime % 50 == 0)
		{


			uint16_t unHueBuf = Led[0].unHue;

			for(uint16_t i = 0; i < CO_WS2812_NUMB_OF_LEDS - 1;i++)
			{
				Led[i].unHue =  Led[i+1].unHue;
			}

			Led[CO_WS2812_NUMB_OF_LEDS - 1].unHue = unHueBuf;


			for(uint16_t i = 0; i < CO_WS2812_NUMB_OF_LEDS;i++)
			{

				Led[i].Refresh();
			}

		}




}


void ObsWS2812_100ms_2()
{
	static uint16_t unHue = 0;
	static uint8_t ucStart = 0;
	static uint16_t unTime = 0;

	static uint16_t unTemp = 0;


	if (ucStart == 0)
	{

		for(uint16_t i = 0; i < CO_WS2812_NUMB_OF_LEDS;i++)
		{
			Led[i].bEnable = true;
			Led[i].ucBrightness = 20;
			Led[i].ucSaturation = 100;
		}

		ucStart = 1;
	}




	unTime++;
	if(unTime % 1 == 0)
	{
		unHue++;
		if(unHue > 360)
		{unHue = 0;}
	}


	if(unTime % 5 == 0)
	{
		unTemp++;
		if(unTemp >= CO_WS2812_NUMB_OF_LEDS)
		{unTemp = 0;}
	}



	for(uint16_t i = 0; i < CO_WS2812_NUMB_OF_LEDS;i++)
	{

		if(unTemp == i)
		{Led[i].unHue = 0;}
		else
		{Led[i].unHue = unHue;}

		Led[i].Refresh();
	}


	HAL_SPI_Transmit_DMA(&hspi1,&aunWS2812DmaBuf[0],CO_WS2812_DMA_BUF_LEN);
}



void ObsWS2812_100ms_3()
{
	static uint16_t unHue = 0;
	static uint8_t ucStart = 0;
	static uint16_t unTime = 0;

	static uint16_t unTemp = 0;
	static uint16_t idx = 50;

	unTime++;
	if(unTime % 5 == 0)
	{
		unTemp++;
		if(unTemp >= CO_WS2812_NUMB_OF_LEDS)
		{unTemp = 0;}
	}




	for(uint16_t i = 0; i < 180;i++)
	{
		Led[idx].bEnable = true;
		Led[idx].ucBrightness = 10;
		Led[idx].ucSaturation = 100;
		Led[idx].unHue = i * 2;
		Led[idx].Refresh();

		idx++;
		if(idx >= 180)
		{idx = 0;}
	}

/*
	for(uint16_t i = 180; i < 300;i++)
	{
		Led[i].bEnable = true;
		Led[i].ucBrightness = 30;
		Led[i].ucSaturation = 100;
		Led[i].unHue = (i * 2) % 180;
		Led[i].Refresh();
	}


	Led[unTemp].ucBrightness = 80;
	Led[unTemp].unHue = 0;
	Led[unTemp].Refresh();
*/




	HAL_SPI_Transmit_DMA(&hspi1,&aunWS2812DmaBuf[0],CO_WS2812_DMA_BUF_LEN);
}


void ObsWS2812_100ms_4()
{
	static uint16_t unHue = 0;
	static uint8_t ucStart = 0;
	static uint16_t unTime = 0;

	static uint16_t unTemp = 0;




	if (ucStart == 0)
	{

		for(uint16_t i = 0; i < 180;i++)
		{
			Led[i].bEnable = true;
			Led[i].ucBrightness = 30;
			Led[i].ucSaturation = 100;
			Led[i].unHue = i * 2;
			Led[i].Refresh();
		}

		for(uint16_t i = 180; i < 300;i++)
		{
			Led[i].bEnable = true;
			Led[i].ucBrightness = 30;
			Led[i].ucSaturation = 100;
			Led[i].unHue = (i * 2) % 180;
			Led[i].Refresh();
		}

		ucStart = 1;

	}








	unTime++;
	if(unTime % 5 == 0)
	{
		unTemp++;


		Led[299].unHue = Led[0].unHue;
		Led[299].Refresh();

		for(uint16_t i = 0; i < 300 - 1;i++)
		{


			Led[i].unHue = Led[i + 1].unHue;
			Led[i].Refresh();


			if(i & 0x01)
			{
				if(unTemp & 0x01)
				{Led[i].bEnable = true;}
				else
				{Led[i].bEnable = false;}

			}
			else
			{
				if(unTemp & 0x01)
				{Led[i].bEnable = false;}
				else
				{Led[i].bEnable = true;}
			}
			Led[i].Refresh();

		}

	}








	HAL_SPI_Transmit_DMA(&hspi1,&aunWS2812DmaBuf[0],CO_WS2812_DMA_BUF_LEN);
}



/*

extern "C" void ApiC_WS2812Hardw_100ms()
{

	HAL_SPI_Transmit_DMA(&hspi1,&aunWS2812DmaBuf[0],CO_WS2812_DMA_BUF_LEN);

}
*/



uint16_t WS2812_Enable = 0;
extern "C" void Enable_WS2812(void)
{


	WS2812_Enable = 1;
}






