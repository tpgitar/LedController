/*
 * ProcessFft.cpp
 *
 *  Created on: 11 paź 2022
 *      Author: t_pro
 */

#include "ProcessFft.h"
//--------------------------------------------------------------------------
ProcessFft::ProcessFft()
{
	// TODO Auto-generated constructor stub

    arm_rfft_fast_init_f32(&S,CO_PROCESS_FFT_INP_BUF);


}
//--------------------------------------------------------------------------
void ProcessFft::ConvIntToFloat(uint16_t* pInp,uint16_t unDataLen)
{
	if(unDataLen > CO_PROCESS_FFT_INP_BUF)
	{unDataLen = CO_PROCESS_FFT_INP_BUF;}

//	float* pfOut = &afInpDataBuf[0];


	for(uint16_t i = 0; i < unDataLen; i++)
	{
		afInpDataBuf[i] = pInp[i];
	}


}
//--------------------------------------------------------------------------
void ProcessFft::CalculateFft(uint16_t* punInpBuf, uint16_t unInpBufLen)
{

	if(unInpBufLen > CO_PROCESS_FFT_INP_BUF)
	{unInpBufLen = CO_PROCESS_FFT_INP_BUF;}

	ConvIntToFloat(punInpBuf,unInpBufLen);

	arm_rfft_fast_f32(&S, &afInpDataBuf[0], &afOutDataBuf[0], 0);

	uint16_t unIdx = 0;
	for(uint16_t i = 0; i < unInpBufLen; i = i + 2)
	{
		anAbsLogModule[unIdx] = (int) ( 20 * log10f(
													sqrtf(
															(afOutDataBuf[i] * afOutDataBuf[i])
															+ (afOutDataBuf[i + 1] * afOutDataBuf[i + 1])
														 )
									           )
								  );
		unIdx++;
	}


}

//--------------------------------------------------------------------------
