/*
 * TLedRgbLine.h
 *
 *  Created on: 25.10.2021
 *      Author: Laptop
 */

#ifndef TLEDRGBLINE_H_
#define TLEDRGBLINE_H_

#include "./LedSection.h"

enum {EN_LED_MODE_ZERO,EN_LED_MODE_DROP,EN_LED_MODE_END};


enum t_openargs {CO_OPEN_ARG_RESTART,CO_OPEN_ARG_PUT,CO_OPEN_ARG_MOVE};

class TLedRgbLine : public TLedRgbSection
{
private:

public:
	TLedRgbLine(const TLedRgb* pLedTabInp, uint16_t unLedTabLenghtInp, uint16_t unBrightnessLimitMaxInp = 100 ): TLedRgbSection(pLedTabInp,unLedTabLenghtInp,unBrightnessLimitMaxInp) {}
	TLedRgbLine(const TLedRgb** ppLedTabInp, uint16_t unLedTabLenghtInp, uint16_t unBrightnessLimitMaxInp = 100 ): TLedRgbSection(ppLedTabInp,unLedTabLenghtInp,unBrightnessLimitMaxInp) {}


	void fvMoveDown(uint16_t unStep, uint16_t unLedStart = 0 ,uint16_t unLedStop = 0xffff);
	void fvMoveDownV2(uint16_t unStep, uint16_t unLedStart = 0,uint16_t unLedStop = 0xffff,bool bMoveHue = true,
				           bool bMoveBrightness = true, bool bCyclic = false);

	void fvDropEffect();

	void fvSnowEffect(t_openargs openArg, uint16_t unColor = 0);
	//void fvColorPattern1(uint16_t unStartVal = 0,uint16_t unStopVal = 360, uint16_t unFactor = 1);



	uint16_t unTask;
	uint16_t unMode;
	uint16_t unDelay;
	uint16_t unSecDelay;
	uint16_t unColor;
	uint16_t unLevelDown;
};




#endif /* TLEDRGBLINE_H_ */
