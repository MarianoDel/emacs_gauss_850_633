//----------------------------------------------
// #### PROYECTO GAUSSTEK O3 - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### HARD.C #################################
//----------------------------------------------
#include "hard.h"
#include "stm32f0xx.h"


// Module Private Types & Macros -----------------------------------------------
#define LED_BLINK_ON    LED_ON
#define LED_BLINK_OFF    LED_OFF

// Led Blinking States
typedef enum
{    
    START_BLINKING = 0,
    WAIT_TO_OFF,
    WAIT_TO_ON,
    WAIT_NEW_CYCLE
    
} led_state_t;


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
//for timers or timeouts
volatile unsigned short timer_led = 0;
volatile unsigned char switches_timer = 0;


//for the led
led_state_t led_state = START_BLINKING;
unsigned char blink = 0;
unsigned char how_many_blinks = 0;


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
//cambia configuracion de bips del LED
void ChangeLed (unsigned char how_many)
{
    how_many_blinks = how_many;
    led_state = START_BLINKING;
}


void UpdateLed (void)
{
    switch (led_state)
    {
        case START_BLINKING:
            blink = how_many_blinks;
            
            if (blink)
            {
                LED_BLINK_ON;
                timer_led = 200;
                led_state++;
                blink--;
            }
            break;

        case WAIT_TO_OFF:
            if (!timer_led)
            {
                LED_BLINK_OFF;
                timer_led = 200;
                led_state++;
            }
            break;

        case WAIT_TO_ON:
            if (!timer_led)
            {
                if (blink)
                {
                    blink--;
                    timer_led = 200;
                    led_state = WAIT_TO_OFF;
                    LED_BLINK_ON;
                }
                else
                {
                    led_state = WAIT_NEW_CYCLE;
                    timer_led = 2000;
                }
            }
            break;

        case WAIT_NEW_CYCLE:
            if (!timer_led)
                led_state = START_BLINKING;

            break;

        default:
            led_state = START_BLINKING;
            break;
    }
}


void FanOn (void)
{
    CTRL_FAN_ON;
}


void FanOff (void)
{
    CTRL_FAN_OFF;
}


unsigned char FanIsActive (void)
{
    if (CTRL_FAN)
        return 1;
    else
        return 0;
}


void HARD_Timeouts (void)
{
    if (timer_led)
        timer_led--;

}



//--- end of file ---//


