/*
 * ProcessFft.h
 *
 *  Created on: 11 paź 2022
 *      Author: t_pro
 */

#ifndef PROCESSFFT_H_
#define PROCESSFFT_H_

#include <arm_math.h>

const uint16_t CO_PROCESS_FFT_INP_BUF = (1024 * 2);

class ProcessFft
{

private:
	float32_t afInpDataBuf[CO_PROCESS_FFT_INP_BUF];
	float32_t afInpDataBufCopy[CO_PROCESS_FFT_INP_BUF];
	float32_t afOutDataBuf[CO_PROCESS_FFT_INP_BUF];
	uint16_t aunAbsLogModule[CO_PROCESS_FFT_INP_BUF/2];
	arm_rfft_fast_instance_f32 S;
	void ConvIntToFloat(uint16_t* pInp,uint16_t unDataLen);


	uint32_t aunSumCzesc[CO_PROCESS_FFT_INP_BUF/2];
	uint32_t aunAbsLogModuleAverage[CO_PROCESS_FFT_INP_BUF/2];



public:
	ProcessFft();
	void CalculateFft(uint16_t* punInpBuf, uint16_t unInpBufLen);
	int16_t fnGetValByIdx(uint16_t unIdx);
	uint16_t fnGetValByFreq(uint16_t unFreq);
	int16_t fnGetValByFreqRange(uint16_t unFreqMin, uint16_t unFreqMax);
	void fvSignalStatistics(uint16_t* punInpBuf, uint16_t unInpBufLen);
	uint16_t fnGetValByFreq_Average(uint16_t unFreq);


	struct
	{
		uint16_t unAdcMin;
		uint16_t unAdcMax;
		uint16_t unAdcAverage;

		uint16_t unFFTModMin;
		uint16_t unFFTModMax;
		uint16_t unFFTSkladStala;
		uint16_t FFTOverflowCnt;


		float32_t fFFTModMin;
		float32_t fFFTModMax;
		float32_t fFFTSkladStala;



	} Stat;


};



#endif /* PROCESSFFT_H_ */
