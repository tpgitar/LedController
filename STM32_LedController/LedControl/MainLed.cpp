#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "./LedRgb.h"
#include "./LedSection.h"
#include "./TBargraf.h"
#include "./Random.h"

//-----------------------------------------------------------------------------------------------------------------------------
#define CO_NUMB_OF_LED_LINES 5
#define CO_NUMB_LEDS_IN_LINE 60
#define CO_DISP_FREQ 50 //20ms

class TLedRgb Led[CO_WS2812_NUMB_OF_LEDS];
TRandomGenerator RandomGen{0x9832};
//-----------------------------------------------------------------------------------------------------------------------------
enum {EN_LED_MODE_ZERO,EN_LED_MODE_DROP};

class TLedRgbLine : public TLedRgbSection
{
private:

public:
	TLedRgbLine(const TLedRgb* pLedTabInp, uint16_t unLedTabLenghtInp): TLedRgbSection(pLedTabInp,unLedTabLenghtInp) {}
	TLedRgbLine(const TLedRgb** ppLedTabInp, uint16_t unLedTabLenghtInp): TLedRgbSection(ppLedTabInp,unLedTabLenghtInp) {}

	void fvMoveDown(uint16_t unStep);

	void fvDropEffect();

	uint16_t unTask;
	uint16_t unMode;
	uint16_t unDelay;
	uint16_t unSecDelay;
};
//-----------------------------------------------------------------------------------------------------------------------------------

const TLedRgb* Line0Leds[] = {
/*0*/	&Led[59], &Led[58], &Led[57], &Led[56], &Led[55], &Led[54], &Led[53], &Led[52], &Led[51], &Led[50],
/*10*/	&Led[49], &Led[48], &Led[47], &Led[46], &Led[45], &Led[44], &Led[43], &Led[42], &Led[41], &Led[40],
/*20*/	&Led[39], &Led[38], &Led[37], &Led[36], &Led[35], &Led[34], &Led[33], &Led[32], &Led[31], &Led[30],
/*30*/	&Led[29], &Led[28], &Led[27], &Led[26], &Led[25], &Led[24], &Led[23], &Led[22], &Led[21], &Led[20],
/*40*/	&Led[19], &Led[18], &Led[17], &Led[16], &Led[15], &Led[14], &Led[13], &Led[12], &Led[11], &Led[10],
/*50*/	&Led[9],  &Led[8],  &Led[7] , &Led[6] , &Led[5] , &Led[4] , &Led[3],  &Led[2],  &Led[1],  &Led[0]
};


const TLedRgb* Line1Leds[] = {
	&Led[119],&Led[118],&Led[117],&Led[116],&Led[115],&Led[114],&Led[113],&Led[112],&Led[111],&Led[110],
	&Led[109],&Led[108],&Led[107],&Led[106],&Led[105],&Led[104],&Led[103],&Led[102],&Led[101],&Led[100],
	&Led[99], &Led[98], &Led[97], &Led[96], &Led[95], &Led[94], &Led[93], &Led[92], &Led[91], &Led[90],
	&Led[89], &Led[88], &Led[87], &Led[86], &Led[85], &Led[84], &Led[83], &Led[82], &Led[81], &Led[80],
	&Led[79], &Led[78], &Led[77], &Led[76], &Led[75], &Led[74], &Led[73], &Led[72], &Led[71], &Led[70],
	&Led[69], &Led[68], &Led[67], &Led[66], &Led[65], &Led[64], &Led[63], &Led[62], &Led[61], &Led[60]
};

const TLedRgb* Line2Leds[] = {
	&Led[179],&Led[178],&Led[177],&Led[176],&Led[175],&Led[174],&Led[173],&Led[172],&Led[171],&Led[170],
	&Led[169],&Led[168],&Led[167],&Led[166],&Led[165],&Led[164],&Led[163],&Led[162],&Led[161],&Led[160],
	&Led[159],&Led[158],&Led[157],&Led[156],&Led[155],&Led[154],&Led[153],&Led[152],&Led[151],&Led[150],
	&Led[149],&Led[148],&Led[147],&Led[146],&Led[145],&Led[144],&Led[143],&Led[142],&Led[141],&Led[140],
	&Led[139],&Led[138],&Led[137],&Led[136],&Led[135],&Led[134],&Led[133],&Led[132],&Led[131],&Led[130],
	&Led[129],&Led[128],&Led[127],&Led[126],&Led[125],&Led[124],&Led[123],&Led[122],&Led[121],&Led[120]
};

const TLedRgb* Line3Leds[] = {
	&Led[239],&Led[238],&Led[237],&Led[236],&Led[235],&Led[234],&Led[233],&Led[232],&Led[231],&Led[230],
	&Led[229],&Led[228],&Led[227],&Led[226],&Led[225],&Led[224],&Led[223],&Led[222],&Led[221],&Led[220],
	&Led[219],&Led[218],&Led[217],&Led[216],&Led[215],&Led[214],&Led[213],&Led[212],&Led[211],&Led[210],
	&Led[209],&Led[208],&Led[207],&Led[206],&Led[205],&Led[204],&Led[203],&Led[202],&Led[201],&Led[200],
	&Led[199],&Led[198],&Led[197],&Led[196],&Led[195],&Led[194],&Led[193],&Led[192],&Led[191],&Led[190],
	&Led[189],&Led[188],&Led[187],&Led[186],&Led[185],&Led[184],&Led[183],&Led[182],&Led[181],&Led[180]

};

const TLedRgb* Line4Leds[] = {
	&Led[299],&Led[298],&Led[297],&Led[296],&Led[295],&Led[294],&Led[293],&Led[292],&Led[291],&Led[290],
	&Led[289],&Led[288],&Led[287],&Led[286],&Led[285],&Led[284],&Led[283],&Led[282],&Led[281],&Led[280],
	&Led[279],&Led[278],&Led[277],&Led[276],&Led[275],&Led[274],&Led[273],&Led[272],&Led[271],&Led[270],
	&Led[269],&Led[268],&Led[267],&Led[266],&Led[265],&Led[264],&Led[263],&Led[262],&Led[261],&Led[260],
	&Led[259],&Led[258],&Led[257],&Led[256],&Led[255],&Led[254],&Led[253],&Led[252],&Led[251],&Led[150],
	&Led[249],&Led[248],&Led[247],&Led[246],&Led[245],&Led[244],&Led[243],&Led[242],&Led[241],&Led[240]

};


//-------------------------
class TLedRgbLine LedLine[CO_NUMB_OF_LED_LINES] = {
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 0], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(Line1Leds, CO_NUMB_LEDS_IN_LINE),//TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 1], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 2], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(Line3Leds, CO_NUMB_LEDS_IN_LINE),//TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 3], CO_NUMB_LEDS_IN_LINE),
	TLedRgbLine(&Led[CO_NUMB_LEDS_IN_LINE * 4], CO_NUMB_LEDS_IN_LINE)
};
//-------------------------

class TBargraf Bargraf[CO_NUMB_OF_LED_LINES] = {

	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 0], CO_NUMB_LEDS_IN_LINE),
	TBargraf(Line1Leds, CO_NUMB_LEDS_IN_LINE),	//TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 1], CO_NUMB_LEDS_IN_LINE),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 2], CO_NUMB_LEDS_IN_LINE),
	TBargraf(Line3Leds, CO_NUMB_LEDS_IN_LINE),//TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 3], CO_NUMB_LEDS_IN_LINE),
	TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 4], CO_NUMB_LEDS_IN_LINE)
};
//-------------------------
TBargraf BargrafHalfUp[CO_NUMB_OF_LED_LINES] = {
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 0 + 30],30),
		TBargraf(&Line1Leds[30],30),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 2 + 30],30),
		TBargraf(&Line3Leds[30],30),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 4 + 30],30),
};


TBargraf BargrafHalfDown[CO_NUMB_OF_LED_LINES] = {
		TBargraf(&Line0Leds[30],30),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 1 + 30],30),
		TBargraf(&Line2Leds[30],30),
		TBargraf(&Led[CO_NUMB_LEDS_IN_LINE * 3 + 30],30),
		TBargraf(&Line4Leds[30],30)
};




//---------------------------------------------------------------------------------------------------------------------------------------------------
void TLedRgbLine::fvMoveDown(uint16_t unStep)
{

	for(uint16_t unLedIdx = 0; unLedIdx < unLedTabLenght; unLedIdx++)
	{
		uint16_t unBuf = unLedIdx + unStep;

		if(unBuf >= unLedTabLenght)
		{
			SetBrigtness(unLedIdx,0);
		}
		else
		{
			SetBrigtness(unLedIdx,getBrightness(unBuf));
		}

	}
}




//---------------------------------------------------------------------------------------------------------------------------------------------------
void TLedRgbLine::fvDropEffect()
{


	if(unMode != EN_LED_MODE_DROP)
	{
		unMode = EN_LED_MODE_DROP;
		unTask = 0;
		unDelay = 0;
	}


	if(unDelay)
	{
		unDelay--;
		return;
	}
	else
	{
		fvMoveDown(1);
		unDelay = 0;

	}


	switch(unTask)
	{
		case 0:
		{

			SetBrigtness(0, unLedTabLenght - 1, 0); //wygas wszystkie
			unTask = 1;

		}break;

		case 1:
		{
			SetBrigtness(unLedTabLenght - 1,10);

			//unSecDelay =   rand() %  (4 * CO_DISP_FREQ) ;

			unSecDelay = RandomGen.funGetRandomValue(60, 180);


			unTask = 2;
		}break;

		case 2:
		{

			SetBrigtness(unLedTabLenght - 1,10);
			unTask = 3;
		}break;

		case 3:
		{

			SetBrigtness(unLedTabLenght - 1,10);
			unTask = 4;
		}break;

		case 4:
		{

			SetBrigtness(unLedTabLenght - 1,10);
			unTask = 5;
		}break;


		case 5:
		{

			SetBrigtness(unLedTabLenght - 1,1 *3);
			unTask = 6;
		}break;

		default:
		{
			unTask++;
			if(unTask > unSecDelay)
			{unTask = 1;}
		}break;

		//rand

	}

}



//---------------------------------------------------------------------------------------------------------------------------------------------------
#define CO_PI (3.141692f)
void fvMainLed20ms()
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

				LedLine[unLineIdx].SetBrigtness(0,CO_NUMB_LEDS_IN_LINE,5);

				LedLine[unLineIdx].SetHue(0,CO_NUMB_LEDS_IN_LINE,/*300*/ 75 * unLineIdx);
			}

			unTask = 3;



		}break;

		case 1:
		{

			LedLine[0].fvDropEffect();
			LedLine[1].fvDropEffect();
			LedLine[2].fvDropEffect();
			LedLine[3].fvDropEffect();
			LedLine[4].fvDropEffect();
		}break;



		case 2:
		{
			static uint16_t unPom = 0;
			static float fRadius = 0;

			unPom++;
			if(unPom > 1000)
			{unPom = 0;}

			fRadius += CO_PI/100;


			int16_t nSin =  static_cast<int16_t>( fabs(sin(fRadius)) * 1000 );
			Bargraf[0].fvSetNomralizedTo1000(nSin);


			nSin = static_cast<int16_t>( fabs(sin(fRadius + (1* CO_PI/6) ) ) * 1000 );
			Bargraf[1].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (2* CO_PI/6) ) ) * 1000 );
			Bargraf[2].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>(fabs(sin(fRadius + (3* CO_PI/6) ) ) * 1000 );
			Bargraf[3].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (4* CO_PI/6) ) ) * 1000 );
			Bargraf[4].fvSetNomralizedTo1000(nSin);


		}break;

		case 3:
		{
			static uint16_t unPom = 0;
			static float fRadius = 0;

			unPom++;
			if(unPom > 1000)
			{unPom = 0;}

			fRadius += CO_PI/200;



			int16_t nSin;

/*
			nSin =  static_cast<int16_t>( fabs(sin(fRadius)) * 1000 );
			BargrafHalfUp[0].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[0].fvSetNomralizedTo1000(nSin);

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (1* CO_PI/6) ) ) * 1000 );
			BargrafHalfUp[1].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[1].fvSetNomralizedTo1000(nSin);

*/

			nSin = static_cast<int16_t>( fabs(sin(fRadius + (2* CO_PI/6) ) ) * 1000 );
			BargrafHalfUp[2].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[2].fvSetNomralizedTo1000(nSin);

/*

			nSin = static_cast<int16_t>(fabs(sin(fRadius + (3* CO_PI/6) ) ) * 1000 );
			BargrafHalfUp[3].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[3].fvSetNomralizedTo1000(nSin);


			nSin = static_cast<int16_t>( fabs(sin(fRadius + (4* CO_PI/6) ) ) * 1000 );
			BargrafHalfUp[4].fvSetNomralizedTo1000(nSin);
			BargrafHalfDown[4].fvSetNomralizedTo1000(nSin);
*/




		}break;



	}

	LedLine[0].Refresh();
}








//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
void fvMainLed20ms_1()
{
	static uint16_t unTask = 0;
	static uint16_t unLedNo = 0;


	switch(unTask)
	{

		case 0:
		{
			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{

				for (uint16_t unLedIdx = 0; unLedIdx < CO_NUMB_LEDS_IN_LINE; unLedIdx++)
				{
					LedLine[unLineIdx].SetHue(unLedIdx,unLineIdx * 20);
					LedLine[unLineIdx].SetSaturation(unLedIdx,100);
					LedLine[unLineIdx].fvEnable(unLedIdx);
				}
				LedLine[unLineIdx].Refresh();



			}

			unTask = 1;

		}break;

		case 1:
		{

		for(uint16_t j = 0; j < 4; j++)
		{
			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].SetBrigtness(unLedNo,5);
				LedLine[unLineIdx].Refresh();
			}

			unLedNo++;
			if(unLedNo >= CO_NUMB_LEDS_IN_LINE)
			{
				unLedNo = 0;
				unTask = 2;
				break;
			}
		}

		}break;


		case 2:
		{
			for(uint16_t unLineIdx = 0; unLineIdx < CO_NUMB_OF_LED_LINES; unLineIdx++)
			{
				LedLine[unLineIdx].SetBrigtness(unLedNo,0);
				LedLine[unLineIdx].Refresh();
			}

			unLedNo++;
			if(unLedNo >= CO_NUMB_LEDS_IN_LINE)
			{
				unLedNo = 0;
				unTask = 1;
			}
		}break;

	}



}


