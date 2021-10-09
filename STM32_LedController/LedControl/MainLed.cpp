#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "./LedRgb.h"
#include "./LedSection.h"
#include "./TBargraf.h"

//-----------------------------------------------------------------------------------------------------------------------------
#define CO_NUMB_OF_LED_LINES 5
#define CO_NUMB_LEDS_IN_LINE 60
#define CO_DISP_FREQ 50 //20ms

class TLedRgb Led[CO_WS2812_NUMB_OF_LEDS];




//-----------------------------------------------------------------------------------------------------------------------------

enum {EN_LED_MODE_ZERO,EN_LED_MODE_DROP};

class TLedRgbLine : public TLedRgbSection
{
private:

public:
	TLedRgbLine(const TLedRgb* pLedTabInp, uint16_t unLedTabLenghtInp): TLedRgbSection(pLedTabInp,unLedTabLenghtInp) {}
	TLedRgbLine(const TLedRgb** ppLedTabInp, uint16_t unLedTabLenghtInp): TLedRgbSection(ppLedTabInp,unLedTabLenghtInp) {}


	void fvMoveDown(uint16_t unStep);

	void fvDropEffect();

	uint16_t unTask;
	uint16_t unMode;
	uint16_t unDelay;
	uint16_t unSecDelay;
};



class TLedRgbLine LedLine[CO_NUMB_OF_LED_LINES] = {
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 0], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 1], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 2], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 3], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 4], CO_NUMB_LEDS_IN_LINE),
};


class TBargraf Bargraf[CO_NUMB_OF_LED_LINES] = {

	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 0], CO_NUMB_LEDS_IN_LINE),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 1], CO_NUMB_LEDS_IN_LINE),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 2], CO_NUMB_LEDS_IN_LINE),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 3], CO_NUMB_LEDS_IN_LINE),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 4], CO_NUMB_LEDS_IN_LINE),

};

//---------------------------------------------------------------------------------------------------------------------------------------------------
void TLedRgbLine::fvMoveDown(uint16_t unStep)
{

	for(uint16_t unLedIdx = 0; unLedIdx < unLedTabLenght; unLedIdx++)
	{
		uint16_t unBuf = unLedIdx + unStep;

		if(unBuf >= unLedTabLenght)
		{
			SetBrigtness(unLedIdx,0);
		}
		else
		{
			SetBrigtness(unLedIdx,getBrightness(unBuf));
		}

	}
}




//---------------------------------------------------------------------------------------------------------------------------------------------------
void TLedRgbLine::fvDropEffect()
{


	if(unMode != EN_LED_MODE_DROP)
	{
		unMode = EN_LED_MODE_DROP;
		unTask = 0;
		unDelay = 0;
	}


	if(unDelay)
	{
		unDelay--;
		return;
	}
	else
	{
		fvMoveDown(1);
		unDelay = 0;

	}


	switch(unTask)
	{
		case 0:
		{

			SetBrigtness(0, unLedTabLenght - 1, 0); //wygas wszystkie
			unTask = 1;

		}break;

		case 1:
		{
			SetBrigtness(unLedTabLenght - 1,10);

			unSecDelay =   rand() %  (4 * CO_DISP_FREQ) ;

			unTask = 2;
		}break;

		case 2:
		{

			SetBrigtness(unLedTabLenght - 1,10);
			unTask = 3;
		}break;

		case 3:
		{

			SetBrigtness(unLedTabLenght - 1,10);
			unTask = 4;
		}break;

		case 4:
		{

			SetBrigtness(unLedTabLenght - 1,10);
			unTask = 5;
		}break;


		case 5:
		{

			SetBrigtness(unLedTabLenght - 1,1 *3);
			unTask = 6;
		}break;

		default:
		{
			unTask++;
			if(unTask > unSecDelay)
			{unTask = 1;}
		}break;

		//rand

	}

}



//---------------------------------------------------------------------------------------------------------------------------------------------------
#define CO_PI (3.141692f)
void fvMainLed20ms()
{
	static uint16_t unTask = 0;




	switch(unTask)
	{

		case 0:
		{

			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].fvEnable(0,CO_NUMB_LEDS_IN_LINE);
				LedLine[unLineIdx].SetSaturation(0,CO_NUMB_LEDS_IN_LINE,100);

				LedLine[unLineIdx].SetBrigtness(0,CO_NUMB_LEDS_IN_LINE,5);

				LedLine[unLineIdx].SetHue(0,CO_NUMB_LEDS_IN_LINE,/*300*/ 75 * unLineIdx);
			}

			unTask = 2;

			srand(0x1234);

		}break;

		case 1:
		{

			LedLine[0].fvDropEffect();
			LedLine[1].fvDropEffect();
			LedLine[2].fvDropEffect();
			LedLine[3].fvDropEffect();
			LedLine[4].fvDropEffect();
		}break;

		case 2:
		{
			static uint16_t unPom = 0;
			static float fRadius = 0;

			unPom++;
			if(unPom > 1000)
			{unPom = 0;}

			fRadius += CO_PI/100;





			int16_t nSin =  static_cast<int16_t>( fabs(sin(fRadius)) * 1000 );
			Bargraf[0].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (1* CO_PI/6) ) ) * 1000 );
			Bargraf[1].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (2* CO_PI/6) ) ) * 1000 );
			Bargraf[2].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>(fabs(sin(fRadius + (3* CO_PI/6) ) ) * 1000 );
			Bargraf[3].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (4* CO_PI/6) ) ) * 1000 );
			Bargraf[4].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>(fabs(sin(fRadius + (5* CO_PI/6) ) ) * 1000 ) ;
			Bargraf[5].fvSetNomralizedTo1000(nSin);






/*

			int16_t nSin = static_cast<int16_t>(sin(fRadius) * 500) + 500;
			Bargraf[0].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>(sin(fRadius + CO_PI/6) * 500) + 500;
			Bargraf[1].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>(sin(fRadius + (2* CO_PI/6)) * 500) + 500;
			Bargraf[2].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>(sin(fRadius + (3* CO_PI/6)) * 500) + 500;
			Bargraf[3].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>(sin(fRadius + (4* CO_PI/6)) * 500) + 500;
			Bargraf[4].fvSetNomralizedTo1000(nSin);
*/


		}break;


	}

	LedLine[0].Refresh();
}








//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
void fvMainLed20ms_1()
{
	static uint16_t unTask = 0;
	static uint16_t unLedNo = 0;


	switch(unTask)
	{

		case 0:
		{
			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{

				for (uint16_t unLedIdx = 0; unLedIdx < CO_NUMB_LEDS_IN_LINE; unLedIdx++)
				{
					LedLine[unLineIdx].SetHue(unLedIdx,unLineIdx * 20);
					LedLine[unLineIdx].SetSaturation(unLedIdx,100);
					LedLine[unLineIdx].fvEnable(unLedIdx);
				}
				LedLine[unLineIdx].Refresh();



			}

			unTask = 1;

		}break;

		case 1:
		{

		for(uint16_t j = 0; j < 4; j++)
		{
			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].SetBrigtness(unLedNo,5);
				LedLine[unLineIdx].Refresh();
			}

			unLedNo++;
			if(unLedNo >= CO_NUMB_LEDS_IN_LINE)
			{
				unLedNo = 0;
				unTask = 2;
				break;
			}
		}

		}break;


		case 2:
		{
			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].SetBrigtness(unLedNo,0);
				LedLine[unLineIdx].Refresh();
			}

			unLedNo++;
			if(unLedNo >= CO_NUMB_LEDS_IN_LINE)
			{
				unLedNo = 0;
				unTask = 1;
			}
		}break;

	}



}


