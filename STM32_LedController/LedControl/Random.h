/*
 * Random.h
 *
 *  Created on: 12.10.2021
 *      Author: Laptop
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include "stdio.h"
#include "stdlib.h"

class TRandomGenerator
{
public:
	TRandomGenerator(uint16_t unInintVal);


	void SetEntropy(uint16_t unInintVal)
	{
		srand(unInintVal);
	}

	uint16_t funGetRandomValue(uint16_t unMin,uint16_t unMax);

	uint16_t funGetRandomColor();

};




#endif /* RANDOM_H_ */
