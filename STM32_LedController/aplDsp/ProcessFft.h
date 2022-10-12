/*
 * ProcessFft.h
 *
 *  Created on: 11 paź 2022
 *      Author: t_pro
 */

#ifndef PROCESSFFT_H_
#define PROCESSFFT_H_

#include <arm_math.h>

const uint16_t CO_PROCESS_FFT_INP_BUF = 1024;

class ProcessFft
{

private:
	float32_t afInpDataBuf[CO_PROCESS_FFT_INP_BUF];
	float32_t afOutDataBuf[CO_PROCESS_FFT_INP_BUF];
	int16_t anAbsLogModule[CO_PROCESS_FFT_INP_BUF/2];
	arm_rfft_fast_instance_f32 S;
	void ConvIntToFloat(uint16_t* pInp,uint16_t unDataLen);


public:
	ProcessFft();
	void CalculateFft(uint16_t* punInpBuf, uint16_t unInpBufLen);



};

#endif /* PROCESSFFT_H_ */
