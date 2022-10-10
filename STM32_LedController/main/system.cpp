
#include "main.h"
#include "stdlib.h"
#include "usb_device.h"

#include "../LedControl/LedRgb.h"
#include "../aplDsp/dataAquisition.h"

extern class TLedRgb Led[];

extern  void fvRunDmaTransfer();



//---------------------------------------------------------------------------------------------------------------------------
extern "C" uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
extern void ObsWS2812_100ms_2();
extern void ObsWS2812_100ms_3();
extern void ObsWS2812_100ms_4();

extern void fvMainLed20ms();

const char sBuf[] = "Test3\r\n";
//---------------------------------------------------------------------------------------------------------------------------
class Tsystem
{
private:
	bool bFlag1ms;
	bool bFlag10ms;
	bool bFlag20ms;
	bool bFlag100ms;
	bool bFlag1s;
	uint16_t unCnt;


public:

	void fvScheduler();
	void fvSetFlags1ms();

};
//---------------------------------------------------------------------------------------------------------------------------
void  Tsystem::fvSetFlags1ms()
{
	bFlag1ms = true;

	if( (unCnt % 10 == 1))
	{bFlag10ms = true;}


	if( (unCnt % 20 == 2))
	{bFlag20ms = true;}



	if( (unCnt % 100 == 3))
	{bFlag100ms = true;}

	if( (unCnt % 1000 == 4))
	{bFlag1s = true;}

	unCnt++;
	if(unCnt >= 1000)
	{unCnt = 0;}

}
//-----------------------------------------------
char sBufUsb[1024];
uint16_t unIdx = 0;

extern void fvTEst();
extern void TastADC(void);


extern dataAquisition DataAquisition;

void Tsystem::fvScheduler()
{
	if(bFlag1ms)
	{
		bFlag1ms = false;
		HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
	}


	if(bFlag10ms)
	{
		bFlag10ms = false;
		HAL_GPIO_TogglePin(GPIOD, LD4_Pin);


		//------------------
		unIdx++;

		if(unIdx >= 180)
		{unIdx = 0;}

		sprintf((char*)sBufUsb,"%d. %d %d %d\r\n",unIdx,Led[unIdx].ucRed,Led[unIdx].ucGreen,Led[unIdx].ucBlue) ;
		CDC_Transmit_FS((uint8_t*) sBufUsb,strlen(sBufUsb));
		//------------------

		uint16_t unDataLen;
		DataAquisition.fpGetBufferRead(&unDataLen);
		//zwalnianie bufora !!

	}


	if(bFlag20ms)
	{
		bFlag20ms = false;

		fvMainLed20ms();
		fvRunDmaTransfer();

		fvTEst();

	}



	if(bFlag100ms)
	{

		bFlag100ms = false;
		//TastADC();


/*
		HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
		ObsWS2812_100ms_3();
*/




	}


	if(bFlag1s)
	{
		bFlag1s = false;
		HAL_GPIO_TogglePin(GPIOD, LD6_Pin);


	}

}

class Tsystem System;

//---------------------------------------------------------------------------------------------------------------------------
extern "C" void fvSysSetFlags(void) // tu jest extern "C", bo funkcja jest wywo�ywana z przerwania, ktore jest w pliku C
{
	System.fvSetFlags1ms();
}


void fvSysScheduler(void)//tu nie ma extern "C", bo funkcja jest wywolywana w main.c, ktore jest includowane w main.cpp, wiec kompilowane jest jako c++
{
	System.fvScheduler();
}
//---------------------------------------------------------------------------------------------------------------------------


