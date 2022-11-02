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
	Stat.unAdcMax = 0x00;
	Stat.unAdcMin = 0xffff;

	Stat.unFFTModMin = 0xffff;
	Stat.unFFTModMax = 0;


	Stat.fFFTModMin = MAXFLOAT;
	Stat.unFFTModMax = -1 *  MAXFLOAT;


}
//--------------------------------------------------------------------------
void ProcessFft::ConvIntToFloat(uint16_t* pInp,uint16_t unDataLen)
{
	if(unDataLen > CO_PROCESS_FFT_INP_BUF)
	{unDataLen = CO_PROCESS_FFT_INP_BUF;}

	for(uint16_t i = 0; i < unDataLen; i++)
	{
		afInpDataBuf[i] = pInp[i];
	}


}
//--------------------------------------------------------------------------

void ProcessFft::fvSignalStatistics(uint16_t* punInpBuf, uint16_t unInpBufLen)
{

	uint32_t ulSum = 0;



	for(uint16_t i = 0; i < unInpBufLen;i++)
	{
		ulSum += punInpBuf[i];

		if(punInpBuf[i] < Stat.unAdcMin)
		{Stat.unAdcMin = punInpBuf[i];}

		if(punInpBuf[i] > Stat.unAdcMax)
		{Stat.unAdcMax = punInpBuf[i];}


	}
	Stat.unAdcAverage =  ulSum/unInpBufLen;





}


void ProcessFft::CalculateFft(uint16_t* punInpBuf, uint16_t unInpBufLen)
{


	fvSignalStatistics(punInpBuf,unInpBufLen);

	if(unInpBufLen > CO_PROCESS_FFT_INP_BUF)
	{unInpBufLen = CO_PROCESS_FFT_INP_BUF;}

	ConvIntToFloat(punInpBuf,unInpBufLen);

	arm_rfft_fast_f32(&S, &afInpDataBuf[0], &afOutDataBuf[0], 0);

	uint16_t unIdx = 0;
	for(uint16_t i = 0; i < unInpBufLen; i = i + 2)
	{


		if(unIdx >= unInpBufLen/2)
		{break;}




		float32_t fBuf =  ( sqrtf(  (afOutDataBuf[i] * afOutDataBuf[i])
												+ (afOutDataBuf[i + 1] * afOutDataBuf[i + 1])
											 )
									  );

/*
		if(fBuf > 25000)
		{afInpDataBufCopy[unIdx] = fBuf - 25000;}
		else
		{afInpDataBufCopy[unIdx] = 0;}
*/

		afInpDataBufCopy[unIdx] = fBuf;

		//--------------
/*
		afInpDataBufCopy[unIdx] /= 10000;


		if(afInpDataBufCopy[unIdx] != 0)
		{aunAbsLogModule[unIdx] = (uint16_t) ( 700 * (log10f(afInpDataBufCopy[unIdx])) );}
		else
		{aunAbsLogModule[unIdx] = 0;}


		if(aunAbsLogModule[unIdx] > 1000)
		{aunAbsLogModule[unIdx] = 1000;}
*/

		//--------------
#define  CO_MAX_VAL_FFT (1500000)
#define CO_IL_ELM_SR (3)

		 fBuf =  log10f( (afInpDataBufCopy[unIdx]/CO_MAX_VAL_FFT) * 150 ) + 0.4;
		 fBuf *= 500;


		 if(fBuf > 0)
		 {aunAbsLogModule[unIdx] = (uint16_t) fBuf;}
		 else
		 {aunAbsLogModule[unIdx] = 0;}




		if(aunAbsLogModule[4] > 10000)
		{
			Stat.FFTOverflowCnt++;
		}


		if(unIdx > 10)
		{//zeby nie liczyl skladowej stalej
			if(Stat.unFFTModMin > aunAbsLogModule[unIdx])
			{Stat.unFFTModMin = aunAbsLogModule[unIdx];}

			if(Stat.unFFTModMax < aunAbsLogModule[unIdx])
			{Stat.unFFTModMax = aunAbsLogModule[unIdx];}


			if(Stat.fFFTModMin > afInpDataBufCopy[unIdx])
			{Stat.fFFTModMin = afInpDataBufCopy[unIdx];}

			if(Stat.fFFTModMax < afInpDataBufCopy[unIdx])
			{Stat.fFFTModMax = afInpDataBufCopy[unIdx];}



		}

		//-----------------------------------
		aunSumCzesc[unIdx] += aunAbsLogModule[unIdx];
		aunSumCzesc[unIdx] -= aunAbsLogModuleAverage[unIdx];
		aunAbsLogModuleAverage[unIdx] = aunSumCzesc[unIdx]/CO_IL_ELM_SR;
		//-----------------------------------


		unIdx++;
	}
	Stat.unFFTSkladStala = aunAbsLogModule[0];






}


/*
LOG:


anAbsLogModule[unIdx] = (int) ( 20 * log10f(
													sqrtf(
															(afOutDataBuf[i] * afOutDataBuf[i])
															+ (afOutDataBuf[i + 1] * afOutDataBuf[i + 1])
														 )
									           )
								  );


*/

//--------------------------------------------------------------------------

int16_t ProcessFft::fnGetValByIdx(uint16_t unIdx)
{
	return aunAbsLogModule[unIdx];
}


uint16_t ProcessFft::fnGetValByFreq(uint16_t unFreq)
{

	uint16_t unIdx = unFreq/(24000/(CO_PROCESS_FFT_INP_BUF/2));

	return aunAbsLogModule[unIdx];

/*
	if(aunAbsLogModule[unIdx] > 60)
	{ return aunAbsLogModule[unIdx] - 60;}
	else
	{return 1;}
*/
}



int16_t ProcessFft::fnGetValByFreqRange(uint16_t unFreqMin, uint16_t unFreqMax)
{

	uint16_t unIdxMin = unFreqMin/(24000/(CO_PROCESS_FFT_INP_BUF/2));
	uint16_t unIdxMax = unFreqMax/(24000/(CO_PROCESS_FFT_INP_BUF/2));

	uint16_t  unRetVal = 0;
	uint32_t ulSum = 0;

	for (uint16_t i = unIdxMin; i <= unIdxMax; i++)
	{
		if(unRetVal < aunAbsLogModule[i])
		{unRetVal = aunAbsLogModule[i];}



	}



	return unRetVal;

}



//


//wywolac w FFTBar i tam przeliczyć na skalę log
float32_t ProcessFft::ffGetMaxValByFreqRange_Lin(uint16_t unFreqMin, uint16_t unFreqMax)
{

	uint16_t unIdxMin = unFreqMin/(24000/(CO_PROCESS_FFT_INP_BUF/2));
	uint16_t unIdxMax = unFreqMax/(24000/(CO_PROCESS_FFT_INP_BUF/2));

	float32_t  fRetVal = 0;


	for (uint16_t i = unIdxMin; i <= unIdxMax; i++)
	{
		if(fRetVal < afInpDataBufCopy[i])
		{fRetVal = afInpDataBufCopy[i];}



	}

	return fRetVal;

}


//--------------------------------------------------------------------------

uint16_t ProcessFft::fnGetValByFreq_Average(uint16_t unFreq)
{

	uint16_t unIdx = unFreq/(24000/(CO_PROCESS_FFT_INP_BUF/2));

	return aunAbsLogModuleAverage[unIdx];

}





