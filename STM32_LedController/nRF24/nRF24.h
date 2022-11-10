/*
 * nRF24.h
 *
 *  Created on: Apr 26, 2020
 *      Author: Mateusz Salamon
 */

#ifndef INC_NRF24_NRF24_H_
#define INC_NRF24_NRF24_H_

#include "main.h"

void nRF24_Init(SPI_HandleTypeDef *hspi);

//
// READ/WRITE REGISTERS
//
uint8_t nRF24_ReadConfig(void);
void nRF24_WriteConfig(uint8_t conf);
uint8_t nRF24_ReadStatus();
void nRF24_WriteStatus(uint8_t st);

//
// SWITCHING BETWEEN RX AND TX
//
void nRF24_RX_Mode(void);
void nRF24_TX_Mode(void);

//
// RADIO SETTINGS
//
void nRF24_SetPALevel(uint8_t lev);
void nRF24_SetDataRate(uint8_t dr);
void nRF24_EnableCRC(uint8_t onoff);
void nRF24_SetCRCLength(uint8_t crcl);
void nRF24_SetRetries(uint8_t ard, uint8_t arc);
void nRF24_SetRFChannel(uint8_t channel);
void nRF24_SetPayloadSize(uint8_t pipe, uint8_t size);
void nRF24_EnablePipe(uint8_t pipe, uint8_t onoff);
void nRF24_AutoACK(uint8_t pipe, uint8_t onoff);
void nRF24_SetRXAddress(uint8_t pipe, uint8_t* address); // Remember to define RX address before TX
void nRF24_SetTXAddress(uint8_t* address);
void nRF24_SetAddressWidth(uint8_t size);

//
// INTERRUPT CONTROL
//
void nRF24_ClearInterrupts(void);
void nRF24_EnableRXDataReadyIRQ(uint8_t onoff);
void nRF24_EnableTXDataSentIRQ(uint8_t onoff);
void nRF24_EnableMaxRetransmitIRQ(uint8_t onoff);

//
// PUSH/PULL DATA TO PAYLOAD
//
void nRF24_WriteTXPayload(uint8_t* data);
void nRF24_WaitTX();
void nRF24_ReadRXPaylaod(uint8_t* data);

//
// TRANSMITTING DATA
//
void nRF24_SendPacket(uint8_t* data);
void nRF24_ReceivePacket(uint8_t* data);

//
// FLUSHING FIFOs
//
void nRF24_FlushRX(void);
void nRF24_FlushTX(void);

//
// IRQ HANDLER
//
void nRF24_IRQ_Handler(void);

//
// POLLING METHOD
//
uint8_t nRF24_RXAvailible(void);


//------------------------
//#define B1_Pin GPIO_PIN_13
//#define B1_GPIO_Port GPIOC
//#define USART_TX_Pin GPIO_PIN_2
//#define USART_TX_GPIO_Port GPIOA
//#define USART_RX_Pin GPIO_PIN_3
//#define USART_RX_GPIO_Port GPIOA
#define NRF24_CSN_Pin GPIO_PIN_14
#define NRF24_CSN_GPIO_Port GPIOB

/*
#define NRF24_IRQ_Pin GPIO_PIN_9
#define NRF24_IRQ_GPIO_Port GPIOA
#define NRF24_IRQ_EXTI_IRQn EXTI9_5_IRQn
*/

//#define TMS_Pin GPIO_PIN_13
//#define TMS_GPIO_Port GPIOA
//#define TCK_Pin GPIO_PIN_14
//#define TCK_GPIO_Port GPIOA
//#define SWO_Pin GPIO_PIN_3
//#define SWO_GPIO_Port GPIOB
#define NRF24_CE_Pin GPIO_PIN_13
#define NRF24_CE_GPIO_Port GPIOB
//------------------------


#endif /* INC_NRF24_NRF24_H_ */
