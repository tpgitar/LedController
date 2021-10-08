/*
 * LedSection.h
 *
 *  Created on: 23.04.2021
 *      Author: Laptop
 */

#ifndef LEDCONTROL_LEDSECTION_H_
#define LEDCONTROL_LEDSECTION_H_

#include "./LedRgb.h"




class TLedRgbSection
{
 private:

	const TLedRgb* pLedTab;
	const TLedRgb** ppLedTab;

protected:
	const  uint16_t unLedTabLenght;




 public:
 	TLedRgbSection(const TLedRgb* pLedTabInp, uint16_t unLedTabLenghtInp): pLedTab(pLedTabInp), ppLedTab(NULL), unLedTabLenght(unLedTabLenghtInp)  {};
 	TLedRgbSection(const TLedRgb** ppLedTabInp, uint16_t unLedTabLenghtInp): pLedTab(NULL), ppLedTab(ppLedTabInp), unLedTabLenght(unLedTabLenghtInp) {};


 	TLedRgb* GetLedPtr(uint16_t unLedNo);
 	TLedRgb* getNextObjPtr();

 	void incObjPtr();
 	void decObjPtr();
 	void setCurrentLedPtr(uint16_t unObjIdx);
 	TLedRgb* getCurrentLedPtr();

 	void SetBrigtness(uint16_t unLedNo, uint8_t ucBright);
 	void SetBrigtness(uint16_t unLedStart,uint16_t unLedStop, uint8_t ucBright);

 	void IncreaseBrightness(uint16_t unLedNo, uint8_t ucBright);
 	void DecreaseBrightness(uint16_t unLedNo, uint8_t ucBright);
 	uint8_t getBrightness(uint16_t unLedNo);

 	void DecreaseHue(uint16_t unLedNo, uint16_t unStep);
 	uint8_t getHue(uint16_t unLedNo);
 	void IncreaseHue(uint16_t unLedNo, uint16_t unStep);
 	void SetHue(uint16_t unLedNo, uint16_t unInpHue);
 	void SetHue(uint16_t unLedStart,uint16_t unLedStop, uint16_t unHue);

 	uint8_t getSaturation(uint16_t unLedNo);
 	void DecreaseSaturation(uint16_t unLedNo, uint8_t ucStep);
 	void IncreaseSaturation(uint16_t unLedNo, uint8_t ucStep);
 	void SetSaturation(uint16_t unLedNo, uint8_t ucSaturationInp);
 	void SetSaturation(uint16_t unLedStart,uint16_t unLedStop,uint8_t ucSaturation);

 	void fvSetEnable(uint16_t unLedNo,bool bVal);
 	void fvEnable(uint16_t unLedNo);
 	void fvEnable(uint16_t unLedStart,uint16_t unLedStop);

 	void fvDisable(uint16_t unLedNo);
 	void fvDisable(uint16_t unLedStart,uint16_t unLedStop);
 	void fvToggle(uint16_t unLedNo);

 	void Refresh(void);





     TLedRgb*  pLedPtr;
     TLedRgb** ppLedPtr;


};







#endif /* LEDCONTROL_LEDSECTION_H_ */
