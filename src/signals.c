//----------------------------------------------------
// #### GAUSS 850-633nm Controller - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### SIGNALS.C ####################################
//----------------------------------------------------

// Includes --------------------------------------------------------------------
#include "signals.h"
#include "pwm.h"
#include "uart.h"


// Private Types Constants and Macros ------------------------------------------


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
treatment_params_t treatment_data;
unsigned short timer_reload;
volatile unsigned short timer_signals = 0;



// Private Module Functions ------------------------------
unsigned short Signal_Calculate_Pwm_From_Power (unsigned char power);
void SetPower (unsigned char * which_color, unsigned char power);


// Module Functions ------------------------------------------------------------
resp_t SetSignalType (signal_type_e signal)
{
    resp_t r = resp_ok;
    
    // if ((treatment_state != TREATMENT_INIT_FIRST_TIME) && (treatment_state != TREATMENT_STANDBY))
    //     return resp_error;

    if ((signal == CWAVE_SIGNAL) ||
        (signal == PULSED_SIGNAL) ||
        (signal == TRIANGULAR_SIGNAL))
    {
        treatment_data.signal = signal;
    }
    else
        r = resp_nok;

    return r;
}

//setea la frecuencia y el timer con el que se muestrea
//por default o error es simepre de 1500Hz -> seniales de 10Hz
resp_t SetFrequency (unsigned char freq)
{
    resp_t r = resp_ok;
    
    // if ((treatment_state != TREATMENT_INIT_FIRST_TIME) && (treatment_state != TREATMENT_STANDBY))
    //     return resp_error;

    if ((freq >= MIN_FREQ_ALLOWED) && (freq <= MAX_FREQ_ALLOWED))
    {
        treatment_data.frequency = freq;
    }
    else
        r = resp_nok;
        
    return r;
}

resp_t SetPowerRed (unsigned char a)
{
    SetPower(&treatment_data.power_red, a);
    return resp_ok;
}


resp_t SetPowerIRed (unsigned char a)
{
    SetPower(&treatment_data.power_ired, a);
    return resp_ok;
}


void SetPower (unsigned char * which_color, unsigned char power)
{
    // channel power off?
    if (power == 0)
        *which_color = 0;
    else
    {
        if (power > 100)
            *which_color = 100;
        else if (power < 10)
            *which_color = 10;
        else
            *which_color = power;
    }
}


void Signal_StopAll (void)
{
    PWM_Update_R(0);
    PWM_Update_IR(0);
}


typedef enum {
    wave_init,
    wave_ton,
    wave_toff
    
} wave_state_e;


wave_state_e wave_state = wave_init;
void Signal_GenerateCWave_Reset (void)
{
    wave_state = wave_init;
}


void Signal_GenerateCWave (void)
{
    unsigned short pwm_red = 0;
    unsigned short pwm_ired = 0;

    switch (wave_state)
    {
    case wave_init:
        pwm_red = Signal_Calculate_Pwm_From_Power (treatment_data.power_red);
        pwm_ired = Signal_Calculate_Pwm_From_Power (treatment_data.power_ired);        
        PWM_Update_R(pwm_red);
        PWM_Update_IR(pwm_ired);
        wave_state++;
        break;

    case wave_ton:
        break;

    default:
        wave_state = wave_init;
        break;
    
    }
}


void Signal_GeneratePulsed_Reset (void)
{
    wave_state = wave_init;
}


void Signal_GeneratePulsed (void)
{
    switch (wave_state)
    {
    case wave_init:
        if (treatment_data.frequency)
            timer_reload = 1000 / treatment_data.frequency;
        else
            timer_reload = 1000;    //one second default

        timer_reload >>= 1;    //50% duty

        //first cycle by toff
        timer_signals = 0;
        wave_state = wave_toff;
        break;

    case wave_ton:
        if (!timer_signals)
        {
            PWM_Update_R(0);
            PWM_Update_IR(0);
            timer_signals = timer_reload;
            wave_state++;
        }
        break;

    case wave_toff:
        if (!timer_signals)
        {
            unsigned short pwm_red = Signal_Calculate_Pwm_From_Power (treatment_data.power_red);
            unsigned short pwm_ired = Signal_Calculate_Pwm_From_Power (treatment_data.power_ired);        
            PWM_Update_R(pwm_red);
            PWM_Update_IR(pwm_ired);
            
            timer_signals = timer_reload;
            wave_state = wave_ton;
        }
        break;
        
    default:
        wave_state = wave_init;
        break;
    
    }

    //fuzzy synchro
#ifdef USE_FUZZY_SYNCHRO
    if (wave_state >= wave_ton)
    {
        if (Usart1SynchroGetted())
        {
            Usart1SynchroReset();
            timer_signals = 0;
            wave_state = wave_toff;
        }
    }
#endif
    
}


void Signal_GenerateTriangular_Reset (void)
{
    wave_state = wave_init;
}


#define wave_rising_edge    wave_ton
#define wave_falling_edge    wave_toff
unsigned char edges_cnt = 0;
void Signal_GenerateTriangular (void)
{
    switch (wave_state)
    {
    case wave_init:
        if (treatment_data.frequency)
            timer_reload = 1000 / (treatment_data.frequency * 100);    //100 points in the edges
        else
            timer_reload = 10;    //one second default

        timer_reload >>= 1;    //50% duty

        //first cycle by toff
        timer_signals = 0;
        edges_cnt = 0;
        wave_state = wave_rising_edge;
        break;

    case wave_rising_edge:
        if (!timer_signals)
        {
            if (edges_cnt < 50)
            {                
                unsigned short slope_red = treatment_data.power_red * edges_cnt;
                unsigned short slope_ired = treatment_data.power_ired * edges_cnt;
                slope_red = slope_red / 50;
                slope_ired = slope_ired / 50;
                
                unsigned short pwm_red = Signal_Calculate_Pwm_From_Power (slope_red);
                unsigned short pwm_ired = Signal_Calculate_Pwm_From_Power (slope_ired);        
                PWM_Update_R(pwm_red);
                PWM_Update_IR(pwm_ired);

                timer_signals = timer_reload;
                edges_cnt++;
            }
            else
            {
                edges_cnt = 0;
                wave_state = wave_falling_edge;
            }
        }
        break;

    case wave_falling_edge:
        if (!timer_signals)
        {
            if (edges_cnt < 50)
            {                
                unsigned short slope_red = treatment_data.power_red * (50 - edges_cnt);
                unsigned short slope_ired = treatment_data.power_ired * (50 - edges_cnt);
                slope_red = slope_red / 50;
                slope_ired = slope_ired / 50;
                
                unsigned short pwm_red = Signal_Calculate_Pwm_From_Power (slope_red);
                unsigned short pwm_ired = Signal_Calculate_Pwm_From_Power (slope_ired);        
                PWM_Update_R(pwm_red);
                PWM_Update_IR(pwm_ired);

                timer_signals = timer_reload;
                edges_cnt++;
            }
            else
            {
                edges_cnt = 0;
                wave_state = wave_rising_edge;
            }
        }
        break;
        
    default:
        wave_state = wave_init;
        break;
    
    }

    //fuzzy synchro
#ifdef USE_FUZZY_SYNCHRO
    if (wave_state >= wave_rising_edge)
    {
        if (Usart1SynchroGetted())
        {
            Usart1SynchroReset();
            timer_signals = 0;
            edges_cnt = 0;
            wave_state = wave_rising_edge;
        }
    }
#endif
}


unsigned short Signal_Calculate_Pwm_From_Power (unsigned char power)
{
    unsigned int calc = 0;
    calc = power * DUTY_100_PERCENT;
    calc = calc / 100;

    return (unsigned short) calc;
}


void SIGNALS_Timeouts (void)
{
    if (timer_signals)
        timer_signals--;
}
//--- end of file ---//
