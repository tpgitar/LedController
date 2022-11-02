/*
 * FftBar.h
 *
 *  Created on: 31 paź 2022
 *      Author: t_pro
 */

#ifndef FFTBAR_H_
#define FFTBAR_H_

#include "ProcessFft.h"


class FftBar
{
private:
	uint16_t unFreqMin;
	uint16_t unFreqMax;

	ProcessFft* pProcessFft;
	uint16_t unNormalizedVal;
	uint16_t unSlewRateRaise;
	uint16_t unSlewRateFall;


public:
	FftBar(ProcessFft* pProcessFftInp = NULL,uint16_t unFreqMinInp = 0,uint16_t unFreqMaxInp = 20000):
		unFreqMin(unFreqMinInp),
		unFreqMax(unFreqMaxInp),
		pProcessFft(pProcessFftInp)
	{
		unSlewRateRaise = 70;
		unSlewRateFall = 70;

	};

	uint16_t fnGetNormalizedVal();

	virtual ~FftBar();
};

#endif /* FFTBAR_H_ */
