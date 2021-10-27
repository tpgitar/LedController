/*
 * LedSection.cpp
 *
 *  Created on: 23.04.2021
 *      Author: Laptop
 */

#include "LedSection.h"

//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::fvSetEnable(uint16_t unLedNo,bool bVal)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	pLed->bEnable = bVal;
}

void TLedRgbSection::fvEnable(uint16_t unLedNo)
{
	fvSetEnable(unLedNo,true);
}

void TLedRgbSection::fvEnable(uint16_t unLedStart,uint16_t unLedStop)
{

	if(unLedStop >= unLedTabLenght)
	{unLedStop = unLedTabLenght - 1;}

	for(uint16_t i = unLedStart; i <=  unLedStop; i++)
	{
		fvSetEnable(i,true);
	}
}


void TLedRgbSection::fvDisable(uint16_t unLedNo)
{
	fvSetEnable(unLedNo,false);
}


void TLedRgbSection::fvDisable(uint16_t unLedStart,uint16_t unLedStop)
{

	if(unLedStop >= unLedTabLenght)
	{unLedStop = unLedTabLenght - 1;}

	for(uint16_t i = unLedStart; i <=  unLedStop; i++)
	{
		fvSetEnable(i,false);
	}
}






void TLedRgbSection::fvToggle(uint16_t unLedNo)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	if(pLed->bEnable)
	{pLed->bEnable = false;}
	else
	{pLed->bEnable = true;}

}
//-----------------------------------------------------------------------------------------------------
TLedRgb* TLedRgbSection::GetLedPtr(uint16_t unLedNo)
{
	const TLedRgb* pLed;

	if(unLedNo >= unLedTabLenght)
	{return NULL;}


	if(ppLedTab != NULL)
	{pLed = ppLedTab[unLedNo];}
	else
	{pLed = (pLedTab + unLedNo);}

	return const_cast<TLedRgb*>(pLed);
}
//-----------------------------------------------------------------------------------------------------
TLedRgb* TLedRgbSection::getNextObjPtr()
{
	if(ppLedTab != NULL)
	{
		ppLedPtr++;
		return *ppLedPtr;
	}
	else
	{
		pLedPtr++;
		return pLedPtr;
	}
}
//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::incObjPtr()
{
	if(ppLedTab != NULL)
	{
		ppLedPtr++;
	}
	else
	{
		pLedPtr++;
	}
}
//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::decObjPtr()
{
	if(ppLedTab != NULL)
	{
		ppLedPtr--;
	}
	else
	{
		pLedPtr--;
	}
}
//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::setCurrentLedPtr(uint16_t unObjIdx)
{
	if(ppLedTab != NULL)
	{
		ppLedPtr = const_cast<TLedRgb**>(ppLedTab) + unObjIdx;
	}
	else
	{
		pLedPtr = const_cast<TLedRgb*>(pLedTab) + unObjIdx;
	}
}
//-----------------------------------------------------------------------------------------------------
TLedRgb* TLedRgbSection::getCurrentLedPtr()
{
	if(ppLedTab != NULL)
	{
		return *ppLedPtr;
	}
	else
	{
		return pLedPtr;
	}
}


//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::SetBrigtness(uint16_t unLedStart,uint16_t unLedStop, uint8_t ucBright)
{



	if(unLedStop >= unLedTabLenght)
	{unLedStop = unLedTabLenght - 1;}


	setCurrentLedPtr(unLedStart);


	for(uint16_t i = unLedStart; i <=  unLedStop; i++)
	{
		getCurrentLedPtr()->ucBrightness = ucBright;
		incObjPtr();
	}

}
//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::SetBrigtness(uint16_t unLedNo, uint8_t ucBright)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	if(ucBright < CO_ucMaxBrightness)
	{pLed->ucBrightness = ucBright;}
	else
	{pLed->ucBrightness = CO_ucMaxBrightness;}

	//pLed->Refresh();

}

void TLedRgbSection::IncreaseBrightness(uint16_t unLedNo, uint8_t ucBright)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	uint16_t unBuf = pLed->ucBrightness + ucBright;

	if(unBuf < CO_ucMaxBrightness)
	{pLed->ucBrightness = unBuf;}
	else
	{pLed->ucBrightness = CO_ucMaxBrightness;}
}

void TLedRgbSection::DecreaseBrightness(uint16_t unLedNo, uint8_t ucBright)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}


	if(ucBright < pLed->ucBrightness)
	{pLed->ucBrightness -= ucBright;}
	else
	{pLed->ucBrightness = 0;}

}

uint8_t TLedRgbSection::getBrightness(uint16_t unLedNo)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return 0;}

	return pLed->ucBrightness;
}
//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::SetHue(uint16_t unLedNo, uint16_t unInpHue)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	if(unInpHue < CO_unMaxHue)
	{pLed->unHue = unInpHue;}
	else
	{pLed->unHue = CO_unMaxHue;}

}

void TLedRgbSection::SetHue(uint16_t unLedStart,uint16_t unLedStop, uint16_t unHue)
{


	if(unLedStop >= unLedTabLenght)
	{unLedStop = unLedTabLenght - 1;}

	setCurrentLedPtr(unLedStart);

	for(uint16_t i = unLedStart; i <=  unLedStop; i++)
	{
		getCurrentLedPtr()->unHue = unHue;
		incObjPtr();
	}

}


void TLedRgbSection::IncreaseHue(uint16_t unLedNo, uint16_t unStep)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	uint16_t unBuf = pLed->unHue + unStep;

	if(unBuf < CO_unMaxHue)
	{pLed->unHue = unBuf;}
	else
	{pLed->unHue = CO_unMaxHue;}
}

void TLedRgbSection::DecreaseHue(uint16_t unLedNo, uint16_t unStep)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	if(unStep < pLed->unHue)
	{pLed->unHue -= unStep;}
	else
	{pLed->unHue = 0;}
}

uint8_t TLedRgbSection::getHue(uint16_t unLedNo)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return 0;}

	return pLed->unHue;
}
//-----------------------------------------------------------------------------------------------------

void TLedRgbSection::SetSaturation(uint16_t unLedNo, uint8_t ucSaturationInp)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	if(ucSaturationInp < CO_ucMaxSaturation)
	{pLed->ucSaturation = ucSaturationInp;}
	else
	{pLed->ucSaturation = CO_ucMaxSaturation;}

}


void TLedRgbSection::SetSaturation(uint16_t unLedStart,uint16_t unLedStop,uint8_t ucSaturation)
{


	if(unLedStop >= unLedTabLenght)
	{unLedStop = unLedTabLenght - 1;}

	setCurrentLedPtr(unLedStart);

	for(uint16_t i = unLedStart; i <=  unLedStop; i++)
	{
		getCurrentLedPtr()->ucSaturation = ucSaturation;
		incObjPtr();
	}

}



void TLedRgbSection::IncreaseSaturation(uint16_t unLedNo, uint8_t ucStep)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	uint16_t unBuf = pLed->ucSaturation + ucStep;

	if(unBuf < CO_ucMaxSaturation)
	{pLed->ucSaturation = unBuf;}
	else
	{pLed->ucSaturation = CO_ucMaxSaturation;}

}

void TLedRgbSection::DecreaseSaturation(uint16_t unLedNo, uint8_t ucStep)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return;}

	if(ucStep < pLed->ucSaturation)
	{pLed->ucSaturation -= ucStep;}
	else
	{pLed->ucSaturation = 0;}

}

uint8_t TLedRgbSection::getSaturation(uint16_t unLedNo)
{
	TLedRgb* pLed = GetLedPtr(unLedNo);

	if(pLed == NULL)
	{return 0;}

	return pLed->ucSaturation;
}

//-----------------------------------------------------------------------------------------------------
void TLedRgbSection::Refresh(void)
{
	if(ppLedTab != NULL)
	{
		TLedRgb** ppLedTabBuf = const_cast<TLedRgb**>(ppLedTab);

		for(uint16_t i = 0; i < unLedTabLenght; i++)
		{
			(*ppLedTabBuf)->Refresh();
			ppLedTabBuf++;
		}

	}
	else
	{
		if(pLedTab != NULL)
		{
			TLedRgb* pLedTabBuf = const_cast<TLedRgb*>(pLedTab);
			for(uint16_t i = 0; i < unLedTabLenght; i++)
			{
				pLedTabBuf->Refresh();
				pLedTabBuf++;
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------




