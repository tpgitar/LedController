/*
 * LedRgb.h
 *
 *  Created on: 12.10.2020
 *      Author: Laptop
 */

#include "stdio.h"

#ifndef LEDCONTROL_LEDRGB_H_
#define LEDCONTROL_LEDRGB_H_

const uint8_t CO_ucMinBrightness = 0;
const uint8_t CO_ucMaxBrightness = 100;

const uint8_t CO_ucMinSaturation = 0;
const uint8_t CO_ucMaxSaturation = 100;

const uint16_t CO_unMinHue = 0;
const uint16_t CO_unMaxHue = 360;



class TLedRgb
{
private:
public:

	void SetHue(uint16_t uInpHue);
	void SetSaturation(uint8_t ucInpSaturation);
	void SetBrighness(uint8_t ucInpBrightness);
	uint8_t GetBrighness();

	void DecreaseBrighness(uint8_t ucStep);
	void IncreaseBrighness(uint8_t ucStep);


	void Refresh(void);

	bool bEnable;
	uint16_t unTimer;
	uint16_t unHue;
	uint8_t ucSaturation;
	uint8_t ucBrightness;

	uint8_t ucRed;
	uint8_t ucGreen;
	uint8_t ucBlue;

};

#define CO_WS2812_NUMB_OF_LEDS 300
//----------------------------------------------------------------------------------------


#endif /* LEDCONTROL_LEDRGB_H_ */





