#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "./LedRgb.h"
#include "./LedSection.h"
#include "./TBargraf.h"
#include "./TLedRgbLine.h"
#include "./Random.h"
#include "Interpol.h"
#include "colors.h"
#include "../aplDsp/ProcessFft.h"
#include "../aplDsp/FftBar.h"

extern ProcessFft processFFT;



/*
FftBar fftBar100Hz(&processFFT,120,150);
FftBar fftBar1kHz(&processFFT,500,1500);
FftBar fftBar3kHz(&processFFT,1500,5000);
FftBar fftBar7kHz(&processFFT,5000,8000);
FftBar fftBar10kHz(&processFFT,8000,12000);

*/

FftBar fftBar100Hz(&processFFT,110,130);
FftBar fftBar1kHz(&processFFT,900,1100);
FftBar fftBar3kHz(&processFFT,2700,3300);
FftBar fftBar7kHz(&processFFT,6300,7700);
FftBar fftBar10kHz(&processFFT,8000,12000);




//-----------------------------------------------------------------------------------------------------------------------------
void fnSetMatrixColors(TLedRgbLine* pLine,TinterpolBiline* pColorMatrix);
void fnColorTransformation(uint16_t unDelaySec, bool bRestart);
//-----------------------------------------------------------------------------------------------------------------------------
#define CO_NUMB_OF_LED_LINES 5
#define CO_NUMB_LEDS_IN_LINE 60
#define CO_DISP_FREQ 50 //20ms

class TLedRgb Led[CO_WS2812_NUMB_OF_LEDS];
TRandomGenerator RandomGen{0x9832};

class TinterpolBiline ColorMatrix(0,4,0,59);

#define CO_BRIGHTNESS_LIMIT_MAX 10
//-----------------------------------------------------------------------------------------------------------------------------
const TLedRgb* Line0Leds[] = {
/*0*/	&Led[59], &Led[58], &Led[57], &Led[56], &Led[55], &Led[54], &Led[53], &Led[52], &Led[51], &Led[50],
/*10*/	&Led[49], &Led[48], &Led[47], &Led[46], &Led[45], &Led[44], &Led[43], &Led[42], &Led[41], &Led[40],
/*20*/	&Led[39], &Led[38], &Led[37], &Led[36], &Led[35], &Led[34], &Led[33], &Led[32], &Led[31], &Led[30],
/*30*/	&Led[29], &Led[28], &Led[27], &Led[26], &Led[25], &Led[24], &Led[23], &Led[22], &Led[21], &Led[20],
/*40*/	&Led[19], &Led[18], &Led[17], &Led[16], &Led[15], &Led[14], &Led[13], &Led[12], &Led[11], &Led[10],
/*50*/	&Led[9],  &Led[8],  &Led[7] , &Led[6] , &Led[5] , &Led[4] , &Led[3],  &Led[2],  &Led[1],  &Led[0]
};


//----------------

const TLedRgb* Line1Leds[] = {
&Led[119],&Led[118],&Led[117],&Led[116],&Led[115],&Led[114],&Led[113],&Led[112],&Led[111],&Led[110],
	&Led[109],&Led[108],&Led[107],&Led[106],&Led[105],&Led[104],&Led[103],&Led[102],&Led[101],&Led[100],
	&Led[99], &Led[98], &Led[97], &Led[96], &Led[95], &Led[94], &Led[93], &Led[92], &Led[91], &Led[90],
	&Led[89], &Led[88], &Led[87], &Led[86], &Led[85], &Led[84], &Led[83], &Led[82], &Led[81], &Led[80],
	&Led[79], &Led[78], &Led[77], &Led[76], &Led[75], &Led[74], &Led[73], &Led[72], &Led[71], &Led[70],
	&Led[69], &Led[68], &Led[67], &Led[66], &Led[65], &Led[64], &Led[63], &Led[62], &Led[61], &Led[60]
};



/*
const TLedRgb* Line1Leds[] = {
0	&Led[60],&Led[61],&Led[62],&Led[63],&Led[64],&Led[65],&Led[66],&Led[67],&Led[68],&Led[69],
0	&Led[70],&Led[71],&Led[72],&Led[73],&Led[74],&Led[75],&Led[76],&Led[77],&Led[78],&Led[79],
0	&Led[80],&Led[81],&Led[82],&Led[83],&Led[84],&Led[85],&Led[86],&Led[87],&Led[88],&Led[89],
0	&Led[90],&Led[91],&Led[92],&Led[93],&Led[94],&Led[95],&Led[96],&Led[97],&Led[98],&Led[99],
10	&Led[100],&Led[101],&Led[102],&Led[103],&Led[104],&Led[105],&Led[106],&Led[107],&Led[108],&Led[109],
		&Led[110],&Led[111],&Led[112],&Led[113],&Led[114],&Led[115],&Led[116],&Led[117],&Led[118],&Led[119]
};

*/



//----------------



const TLedRgb* Line2Leds[] = {
/*0*/	&Led[179],&Led[178],&Led[177],&Led[176],&Led[175],&Led[174],&Led[173],&Led[172],&Led[171],&Led[170],
/*10*/	&Led[169],&Led[168],&Led[167],&Led[166],&Led[165],&Led[164],&Led[163],&Led[162],&Led[161],&Led[160],
/*20*/	&Led[159],&Led[158],&Led[157],&Led[156],&Led[155],&Led[154],&Led[153],&Led[152],&Led[151],&Led[150],
/*30*/	&Led[149],&Led[148],&Led[147],&Led[146],&Led[145],&Led[144],&Led[143],&Led[142],&Led[141],&Led[140],
/*40*/	&Led[139],&Led[138],&Led[137],&Led[136],&Led[135],&Led[134],&Led[133],&Led[132],&Led[131],&Led[130],
/*50*/	&Led[129],&Led[128],&Led[127],&Led[126],&Led[125],&Led[124],&Led[123],&Led[122],&Led[121],&Led[120]
};

//---------------------------------

const TLedRgb* Line3Leds[] = {
&Led[239],&Led[238],&Led[237],&Led[236],&Led[235],&Led[234],&Led[233],&Led[232],&Led[231],&Led[230],
	&Led[229],&Led[228],&Led[227],&Led[226],&Led[225],&Led[224],&Led[223],&Led[222],&Led[221],&Led[220],
	&Led[219],&Led[218],&Led[217],&Led[216],&Led[215],&Led[214],&Led[213],&Led[212],&Led[211],&Led[210],
	&Led[209],&Led[208],&Led[207],&Led[206],&Led[205],&Led[204],&Led[203],&Led[202],&Led[201],&Led[200],
	&Led[199],&Led[198],&Led[197],&Led[196],&Led[195],&Led[194],&Led[193],&Led[192],&Led[191],&Led[190],
	&Led[189],&Led[188],&Led[187],&Led[186],&Led[185],&Led[184],&Led[183],&Led[182],&Led[181],&Led[180]

};

/*

const TLedRgb* Line3Leds[] = {
		&Led[180],&Led[181],&Led[182],&Led[183],&Led[184],&Led[185],&Led[186],&Led[187],&Led[188],&Led[189],
		&Led[190],&Led[191],&Led[192],&Led[193],&Led[194],&Led[195],&Led[196],&Led[197],&Led[198],&Led[199],
		&Led[200],&Led[201],&Led[202],&Led[203],&Led[204],&Led[205],&Led[206],&Led[207],&Led[208],&Led[209],
		&Led[210],&Led[211],&Led[212],&Led[213],&Led[214],&Led[215],&Led[216],&Led[217],&Led[218],&Led[219],
		&Led[220],&Led[221],&Led[222],&Led[223],&Led[224],&Led[225],&Led[226],&Led[227],&Led[228],&Led[229],
		&Led[230],&Led[231],&Led[232],&Led[233],&Led[234],&Led[235],&Led[236],&Led[237],&Led[238],&Led[239]
};
*/



//---------------------------------


const TLedRgb* Line4Leds[] = {
/*0*/	&Led[299],&Led[298],&Led[297],&Led[296],&Led[295],&Led[294],&Led[293],&Led[292],&Led[291],&Led[290],
/*10*/	&Led[289],&Led[288],&Led[287],&Led[286],&Led[285],&Led[284],&Led[283],&Led[282],&Led[281],&Led[280],
/*20*/	&Led[279],&Led[278],&Led[277],&Led[276],&Led[275],&Led[274],&Led[273],&Led[272],&Led[271],&Led[270],
/*30*/	&Led[269],&Led[268],&Led[267],&Led[266],&Led[265],&Led[264],&Led[263],&Led[262],&Led[261],&Led[260],
/*40*/	&Led[259],&Led[258],&Led[257],&Led[256],&Led[255],&Led[254],&Led[253],&Led[252],&Led[251],&Led[250],
/*50*/	&Led[249],&Led[248],&Led[247],&Led[246],&Led[245],&Led[244],&Led[243],&Led[242],&Led[241],&Led[240]

};

//-------------------------
/*
class TLedRgbLine LedLine[CO_NUMB_OF_LED_LINES] = {
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 0], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),
	TLedRgbLine(Line1Leds, CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),//TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 1], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 2], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),
	TLedRgbLine(Line3Leds, CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),//TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 3], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 4], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX)
};
*/

class TLedRgbLine LedLine[CO_NUMB_OF_LED_LINES] = {
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 0], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 1], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 2], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 3], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 4], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX)
};



#define CO_MAX_PREDELAY 2
#define CO_MAX_DELAY 4


//-------------------------
class TBargraf Bargraf[CO_NUMB_OF_LED_LINES] = {

	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 0], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX, CO_MAX_PREDELAY, CO_MAX_DELAY),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 1], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX, CO_MAX_PREDELAY, CO_MAX_DELAY),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 2], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX, CO_MAX_PREDELAY, CO_MAX_DELAY),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 3], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX, CO_MAX_PREDELAY, CO_MAX_DELAY),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 4], CO_NUMB_LEDS_IN_LINE, CO_BRIGHTNESS_LIMIT_MAX, CO_MAX_PREDELAY, CO_MAX_DELAY)
};



//-------------------------
/*
TBargraf BargrafHalfUp[CO_NUMB_OF_LED_LINES] = {
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 0 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line1Leds[30],30),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 2 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line3Leds[30],30),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 4 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
};
*/


TBargraf BargrafHalfUp[CO_NUMB_OF_LED_LINES] = {
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 0 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 1 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 2 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 3 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 4 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
};





/*

TBargraf BargrafHalfDown[CO_NUMB_OF_LED_LINES] = {
		TBargraf(&Line0Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 1 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line2Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 3 + 30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line4Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX)
};

*/


TBargraf BargrafHalfDown[CO_NUMB_OF_LED_LINES] = {

		TBargraf(&Line0Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line1Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line2Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line3Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX),
		TBargraf(&Line4Leds[30],30, CO_BRIGHTNESS_LIMIT_MAX)
};


//---------------------------------------------------------------------------------------------------------------------------------------------------
#define CO_PI (3.141692f)
#define CO_SIN_RASTER (CO_PI/20)

struct def_led_statem_machine
{
	uint16_t unMainTask;
	uint16_t unInternalTask;
	uint16_t unMainTimer;



};

#define CO_TIMEOUT_CHANGE_MODE   (50*60*1) //10 sek for test  //(50*60*10) //10min

struct def_led_statem_machine State;

enum {EN_LED_EFFECT_RAIN=1,EN_LED_EFFECT_SIN_1HALF,EN_LED_EFFECT_SNOW1,EN_LED_EFFECT_SIN_2HALF,EN_LED_EFFECT_SPECTRUM,EN_LED_EFFECT_END};


//----------------------------------------------------------------------------------
void fvSetMatixColors()
{
	for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
	{

		for(uint16_t unLedIdx = 0; unLedIdx < CO_NUMB_LEDS_IN_LINE; unLedIdx++)
		{
			LedLine[unLineIdx].SetHue(unLedIdx,ColorMatrix.getPointValue(unLineIdx,unLedIdx));
		}
	}
}


//----------------------------------------------------------------------------------
void fvRainEffect()
{
	for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
	{
		LedLine[unLineIdx].fvDropEffect();
	}

}
//----------------------------------------------------------------------------------
void fvSinus1HalfEffect()
{
	static uint16_t unPom = 0;
	static float fRadius = 0;



	if(State.unInternalTask == 0)
	{//restart
		for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
		{
			LedLine[unLineIdx].SetHue(0,CO_NUMB_LEDS_IN_LINE,75 * unLineIdx);
		}

		State.unInternalTask = 1;
	}
	else
	{


		unPom++;
		if(unPom > 1000)
		{unPom = 0;}

		if(unPom % 2 == 0)
		{
			fRadius += (2*CO_PI)/100;
		}

		int16_t nSin;


		for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
		{
			nSin = static_cast<int16_t>( fabs(sin(fRadius + (unLineIdx * CO_SIN_RASTER) ) ) * 1000 );
			Bargraf[unLineIdx].fvBargrafEffect(nSin);
		}
	}
}

//----------------------------------------------------------------------------------
void fvSinus2HalfEffect()
{

//	static uint16_t unPom = 0;
	static float fRadius = 0;
	static uint16_t unTime = 0;


	if(State.unInternalTask == 0)
	{//restart
/*
		for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
		{
			LedLine[unLineIdx].SetHue(0,CO_NUMB_LEDS_IN_LINE,RandomGen.funGetRandomColor());
		}
*/
		fnColorTransformation(10,true);

		for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
		{
			LedLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,10);
		}

		State.unInternalTask = 1;

	}

	if(unTime)
	{
		unTime--;
		return;
	}
	else
	{unTime = 0;}


	fnColorTransformation(10,false);

	/*unTime++;
	if(unTime > 500)
	{
		unTime = 0;
	}
*/
/*
	unPom++;
	if(unPom > 1000)
	{unPom = 0;}
*/

	fRadius += (2*CO_PI)/200;

	int16_t nSin;

	for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
	{
		nSin = static_cast<int16_t>( fabs(sin(fRadius + (unLineIdx * CO_SIN_RASTER) ) ) * 1000 );
		BargrafHalfUp[unLineIdx].fvSetNomralizedTo1000(nSin);
		BargrafHalfDown[unLineIdx].fvSetNomralizedTo1000(nSin);
	}


}
//--------------------------------------------------------------------------------------
void fvSnowEffect1()
{

	static uint16_t unPom = 0;
	static uint16_t Color = 0;



	if (State.unInternalTask == 0)
	{
		unPom = 0;
		State.unInternalTask = 1;
	}




	if(unPom == 0)
	{
		for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
		{LedLine[unLineIdx].fvSnowEffect(CO_OPEN_ARG_RESTART);}

		Color = RandomGen.funGetRandomColor();

		//LedLine[4].SetHue(0,59,Color);
	    //ColorMatrix.setCornersColors(Color,Color,Color,Color); //LD LG PD PG*/
	    //fnSetMatrixColors(&LedLine[0],&ColorMatrix);

		unPom = 3000;
	}
	else
	{
		unPom--;
	}

	if(unPom % 50 == 0)
	{
		LedLine[0].fvSnowEffect(CO_OPEN_ARG_PUT,Color);
	}
	else
	{
		LedLine[0].fvSnowEffect(CO_OPEN_ARG_MOVE);
	}



	if(unPom % 50 == 10)
	{
		LedLine[1].fvSnowEffect(CO_OPEN_ARG_PUT,Color);
	}
	else
	{
		LedLine[1].fvSnowEffect(CO_OPEN_ARG_MOVE);
	}


	if(unPom % 50 == 30)
	{
		LedLine[2].fvSnowEffect(CO_OPEN_ARG_PUT,Color);
	}
	else
	{
		LedLine[2].fvSnowEffect(CO_OPEN_ARG_MOVE);
	}

	if(unPom % 50 == 40)
	{
		LedLine[3].fvSnowEffect(CO_OPEN_ARG_PUT,Color);
	}
	else
	{
		LedLine[3].fvSnowEffect(CO_OPEN_ARG_MOVE);
	}

	if(unPom % 50 == 15)
	{
		LedLine[4].fvSnowEffect(CO_OPEN_ARG_PUT,Color);
	}
	else
	{
		LedLine[4].fvSnowEffect(CO_OPEN_ARG_MOVE);
	}



}



void fvSpectrum()
{

	static uint16_t unTim;

	 unTim++;
	// if( unTim % 3 != 0)
	// {return;}


	if(State.unInternalTask == 0)
	{//restart
		for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
		{
			//LedLine[unLineIdx].SetHue(0,CO_NUMB_LEDS_IN_LINE,75 * unLineIdx);
			LedLine[unLineIdx].fvColorPattern1(80,360,2);
		}

		State.unInternalTask = 1;
	}
	else
	{
/*
		Bargraf[0].fvBargrafEffect(processFFT.fnGetValByFreqRange(120,150));
		Bargraf[1].fvBargrafEffect(processFFT.fnGetValByFreqRange(500,1500));
		Bargraf[2].fvBargrafEffect(processFFT.fnGetValByFreqRange(1500, 5000));
		Bargraf[3].fvBargrafEffect(processFFT.fnGetValByFreqRange(5000,8000));
		Bargraf[4].fvBargrafEffect(processFFT.fnGetValByFreqRange(8000, 12000));
*/

		Bargraf[0].fvBargrafEffect(fftBar100Hz.fnGetNormalizedVal());
		Bargraf[1].fvBargrafEffect(fftBar1kHz.fnGetNormalizedVal());
		Bargraf[2].fvBargrafEffect(fftBar3kHz.fnGetNormalizedVal());
		Bargraf[3].fvBargrafEffect(fftBar7kHz.fnGetNormalizedVal());
		Bargraf[4].fvBargrafEffect(fftBar10kHz.fnGetNormalizedVal());

	}
}



//----------------------------------------------------------------------------------
void fvMainLed20ms()
{



	//---
	State.unMainTask = EN_LED_EFFECT_SPECTRUM;
	State.unMainTimer = CO_TIMEOUT_CHANGE_MODE;
	for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
	{
		LedLine[unLineIdx].fvEnable(0,CO_NUMB_LEDS_IN_LINE);
		LedLine[unLineIdx].SetSaturation(0,CO_NUMB_LEDS_IN_LINE,100);
		LedLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,0);
	}
	//---


	 if(State.unMainTimer)
	 {
		 State.unMainTimer--;

		 switch(State.unMainTask)
		 {

		 	 case EN_LED_EFFECT_SPECTRUM:
		 	 {
		 		fvSpectrum();
		 	 }break;

		 	 case EN_LED_EFFECT_RAIN:
		 	 {


		 		 fvRainEffect();

		 	 }break;


		 	 case EN_LED_EFFECT_SIN_1HALF:
			 {
				 fvSinus1HalfEffect();
			 }break;

		 	 case EN_LED_EFFECT_SIN_2HALF:
			 {
				 fvSinus2HalfEffect();
			 }break;

		 	 case EN_LED_EFFECT_SNOW1:
			 {
				 fvSnowEffect1();
			 }break;



		 	 default:
		 	 {
		 		State.unMainTimer = 0;
		 	 }break;
		 }


	 }
	 else
	 {
		 State.unMainTimer = CO_TIMEOUT_CHANGE_MODE;

		 State.unInternalTask = 0;
		 //State.unMainTask = RandomGen.funGetRandomValue(1,EN_LED_EFFECT_END - 1);

		 //--

		 State.unMainTask++;
		 if(State.unMainTask >= EN_LED_EFFECT_END)
		 {
			 State.unMainTask = 1;
		 }

		 //State.unMainTask = EN_LED_EFFECT_SIN_2HALF;
		 //--
		 for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
		 {
			LedLine[unLineIdx].fvEnable(0,CO_NUMB_LEDS_IN_LINE);
			LedLine[unLineIdx].SetSaturation(0,CO_NUMB_LEDS_IN_LINE,100);
			LedLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,0);
		 }
	 }

	 for(uint16_t i = 0; i < CO_NUMB_OF_LED_LINES; i++)
	 {
		LedLine[i].Refresh();
	 }
}



void fvMainLed20ms_2()
{
	static uint16_t unTask = 0;




	switch(unTask)
	{

		case 0:
		{




			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].fvEnable(0,CO_NUMB_LEDS_IN_LINE);
				LedLine[unLineIdx].SetSaturation(0,CO_NUMB_LEDS_IN_LINE,100);

				LedLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,0);

				LedLine[unLineIdx].SetHue(0,CO_NUMB_LEDS_IN_LINE,75 * unLineIdx);
			}


			ColorMatrix.setCornersColors(RandomGen.funGetRandomColor(),RandomGen.funGetRandomColor(),RandomGen.funGetRandomColor(),RandomGen.funGetRandomColor()); //LD LG PD PG

			unTask = 2;
		}break;

		case 1:
		{//ok

			LedLine[0].fvDropEffect();
			LedLine[1].fvDropEffect();
			LedLine[2].fvDropEffect();
			LedLine[3].fvDropEffect();
			LedLine[4].fvDropEffect();
		}break;



		case 2:
		{//ok
			static uint16_t unPom = 0;
			static float fRadius = 0;
			static uint16_t unPom2 = 0;

			unPom++;
			if(unPom > 1000)
			{unPom = 0;}

			if(unPom % 2 == 0)
			{
				fRadius += (2*CO_PI)/100;
			}

			int16_t nSin;


			nSin =  static_cast<int16_t>( fabs(sin(fRadius)) * 1000 );
			Bargraf[0].fvBargrafEffect(nSin);


			nSin = static_cast<int16_t>( fabs(sin(fRadius + (1* CO_SIN_RASTER) ) ) * 1000 );
			Bargraf[1].fvBargrafEffect(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (2* CO_SIN_RASTER) ) ) * 1000 );
			Bargraf[2].fvBargrafEffect(nSin);

			nSin = static_cast<int16_t>(fabs(sin(fRadius + (3* CO_SIN_RASTER) ) ) * 1000 );
			Bargraf[3].fvBargrafEffect(nSin);


			nSin = static_cast<int16_t>( fabs(sin(fRadius + (4* CO_SIN_RASTER) ) ) * 1000 );
			Bargraf[4].fvBargrafEffect(nSin);


		}break;

		case 3:
		{//ok
			static uint16_t unPom = 0;
			static float fRadius = 0;
			static uint16_t unTime = 0;


			unTime++;
			if(unTime > 500)
			{
				unTime = 0;
				unTask = 6;
			}

			unPom++;
			if(unPom > 1000)
			{unPom = 0;}

			fRadius += (2*CO_PI)/200;



			int16_t nSin;


			nSin =  static_cast<int16_t>( fabs(sin(fRadius)) * 1000 );
			BargrafHalfUp[0].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[0].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (1* CO_SIN_RASTER) ) ) * 1000 );
			BargrafHalfUp[1].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[1].fvSetNomralizedTo1000(nSin);


			nSin = static_cast<int16_t>( fabs(sin(fRadius + (2* CO_SIN_RASTER) ) ) * 1000 );//>>
			BargrafHalfUp[2].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[2].fvSetNomralizedTo1000(nSin);



			nSin = static_cast<int16_t>(fabs(sin(fRadius + (3* CO_SIN_RASTER) ) ) * 1000 );
			BargrafHalfUp[3].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[3].fvSetNomralizedTo1000(nSin);


			nSin = static_cast<int16_t>( fabs(sin(fRadius + (4* CO_SIN_RASTER) ) ) * 1000 );
			BargrafHalfUp[4].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[4].fvSetNomralizedTo1000(nSin);



		}break;


		case 4:
		{
			static uint16_t unPom = 0;


			unPom++;
			if(unPom > 3000)
			{
				unPom = 0;
			}

			if(unPom == 0)
			{
			   LedLine[0].fvSnowEffect(CO_OPEN_ARG_RESTART);
			   LedLine[1].fvSnowEffect(CO_OPEN_ARG_RESTART);
			   LedLine[2].fvSnowEffect(CO_OPEN_ARG_RESTART);
			   LedLine[3].fvSnowEffect(CO_OPEN_ARG_RESTART);
			   LedLine[4].fvSnowEffect(CO_OPEN_ARG_RESTART);

			   uint16_t Color = RandomGen.funGetRandomColor();

			   LedLine[4].SetHue(0,59,Color);

			   //ColorMatrix.setColors(Color,Color,Color,Color); //LD LG PD PG*/

			}



			if(unPom % 50 == 0)
			{
				LedLine[0].fvSnowEffect(CO_OPEN_ARG_PUT);
			}
			else
			{
				LedLine[0].fvSnowEffect(CO_OPEN_ARG_MOVE);
			}


			if(unPom % 50 == 10)
			{
				LedLine[1].fvSnowEffect(CO_OPEN_ARG_PUT);
			}
			else
			{
				LedLine[1].fvSnowEffect(CO_OPEN_ARG_MOVE);
			}


			if(unPom % 50 == 30)
			{
				LedLine[2].fvSnowEffect(CO_OPEN_ARG_PUT);
			}
			else
			{
				LedLine[2].fvSnowEffect(CO_OPEN_ARG_MOVE);
			}

			if(unPom % 50 == 40)
			{
				LedLine[3].fvSnowEffect(CO_OPEN_ARG_PUT);
			}
			else
			{
				LedLine[3].fvSnowEffect(CO_OPEN_ARG_MOVE);
			}

			if(unPom % 50 == 15)
			{
				LedLine[4].fvSnowEffect(CO_OPEN_ARG_PUT);
			}
			else
			{
				LedLine[4].fvSnowEffect(CO_OPEN_ARG_MOVE);
			}


		}break;

		case 5:
		{
			static int16_t nLineIdx = (CO_NUMB_OF_LED_LINES - 1) * (-1);
			static int16_t unLedIdx = 0;
			static int16_t nDirection = 1;

			static uint16_t unPom = 0;


			unPom++;
			if(unPom > 2)
			{
				unPom = 0;
			}
			else
			{break;}



			if(nLineIdx >= CO_NUMB_OF_LED_LINES)
			{
				nDirection = -1;
			}

			if(nLineIdx < 0)
			{
				nDirection = 1;
			}

			nLineIdx += nDirection;


			if(nLineIdx == 0)
			{
				unLedIdx++;
				if(unLedIdx > CO_NUMB_LEDS_IN_LINE)
				{
					unLedIdx = 0;
					for(int16_t k = 0; k < CO_NUMB_OF_LED_LINES ; k++)
					{
						LedLine[k].fvSnowEffect(CO_OPEN_ARG_RESTART);
					}
				}
			}



			for(int16_t k = 0; k < CO_NUMB_OF_LED_LINES ; k++)
			{
				if(nLineIdx == k)
				{
					LedLine[k].fvSnowEffect(CO_OPEN_ARG_MOVE);
					LedLine[k].fvSnowEffect(CO_OPEN_ARG_PUT);
				}
				else
				{LedLine[k].fvSnowEffect(CO_OPEN_ARG_MOVE);}

			}





		}break;


		case 6:
		{
			static uint16_t unDelay = 0;


			if(unDelay)
			{
				unDelay--;
				break;
			}

			//unDelay = 200;

			//ColorMatrix.setColors(360,0,0,360); //LD LG PD PG
			ColorMatrix.setCornersColors(RandomGen.funGetRandomColor(),
									RandomGen.funGetRandomColor(),
									RandomGen.funGetRandomColor(),
									RandomGen.funGetRandomColor());



			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,10);
				for(uint16_t unLedIdx = 0; unLedIdx < CO_NUMB_LEDS_IN_LINE; unLedIdx++)
				{
					LedLine[unLineIdx].SetHue(unLedIdx,ColorMatrix.getPointValue(unLineIdx,unLedIdx));
				}
			}

			unTask = 3;

		}break;


		case 7:
		{
			static uint16_t un_Color = 0;

			static uint16_t unDelay = 0;
			static uint16_t unIdx = 0;


			unDelay++;
			if(unDelay < 10)
			{
				break;
			}
			unDelay = 0;
			un_Color += 1;
			un_Color %= 360;

			//ColorMatrix.getPointValue(unLineIdx,unLedIdx)

			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].fvEnable(0,CO_NUMB_LEDS_IN_LINE);
				LedLine[unLineIdx].SetSaturation(0,CO_NUMB_LEDS_IN_LINE,100);
				LedLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,10);
				LedLine[unLineIdx].SetHue(0,CO_NUMB_LEDS_IN_LINE,ColorTab[unIdx]);
			}



			unIdx++;
			unIdx %= funGetSizeofColorTab();


		}break;

		case 8:
		{
			fnColorTransformation(3,false);

			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,10);
			}

		}break;


	}

	LedLine[0].Refresh();
	LedLine[1].Refresh();
	LedLine[2].Refresh();
	LedLine[3].Refresh();
	LedLine[4].Refresh();

}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void fnSetMatrixColors(TLedRgbLine* pLine,TinterpolBiline* pColorMatrix)
{
	for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
	{
		//pLine[unLineIdx].SetBrightness(0,CO_NUMB_LEDS_IN_LINE,10);
		for(uint16_t unLedIdx = 0; unLedIdx < CO_NUMB_LEDS_IN_LINE; unLedIdx++)
		{
			pLine[unLineIdx].SetHue(unLedIdx,pColorMatrix->getPointValue(unLineIdx,unLedIdx));
		}
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------------

void fnColorTransformation(uint16_t unDelaySec, bool bRestart)
{
	static uint16_t ColorDest_LD = 0;
	static uint16_t ColorDest_LG = 0;
	static uint16_t ColorDest_PD = 0;
	static uint16_t ColorDest_PG = 0;

	static uint16_t unTask = 0;
	static uint16_t unTimer = 0;


	if(bRestart == true)
	{
		 unTask = 0;
	}


	switch(unTask)
	{
		case 0:
		{
			switch(RandomGen.funGetRandomValue(0,3))
			{
				case 0:
				{
					//ColorDest_LD = RandomGen.funGetRandomValue(0,360);
					ColorDest_LD = RandomGen.funGetRandomColor();
				}break;

				case 1:
				{
					//ColorDest_LG = RandomGen.funGetRandomValue(0,360);
					ColorDest_LG = RandomGen.funGetRandomColor();
				}break;

				case 2:
				{
					//ColorDest_PD = RandomGen.funGetRandomValue(0,360);
					ColorDest_PD = RandomGen.funGetRandomColor();
				}break;

				case 3:
				{
					//ColorDest_PG = RandomGen.funGetRandomValue(0,360);
					ColorDest_PG = RandomGen.funGetRandomColor();
				}break;
			}

			unTask = 1;


		}break;

		case 1:
		{
			if(ColorMatrix.fvAjustCornerLinear(ColorDest_LD,ColorDest_LG,ColorDest_PD,ColorDest_PG) == 0)
			{
				unTask = 2;
				unTimer = 50 * unDelaySec;
			}

			fnSetMatrixColors(&LedLine[0],&ColorMatrix);


		}break;


		case 2:
		{//wait

			if(unTimer)
			{unTimer--;}
			else
			{unTask = 0;}
		}break;

	}
}




//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------

