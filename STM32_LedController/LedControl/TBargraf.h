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

public:

	TBargraf(const TLedRgb* pLedTabInp, uint16_t unLedTabLenghtInp): TLedRgbSection(pLedTabInp,unLedTabLenghtInp) {}
	TBargraf(const TLedRgb** ppLedTabInp, uint16_t unLedTabLenghtInp): TLedRgbSection(ppLedTabInp,unLedTabLenghtInp) {}

	void fvSetNomralizedTo1000(uint16_t unNormValue);


	void fvBargrafEffect();


};




//} /* namespace std */

#endif /* TBARGRAF_H_ */
