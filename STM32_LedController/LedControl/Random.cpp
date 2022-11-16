/*
 * Random.c
 *
 *  Created on: 12.10.2021
 *      Author: Laptop
 */

#include "./Random.h"
#include "colors.h"





TRandomGenerator::TRandomGenerator(uint16_t unInintVal)
{
	SetEntropy(unInintVal);
}


uint16_t TRandomGenerator::funGetRandomValue(uint16_t unMin,uint16_t unMax)
{

	int16_t nRandom = rand();

	uint16_t unRet =  (abs(nRandom) % (unMax - unMin + 1)) + unMin;

	return unRet;
}


uint16_t TRandomGenerator::funGetRandomColor()
{

	uint16_t unIdx = funGetRandomValue(0,funGetSizeofColorTab() );

	return ColorTab[unIdx];
}


uint16_t TRandomGenerator::funGetRandomColor(const struct def_color_srt* pColorStr)
{
	uint16_t unIdx = funGetRandomValue(0,pColorStr->unNumbOfColors - 1);

	return pColorStr->pColorTab[unIdx];


}
