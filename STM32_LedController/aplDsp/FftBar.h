/*
 * FftBar.h
 *
 *  Created on: 31 paź 2022
 *      Author: t_pro
 */

#ifndef FFTBAR_H_
#define FFTBAR_H_

#include "ProcessFft.h"


class LowPassFilter
{
private:
	uint32_t ulSum;
	//uint16_t unNumbOfElements;
	uint16_t unAverage;

public:
	//LowPassFilter(uint16_t unNumbOfElementsInp);
	uint16_t fnFilter(uint16_t unInpVal,uint16_t unNumbOfElements);

};





class FftBar
{
private:
	uint16_t unFreqMin;
	uint16_t unFreqMax;

	ProcessFft* pProcessFft;
	uint16_t unNormalizedVal;
	uint16_t unSlewRateRaise;
	uint16_t unSlewRateFall;
	float32_t fGain;


public:

	LowPassFilter lowPassFilter_InpSign;

	FftBar(ProcessFft* pProcessFftInp = NULL,uint16_t unFreqMinInp = 0,uint16_t unFreqMaxInp = 20000,float32_t fGainInp = 1.0):
		unFreqMin(unFreqMinInp),
		unFreqMax(unFreqMaxInp),
		pProcessFft(pProcessFftInp)
	{
		unSlewRateRaise = 70;
		unSlewRateFall = 35;
		fGain = fGainInp;

	};

	uint16_t fnGetNormalizedVal();

	virtual ~FftBar();
};

#endif /* FFTBAR_H_ */
