/*
 * FftBar.cpp
 *
 *  Created on: 31 paź 2022
 *      Author: t_pro
 */

#include "FftBar.h"


//LowPassFilter::LowPassFilter(uint16_t unNumbOfElementsInp) : unNumbOfElements(unNumbOfElementsInp) {}

uint16_t LowPassFilter::fnFilter(uint16_t unInpVal,uint16_t unNumbOfElements)
{
	ulSum += unInpVal;
	ulSum -= unAverage;
	unAverage = ulSum/unNumbOfElements;

	return unAverage;
}




/*
FftBar::FftBar()
{
	// TODO Auto-generated constructor stub

}
*/

FftBar::~FftBar()
{
	// TODO Auto-generated destructor stub
}



uint16_t FftBar::fnGetNormalizedVal()
{

	uint16_t unRet = 0;

	float fBuf = pProcessFft->ffGetMaxValByFreqRange_Lin(unFreqMin, unFreqMax);


#define  CO_MAX_VAL_FFT (1500000)
#define CO_IL_ELM_SR (3)
#define CO_NORMA_MAX 1000

/*
	 fBuf =  log10f( (afInpDataBufCopy[unIdx]/CO_MAX_VAL_FFT) * 150 ) + 0.4;
	 fBuf *= 500;
*/

	fBuf =  log10f( (fBuf/CO_MAX_VAL_FFT) * 150 ) + 0.4;
	fBuf *= 550 * fGain;

	if(fBuf > 0)
	{unRet = (uint16_t) fBuf;}
	else
	{unRet = 0;}

	if(unRet > CO_NORMA_MAX)
	{unRet = CO_NORMA_MAX;}


	unRet = lowPassFilter_InpSign.fnFilter(unRet,4);


	if( (unSlewRateRaise == 0) && (unSlewRateFall == 0) )
	{
		this->unNormalizedVal = unRet;
	}
	else
	{
		if(unRet > this->unNormalizedVal + unSlewRateRaise)
		{this->unNormalizedVal += unSlewRateRaise;}
		else
		{
			if(unRet + unSlewRateFall < this->unNormalizedVal)
			{this->unNormalizedVal -= unSlewRateFall;}
			else
			{this->unNormalizedVal = unRet;}
		}


	}



	return this->unNormalizedVal;
}



