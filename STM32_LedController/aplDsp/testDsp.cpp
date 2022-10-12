//#define ARM_MATH_CM4

#include <arm_math.h>


/* USER CODE BEGIN PV */
float32_t FFT_Input_Q15_f[50];
float32_t aFFT_Input_Q15[50];
/* USER CODE END PV */

/* USER CODE BEGIN PD */
#define FFT_Length 50
/* USER CODE END PD */





/* USER CODE BEGIN 1 */
//	arm_float_to_q15((float32_t *)&FFT_Input_Q15_f[0], (q15_t *)&aFFT_Input_Q15[0], FFT_Length*2);
/* USER CODE END 1 */

void fvTEst()
{
	arm_float_to_q15((float32_t *)&FFT_Input_Q15_f[0], (q15_t *)&aFFT_Input_Q15[0], FFT_Length*2);
	//arm_rfft_fast_f32(S, p, pOut, 0)
}



