/*
 * TBargraf.cpp
 *
 *  Created on: 09.10.2021
 *      Author: Laptop
 */

#include "TBargraf.h"
#include "colors.h"

//namespace std {

//--------------------------------------------------------------------------------------------------------------
void TBargraf::fvBargrafEffect(uint16_t unNormValue)
{

	uint16_t unActivLedNumb = (static_cast<uint32_t>(unNormValue) * unLedTabLenght)/1000;


	if(unDelay)
	{unDelay--;}
	else
	{
		if(unMaxLedNumb)
		{
			unMaxLedNumb--;

		}
		unDelay = unCfgDelay;
	}


	if(unActivLedNumb > unMaxLedNumb)
	{

		unMaxLedNumb = unActivLedNumb;



		unDelay = unCfgPreDelay;
	}


	for(uint16_t i = 0; i <  unLedTabLenght; i++)
	{

		if((i <= unActivLedNumb))
		{
			SetBrigtness(i,10);
		}
		else
		{
			SetBrigtness(i,0);
		}
	}
	SetBrigtness(unMaxLedNumb,10);
	//SetHue(unMaxLedNumb,CO_COLOR_140_BLUE_BRIGHT);
}
//-----------------------------------------------------------------------------------------------------
void TBargraf::fvBargrafEffect1(uint16_t unNormValue)
{

	uint16_t unActivLedNumb = (static_cast<uint32_t>(unNormValue) * unLedTabLenght)/1000;


	fvColorPattern1(80,360,3);
	/*for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
	{
		LedLine[unLineIdx].fvColorPattern1(80,360,3);
	}
*/

	if(unDelay)
	{unDelay--;}
	else
	{
		if(unMaxLedNumb)
		{
			unMaxLedNumb--;

		}
		unDelay = unCfgDelay;
	}


	if(unActivLedNumb > unMaxLedNumb)
	{

		unMaxLedNumb = unActivLedNumb;



		unDelay = unCfgPreDelay;
	}


	for(uint16_t i = 0; i <  unLedTabLenght; i++)
	{

		if((i <= unActivLedNumb))
		{
			SetBrigtness(i,10);
		}
		else
		{
			SetBrigtness(i,0);
		}
	}

	SetBrigtness(unMaxLedNumb,10);
	SetHue(unMaxLedNumb,CO_COLOR_140_BLUE_BRIGHT);
}



//-----------------------------------------------------------------------------------------------------







void TBargraf::fvSetNomralizedTo1000(uint16_t unNormValue)
{
	uint16_t unActivLedNumb = (static_cast<uint32_t>(unNormValue) * unLedTabLenght)/1000;


	for(uint16_t i = 0; i <  unLedTabLenght; i++)
	{

		if(i <= unActivLedNumb)
		{
			SetBrigtness(i,10);
		}
		else
		{
			SetBrigtness(i,0);
		}

	}



}

//} /* namespace std */
