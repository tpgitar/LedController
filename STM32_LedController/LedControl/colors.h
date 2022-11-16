/*
 * colors.h
 *
 *  Created on: 28.10.2021
 *      Author: Laptop
 */

#ifndef COLORS_H_
#define COLORS_H_

#include "stdlib.h"
#include "stdio.h"


#define CO_COLOR_5_ORANGE				5
#define CO_COLOR_7_ORANGE				7
#define CO_COLOR_8_ORANGE				8
#define CO_COLOR_10_ORANGE				10

#define CO_COLOR_15_YELLOW				15
#define CO_COLOR_20_YELLOW				20
#define CO_COLOR_23_YELLOW				23
#define CO_COLOR_25_YELLOW				23
#define CO_COLOR_30_YELLOW				30
#define CO_COLOR_33_YELLOW				33

#define CO_COLOR_35_YELLOW_GR			35
#define CO_COLOR_40_YELLO_GR			40

#define CO_COLOR_50_GREEN				50
#define CO_COLOR_60_GREEN				60
#define CO_COLOR_70_GREEN				70
#define CO_COLOR_80_GREEN				80
#define CO_COLOR_90_GREEN				90
#define CO_COLOR_100_GREEN				100
#define CO_COLOR_110_GREEN				110
#define CO_COLOR_120_GREEN				120
#define CO_COLOR_124_GREEN_BL			124  //!!

#define CO_COLOR_130_BLUE_GR			130
#define CO_COLOR_140_BLUE_BRIGHT		140
#define CO_COLOR_150_BLUE_BRIGHT		150
#define CO_COLOR_160_BLUE_BRIGHT		160
#define CO_COLOR_170_BLUE				170
#define CO_COLOR_180_BLUE				180
#define CO_COLOR_190_BLUE				190
#define CO_COLOR_200_BLUE				200
#define CO_COLOR_200_BLUE				200
#define CO_COLOR_210_BLUE				210
#define CO_COLOR_220_BLUE				220
#define CO_COLOR_230_BLUE				230
#define CO_COLOR_240_BLUE_STRONG		240
#define CO_COLOR_250_BLUE_PURPL			250

#define CO_COLOR_260_PURPL_BLUE			260
#define CO_COLOR_270_PURPLE_BRIGHT		270
#define CO_COLOR_280_PURPLE				280
#define CO_COLOR_290_PURPLE				290
#define CO_COLOR_300_PURPLE				300
#define CO_COLOR_300_PURPLE				300
#define CO_COLOR_310_PURPLE				310
#define CO_COLOR_320_PURPLE				320
#define CO_COLOR_330_PURPLE				330
#define CO_COLOR_340_PURPLE_STRONG		340
#define CO_COLOR_350_PINK				350

#define CO_COLOR_358_RED				358
#define CO_COLOR_359_RED				359
#define CO_COLOR_360_RED				360
#define CO_COLOR_0_RED					0
#define CO_COLOR_1_RED					1
#define CO_COLOR_2_RED					2
#define CO_COLOR_3_RED					3
#define CO_COLOR_4_RED					4



struct def_color_srt
{
	const uint16_t* pColorTab;
	const uint16_t unNumbOfColors;
};


extern const uint16_t ColorTab[];
extern uint16_t funGetSizeofColorTab();
extern const struct def_color_srt ColorStructStandard;
extern const struct def_color_srt ColorStructDark;





#endif /* COLORS_H_ */
