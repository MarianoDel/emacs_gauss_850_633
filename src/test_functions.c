//------------------------------------------------
// #### PROJECT: O3 TREATMENT - Custom Board #####
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.C #########################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "test_functions.h"
#include "hard.h"
#include "tim.h"
#include "gpio.h"
#include "uart.h"

#include <stdio.h>


// Externals -------------------------------------------------------------------
extern volatile unsigned short timer_standby;
extern volatile unsigned char usart1_have_data;



// Globals ---------------------------------------------------------------------


// Module Private Types & Macros -----------------------------------------------


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
void TF_Led (void)
{
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        Wait_ms(1000);
    }
}


void TF_Ctrl_Fan (void)
{
    while (1)
    {
        if (CTRL_FAN)
        {
            LED_OFF;
            CTRL_FAN_OFF;
        }
        else
        {
            LED_ON;
            CTRL_FAN_ON;
        }

        Wait_ms(5000);
    }
}


void TF_Led_Blinking (void)
{
    ChangeLed(2);
        
    while(1)
        UpdateLed();
}


void TF_Usart1_RxTx (void)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }
    
    Usart1Config();

    char s_to_send [100] = { 0 };
    Usart1Send("Ready to test...\n");
    while (1)
    {
        if (usart1_have_data)
        {
            usart1_have_data = 0;
            
            if (LED)
                LED_OFF;
            else
                LED_ON;
            
            Usart1ReadBuffer((unsigned char *) s_to_send, 100);
            Wait_ms(1000);
            Usart1Send(s_to_send);
        }
    }
}


void TF_Usart1_Tx_Single (void)
{
    Usart1Config();

    while (1)
    {
        LED_ON;
        Usart1SendSingle('M');
        Wait_ms(50);
        LED_OFF;
        Wait_ms(1000);
    }
}


void TF_Tim3_Channels (void)
{
    TIM_3_Init();
    
    while (1)
    {
        LED_ON;
        Update_TIM3_CH1(DUTY_20_PERCENT);
        Update_TIM3_CH2(DUTY_70_PERCENT);
        Wait_ms(1000);
        LED_OFF;

        Update_TIM3_CH1(DUTY_NONE);
        Update_TIM3_CH2(DUTY_NONE);
        Wait_ms(1000);
    }
}






//--- end of file ---//
