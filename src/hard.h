//----------------------------------------------
// #### DEXEL 2CH PROJECT - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### HARD.H #################################
//----------------------------------------------
#ifndef _HARD_H_
#define _HARD_H_

#include "stm32f0xx.h"


//-- Defines For Configuration -------------------
//---- Configuration for Hardware Versions -------
#define HARDWARE_VERSION_1_0    //micro F030K6T6


// #define SOFTWARE_VERSION_1_1
#define SOFTWARE_VERSION_1_0


//---- Features Configuration -----------------


//---- End of Features Configuration ----------


// Exported Pinout Names -------------------------------------------------------
#ifdef HARDWARE_VERSION_1_0
//GPIOA pin0    
//GPIOA pin1    
//GPIOA pin2    NC

//GPIOA pin3    
#define CTRL_FAN    ((GPIOA->ODR & 0x0008) != 0)
#define CTRL_FAN_ON    (GPIOA->BSRR = 0x00000008)
#define CTRL_FAN_OFF    (GPIOA->BSRR = 0x00080000)

//GPIOA pin4
//GPIOA pin5    NC

//GPIOA pin6    TIM3_CH1 CH_IR
//GPIOA pin7    TIM3_CH2 CH_R

//GPIOB pin0    
#define LED    ((GPIOB->ODR & 0x0001) != 0)
#define LED_ON    (GPIOB->BSRR = 0x00000001)
#define LED_OFF    (GPIOB->BSRR = 0x00010000)

//GPIOB pin1    NC

//GPIOA pin8    NC

//GPIOA pin9    Usart1 Tx
//GPIOA pin10    Usart1 Rx

//GPIOA pin11    
//GPIOA pin12
//GPIOA pin13
//GPIOA pin14
//GPIOA pin15    NC

//GPIOB pin3
//GPIOB pin4
//GPIOB pin5
//GPIOB pin6
//GPIOB pin7    NC

#endif    //HARDWARE_VER_1_0

// Exported Types & Macros -----------------------------------------------------

//Estados Externos de LED BLINKING
#define LED_NO_BLINKING    0
#define LED_TREATMENT_STANDBY    1
#define LED_TREATMENT_GENERATING    2
#define LED_TREATMENT_PAUSED    3
#define LED_NO_RFID    4

#define CH1_VAL_OFFSET    0
#define CH2_VAL_OFFSET    1

//--- Stringtify Utils -----------------------
#define str_macro(s) #s


// Module Exported Functions ---------------------------------------------------
void HARD_Timeouts (void);

void ChangeLed (unsigned char);
void UpdateLed (void);


#endif /* _HARD_H_ */

//--- end of file ---//

