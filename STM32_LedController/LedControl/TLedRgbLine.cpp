/*
 * TLedRgbLine.cpp
 *
 *  Created on: 25.10.2021
 *      Author: Laptop
 */

#include "stdio.h"
#include "./TLedRgbLine.h"
#include "./Random.h"

extern TRandomGenerator RandomGen;

//---------------------------------------------------------------------------------------------------------------------------------------------------
void TLedRgbLine::fvMoveDown(uint16_t unStep, uint16_t unLedStart,uint16_t unLedStop)
{

	if(unLedStop >= unLedTabLenght)
	{unLedStop = unLedTabLenght - 1;}

	if(unLedStart >= unLedTabLenght)
	{unLedStart = unLedTabLenght - 1;}


	for(uint16_t unLedIdx = unLedStart; unLedIdx <= unLedStop; unLedIdx++)
	{
		uint16_t unBuf = unLedIdx + unStep;

		if(unBuf >= unLedStop + 1)
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
			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);

			//unSecDelay =   rand() %  (4 * CO_DISP_FREQ) ;

			unSecDelay = RandomGen.funGetRandomValue(60, 180);


			unTask = 2;
		}break;

		case 2:
		{

			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax); //TODO: dodac zmianna jasnosci
			unTask = 3;
		}break;

		case 3:
		{

			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);
			unTask = 4;
		}break;

		case 4:
		{

			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);
			unTask = 5;
		}break;


		case 5:
		{

			SetBrigtness(unLedTabLenght - 1, unBrightnessLimitMax);
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


void TLedRgbLine::fvSnowEffect(t_openargs openArg)
{

/*
	if(unMode != EN_LED_MODE_DROP)
	{
		unMode = EN_LED_MODE_DROP;
		unTask = 0;
		unDelay = 0;
	}
*/


	switch(openArg)
	{
		case CO_OPEN_ARG_RESTART:
		{
			SetBrigtness(0, unLedTabLenght - 1, 0); //wygas wszystkie
			unLevelDown = 0;
		}break;

		case CO_OPEN_ARG_PUT:
		{
			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);

		}break;

		case CO_OPEN_ARG_MOVE:
		{

			fvMoveDown(1, unLevelDown, unLedTabLenght - 1);
			while(getBrightness(unLevelDown) != 0)
			{
				unLevelDown++;
			}

/*
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
*/


		}break;

	}

}
