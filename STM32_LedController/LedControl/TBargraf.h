/*
 * TBargraf.h
 *
 *  Created on: 09.10.2021
 *      Author: Laptop
 */

#ifndef TBARGRAF_H_
#define TBARGRAF_H_

#include "stdio.h"
#include "./LedRgb.h"
#include "./LedSection.h"



//namespace std {

class TBargraf : public TLedRgbSection
{

private:
	uint16_t unNormalizedValue;
	uint16_t unBackgroundHue;
	uint8_t unBackgroundBrightness;

	uint16_t unMaxLedNumb;
	uint16_t unDelay;

public:

	TBargraf(const TLedRgb* pLedTabInp, uint16_t unLedTabLenghtInp, uint16_t unBrightnessLimitMaxInp = 100 ): TLedRgbSection(pLedTabInp,unLedTabLenghtInp,unBrightnessLimitMaxInp) {}
	TBargraf(const TLedRgb** ppLedTabInp, uint16_t unLedTabLenghtInp, uint16_t unBrightnessLimitMaxInp = 100 ): TLedRgbSection(ppLedTabInp,unLedTabLenghtInp,unBrightnessLimitMaxInp) {}

	void fvSetNomralizedTo1000(uint16_t unNormValue);


	void fvBargrafEffect(uint16_t unNormValue);


};




//} /* namespace std */

#endif /* TBARGRAF_H_ */
