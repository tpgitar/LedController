/*
 * LedRgb.cpp
 *
 *  Created on: 09.10.2020
 *      Author: Laptop
 */
#include "stdio.h"

#include "./LedRgb.h"

//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------

void TLedRgb::SetHue(uint16_t uiInpHue)
{
	unHue = uiInpHue;

}
void TLedRgb::SetSaturation(uint8_t ucInpSaturation)
{
	ucSaturation = ucInpSaturation;
}

void TLedRgb::SetBrighness(uint8_t ucInpBrightness)
{
	ucBrightness = ucInpBrightness;
}
//--------------------------------------------------------------------------------------------------------
#include "string.h"
#include "math.h"

/*
    double fmod (double numer, double denom);
    fmod = numer - tquot * denom
*/

void TLedRgb::Refresh(void)
{//konwersja HSV  do RGB
	//259 200 10
//-----------------------

	if(bEnable == false)
	{
	    ucRed = 0;
	    ucGreen = 0;
	    ucBlue = 0;
	}
	else
	{


		float s = ((float)ucSaturation)/100;
		float v = ((float)ucBrightness)/100;
		float C = s*v;


//		float X = C*(1-abs(fmod(H/60.0, 2)-1));

/*		float zmFloat = static_cast<float>(unHue)/60.0;
		uint16_t ZmInt = zmFloat/2;
		float fReszta = zmFloat - (ZmInt*2);
		fReszta -= 1;

		if( fReszta < 0)
		{fReszta *= -1;}
*/
		float fReszta = abs(fmod(unHue/60.0, 2)-1);

		float X = C*(1-fReszta);

		float m = v-C;

		float r,g,b;

		if(unHue >= 0 && unHue < 60){
			r = C,g = X,b = 0;
		}
		else if(unHue >= 60 && unHue < 120){
			r = X,g = C,b = 0;
		}
		else if(unHue >= 120 && unHue < 180){
			r = 0,g = C,b = X;
		}
		else if(unHue >= 180 && unHue < 240){
			r = 0,g = X,b = C;
		}
		else if(unHue >= 240 && unHue < 300){
			r = X,g = 0,b = C;
		}
		else{
			r = C,g = 0,b = X;
		}




		ucRed = (r+m)*255;
		ucGreen = (g+m)*255;
		ucBlue = (b+m)*255;

/*
		ucRed = 50;
		ucGreen = 20;
		ucBlue = 20;
*/



	}
}
