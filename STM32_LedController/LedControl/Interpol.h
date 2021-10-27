/*
 * InterpolBiline.h
 *
 *  Created on: 25 lis 2019
 *      Author: Laptop
 */
//---------------------------------------------------------------------------------------------------------------
#ifndef INTERPOL_H_
#define INTERPOL_H_
//#include <stdexcept>
#include <cstdint>
//---------------------------------------------------------------------------------------------------------------
class TinterpolBiline
{
private:
	const uint16_t x1;
	const uint16_t x2;
	const uint16_t y1;
	const uint16_t y2;

protected:
	uint16_t q11;
	uint16_t q12;
	uint16_t q21;
	uint16_t q22;


public:
	TinterpolBiline(
					const uint16_t inpX1,const uint16_t inpX2,
					const uint16_t inpY1,const uint16_t inpY2,
					const uint16_t inpQ11 = 0,const uint16_t inpQ12 = 0,
					const uint16_t inpQ21 = 0,const uint16_t inpQ22 = 0
					);

	uint16_t getPointValue(const uint16_t x,const uint16_t y) const;
	uint16_t getPointValue(const uint16_t x, const uint16_t y, const uint16_t inpQ11,const uint16_t inpQ12, const uint16_t inpQ21, const uint16_t inpQ22) const;

	void setColors(const uint16_t inpQ11,const uint16_t inpQ12,
				   const uint16_t inpQ21,const uint16_t inpQ22);


};
//---------------------------------------------------------------------------------------------------------------
struct TInterpolBiline_BadArgExc
{

};
//---------------------------------------------------------------------------------------------------------------
#endif /* INTERPOL_H_ */
