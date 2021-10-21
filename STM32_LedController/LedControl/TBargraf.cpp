/*
 * TBargraf.cpp
 *
 *  Created on: 09.10.2021
 *      Author: Laptop
 */

#include "TBargraf.h"

//namespace std {


void TBargraf::fvBargrafEffect(uint16_t unNormValue)
{

	uint16_t unActivLedNumb = (static_cast<uint32_t>(unNormValue) * unLedTabLenght)/1000;

	if(unDelay)
	{unDelay--;}
	else
	{
		if(unMaxLedNumb)
		{unMaxLedNumb--;}
		unDelay = 1;
	}

	if(unActivLedNumb > unMaxLedNumb)
	{
		unMaxLedNumb = unActivLedNumb;
		unDelay = 2;
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

/*
	if(unMaxLedNumb > 60)
	{unMaxLedNumb = 0;}

	SetBrigtness(unMaxLedNumb,0);

	unMaxLedNumb++;
	unMaxLedNumb %= 60;

	SetBrigtness(unMaxLedNumb,10);
*/

}








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
