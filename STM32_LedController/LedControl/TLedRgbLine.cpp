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
			SetHue(unLedIdx,0);
		}
		else
		{
			SetBrigtness(unLedIdx,getBrightness(unBuf));
			SetHue(unLedIdx,getHue(unBuf));
		}

	}
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void TLedRgbLine::fvMoveDownV2(uint16_t unStep, uint16_t unLedStart,uint16_t unLedStop,bool bMoveHue, bool bMoveBrightness,  bool bCyclic)
{

	if(unLedStop >= unLedTabLenght)
	{unLedStop = unLedTabLenght - 1;}

	if(unLedStart >= unLedTabLenght)
	{unLedStart = unLedTabLenght - 1;}


	for(uint16_t unStepIdx = 0;unStepIdx < unStep; unStepIdx++)
	{
		uint16_t unBufZeroBright = 0;
		uint16_t unBufZeroHue = 0;

		if(bCyclic)
		{
			unBufZeroBright = getBrightness(unLedStart);
			unBufZeroHue = getHue(unLedStart);
		}

		for(uint16_t unLedIdx = unLedStart; unLedIdx < unLedStop; unLedIdx++)
		{
			if(bMoveBrightness)
			{SetBrigtness(unLedIdx,getBrightness(unLedIdx + 1));}
			if(bMoveHue)
			{SetHue(unLedIdx,getHue(unLedIdx + 1));}
		}

		if(bMoveBrightness)
		{SetBrigtness(unLedStop,unBufZeroBright);}
		if(bMoveHue)
		{SetHue(unLedStop,unBufZeroHue);}
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

			SetBrightness(0, unLedTabLenght - 1, 0); //wygas wszystkie
			unTask = 1;

		}break;

		case 1:
		{
			unColor = RandomGen.funGetRandomColor();
			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);
			SetHue(unLedTabLenght - 1,unColor);

			unSecDelay = RandomGen.funGetRandomValue(50, 170);


			unTask = 2;
		}break;

		case 2:
		{

			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);
			SetHue(unLedTabLenght - 1,unColor);
			unTask = 3;
		}break;

		case 3:
		{

			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);
			SetHue(unLedTabLenght - 1,unColor);
			unTask = 4;
		}break;

		case 4:
		{

			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);
			SetHue(unLedTabLenght - 1,unColor);
			unTask = 5;
		}break;


		case 5:
		{

			SetBrigtness(unLedTabLenght - 1, unBrightnessLimitMax);
			SetHue(unLedTabLenght - 1,unColor);
			unTask = 6;
		}break;

		default:
		{
			unTask++;
			if(unTask > unSecDelay)
			{unTask = 1;}
		}break;



	}

}


void TLedRgbLine::fvSnowEffect(t_openargs openArg, uint16_t unColor)
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
			SetBrightness(0, unLedTabLenght - 1, 0); //wygas wszystkie
			unLevelDown = 0;
		}break;

		case CO_OPEN_ARG_PUT:
		{
			SetBrigtness(unLedTabLenght - 1,unBrightnessLimitMax);
			SetHue(unLedTabLenght - 1, unColor );

		}break;

		case CO_OPEN_ARG_MOVE:
		{


			if(unLevelDown < unLedTabLenght - 1)
			{

				fvMoveDown(1, unLevelDown, unLedTabLenght - 1);
				while(getBrightness(unLevelDown) != 0)
				{
					unLevelDown++;
				}


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


void TLedRgbSection::fvColorPattern1(uint16_t unStartVal, uint16_t unStopVal, uint16_t unFactor)
{
/*
	uint16_t unStartVal = 80;
	uint16_t unStopVal = 360;
	uint16_t unFactor = 2;
*/
	setCurrentLedPtr(0);

	for(uint16_t unLedIx = 0; unLedIx < unLedTabLenght;unLedIx++)
	{

		uint16_t unHue =  (unStartVal + ( (unStopVal - unStartVal)/unLedTabLenght ) * unLedIx * unFactor) % 360;
		getCurrentLedPtr()->unHue = unHue;
		incObjPtr();
	}

}
