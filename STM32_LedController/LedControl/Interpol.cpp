/*
 * InterpolBiline.cpp
 *
 *  Created on: 25 lis 2019
 *      Author: Laptop
 */
//---------------------------------------------------------------------------------------------------------------
#include "Interpol.h"


//---------------------------------------------------------------------------------------------------------------
TinterpolBiline::TinterpolBiline(const uint16_t inpX1,const uint16_t inpX2,
								 const uint16_t inpY1,const uint16_t inpY2,
								 const uint16_t inpQ11,const uint16_t inpQ12,
								 const uint16_t inpQ21,const uint16_t inpQ22

				):x1(inpX1), x2(inpX2), y1(inpY1), y2(inpY2),q11(inpQ11), q12(inpQ12), q21(inpQ21), q22(inpQ22)
{
/*

	if( (inpX1 >= inpX2) || (inpY1 >= inpY2) )
	{
		struct TInterpolBiline_BadArgExc e;
		throw e;
	}
*/
}


//---------------------------------------------------------------------------------------------------------------
void TinterpolBiline::setCornersColors(const uint16_t inpQ11,const uint16_t inpQ12,
				   const uint16_t inpQ21,const uint16_t inpQ22)
{
	q11 = inpQ11;
    q12 = inpQ12;
    q21 = inpQ21;
    q22 = inpQ22;


}

//---------------------------------------------------------------------------------------------------------------
uint16_t TinterpolBiline::getPointValue(const uint16_t x, const uint16_t y, const uint16_t inpQ11,const uint16_t inpQ12, const uint16_t inpQ21, const uint16_t inpQ22) const
{
	uint16_t result;

	if( (x == x1) && (y == y1) )
	{
		return inpQ11;
	}

	if( (x == x1) && (y == y2) )
	{
		return inpQ12;
	}

	if( (x == x2) && (y == y1) )
	{
		return inpQ21;
	}

	if( (x == x2) && (y == y2) )
	{
		return inpQ22;
	}


	float fxy1 =   ( static_cast<float>( static_cast<uint32_t>(x2 - x) * static_cast<uint32_t>(inpQ11) ) ) / ( static_cast<float>( x2 - x1 ) )
			      + ( static_cast<float>( static_cast<uint32_t>(x - x1) * static_cast<uint32_t>(inpQ21) ) ) / ( static_cast<float>( x2 - x1 ) );

	float fxy2 =   ( static_cast<float>( static_cast<uint32_t>(x2 - x) * static_cast<uint32_t>(inpQ12) ) ) / ( static_cast<float>( x2 - x1 ) )
			      + ( static_cast<float>( static_cast<uint32_t>(x - x1) * static_cast<uint32_t>(inpQ22) ) ) / ( static_cast<float>( x2 - x1 ) );

	float fxy =  ( static_cast<float>( y2 - y ) * fxy1 ) / ( static_cast<float>( y2 - y1 ) )
			    + ( static_cast<float>( y - y1 ) * fxy2 ) / ( static_cast<float>( y2 - y1 ) ) ;


	result = static_cast<uint16_t>(fxy);


	//DEBUG_OUT("x " << x << " y " << y << " fxy1 " << fxy1 << " fxy2 " << fxy2 << " fxy " << fxy <<  " res " << result << "\r\n");


	if( (fxy - result) >= 0.5)        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{result++;}

	return result;
}
//---------------------------------------------------------------------------------------------------------------
uint16_t TinterpolBiline::getPointValue(const uint16_t x,const  uint16_t y) const
{

	return getPointValue( x, y, q11,q12,q21,q22);

}
//---------------------------------------------------------------------------------------------------------------



uint16_t TinterpolBiline::fvAjustCornerLinear(uint16_t inpQ11,uint16_t inpQ12,uint16_t inpQ21,uint16_t inpQ22)
{
	uint16_t unRet = 0;

	if(inpQ11 > q11)
	{
		q11++;
		unRet++;
	}

	if(inpQ11 < q11)
	{
		q11--;
		unRet++;
	}
	//--
	if(inpQ12 > q12)
	{
		q12++;
		unRet++;
	}

	if(inpQ12 < q12)
	{
		q12--;
		unRet++;
	}

	//--
	if(inpQ21 > q21)
	{
		q21++;
		unRet++;
	}

	if(inpQ21 < q21)
	{
		q21--;
		unRet++;
	}

	//--
	if(inpQ22 > q22)
	{
		q22++;
		unRet++;
	}

	if(inpQ22 < q22)
	{
		q22--;
		unRet++;
	}

	return unRet;
}



