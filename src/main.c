//----------------------------------------------------
// #### GAUSS 850-633nm Controller - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### MAIN.C #######################################
//----------------------------------------------------

// Includes --------------------------------------------------------------------
#include "hard.h"
#include "stm32f0xx.h"
#include "gpio.h"

#include "core_cm0.h"
#include "tim.h"

#include "comm.h"
#include "treatment.h"
#include "signals.h"
// #include "flash_program.h"
// #include "dsp.h"

#include "answers.h"
#include "test_functions.h"
#include "parameters.h"
#include "pwm.h"

#include "uart.h"

#include <stdio.h>
#include <string.h>


// Module Types Constants and Macros -------------------------------------------


// Externals -------------------------------------------------------------------
volatile unsigned char usart1_have_data = 0;


// Globals ---------------------------------------------------------------------
//-- Timers globals ----------------------------------
volatile unsigned short timer_standby = 0;
volatile unsigned short wait_ms_var = 0;


// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
void SysTickError (void);


// Module Functions ------------------------------------------------------------
int main(void)
{
    //GPIO Configuration.
    GPIO_Config();

    //Systick Timer
    if (SysTick_Config(48000))
        SysTickError();

    // Begin Hardware Tests - check test_functions module
    // TF_Led();    //simple led functionality
    // TF_Led_Blinking ();
    // TF_Ctrl_Fan ();
    // TF_Usart1_Tx_Single ();
    // TF_Tim3_Channels ();
    

    // End Hard Tests -------------------------------

    
    // Production Program ---------------------------
    // Start the Hardware
    TIM_3_Init();
    PWM_Update_R (DUTY_NONE);
    PWM_Update_IR (DUTY_NONE);

    Usart1Config();

    // Start the firmware
    COMM_SetOwnChannel(MY_OWN_CHANNEL);
    
    TreatmentManager_Reset();

    while (1)
    {
        TreatmentManager();

        UpdateLed();

        COMM_UpdateCommunications();
    }

    return 0;
}

//--- End of Main ---//



void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

    HARD_Timeouts();

    SIGNALS_Timeouts();

    TREATMENT_Timeouts();

}


void SysTickError (void)
{
    //Capture systick error...
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        for (unsigned char i = 0; i < 255; i++)
        {
            asm ("nop \n\t"
                 "nop \n\t"
                 "nop \n\t" );
        }
    }
}

//--- end of file ---//

