/*
 * dataAquisition.h
 *
 *  Created on: 10 paź 2022
 *      Author: t_pro
 */

#ifndef DATAAQUISITION_H_
#define DATAAQUISITION_H_

const uint16_t CO_FFT_NUMB_OF_SAMPLE = (1024 * 2);
const uint16_t CO_FFT_BUF_LEN  (2 * CO_FFT_NUMB_OF_SAMPLE);


class dataAquisition
{
private:

	uint16_t aunAdcDmaBuf[CO_FFT_BUF_LEN];
	ADC_HandleTypeDef* pHadc;

	bool firstBufFull;
	bool secondBufFull;



public:

	dataAquisition(ADC_HandleTypeDef* pHadcInp) : pHadc(pHadcInp) {}
	void fvStartAquisition()
	//void dataAquisition::fvStartAquisition()
	{
		HAL_ADC_Start_DMA(pHadc,(uint32_t*) &aunAdcDmaBuf[0],CO_FFT_BUF_LEN);
	}

	void SetFirstBuf()
	{
		firstBufFull = true;
		secondBufFull = false;
	}
	void SetSecondtBuf()
	{
		firstBufFull = false;
		secondBufFull = true;
	}

	uint16_t* fpGetBufferRead(uint16_t* punDalaLen)
	{
		if(firstBufFull)
		{
			*punDalaLen = CO_FFT_BUF_LEN/2;
			return &aunAdcDmaBuf[0];
		}
		else
		{
			if(secondBufFull)
			{
				*punDalaLen = CO_FFT_BUF_LEN/2;
				return &aunAdcDmaBuf[CO_FFT_BUF_LEN/2];
			}
			else
			{
				return NULL;
			}
		}

	}

	void fvReleaseBuf(uint16_t* pInpDataBuf)
	{
		if(pInpDataBuf == &aunAdcDmaBuf[0])
		{
			firstBufFull = false;
		}

		if(pInpDataBuf == &aunAdcDmaBuf[CO_FFT_BUF_LEN/2])
		{
			secondBufFull = false;
		}
	}



	struct
	{
		uint16_t unHalfDmaCnt;
		uint16_t unCompleteDmaCnt;



	} Stat;

};




#endif /* DATAAQUISITION_H_ */
