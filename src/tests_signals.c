//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    TEST PLATFORM FOR FIRMWARE
// ##
// #### TESTS.C ###############################
//---------------------------------------------

// Includes Modules for tests --------------------------------------------------
#include "signals.h"
#include "answers.h"
#include "pwm.h"
#include "tests_ok.h"

#include <stdio.h>
// #include <stdlib.h>
#include <string.h>


// Externals -------------------------------------------------------------------
extern treatment_params_t treatment_data;


// Globals ---------------------------------------------------------------------
extern unsigned short timer_signals;


// Module Auxialiary Functions -------------------------------------------------
void Update_TIM3_CH2 (unsigned short pwm);
void Update_TIM3_CH1 (unsigned short pwm);


// Module Functions for testing ------------------------------------------------
void Test_Signals_Functions (void);
void Test_Signals_Waveforms (void);


// Module Functions ------------------------------------------------------------


int main(int argc, char *argv[])
{

    Test_Signals_Functions ();
    Test_Signals_Waveforms ();
    
}


void Test_Signals_Functions (void)
{
    resp_t resp = resp_nok;

    printf("Testing Signal Setters: ");
    if ((SetSignalType(TRIANGULAR_SIGNAL) == resp_ok) &&
        (SetSignalType(CWAVE_SIGNAL) == resp_ok) &&
        (SetSignalType(PULSED_SIGNAL) == resp_ok))
    {
        PrintOK();
    }
    else
        PrintERR();

    printf("Testing Signal Setters with errors: ");
    if ((SetSignalType(10) == resp_nok) &&
        (SetSignalType(255) == resp_nok))
    {
        PrintOK();
    }
    else
        PrintERR();

    printf("Testing Signal Set Triangular: ");
    treatment_data.signal = 0xFF;
    if ((SetSignalType(TRIANGULAR_SIGNAL) == resp_ok) &&
        (treatment_data.signal == TRIANGULAR_SIGNAL))
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing Signal Set Cwave: ");
    treatment_data.signal = 0xFF;
    if ((SetSignalType(CWAVE_SIGNAL) == resp_ok) &&
        (treatment_data.signal == CWAVE_SIGNAL))
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing Signal Set Pulsed: ");
    treatment_data.signal = 0xFF;
    if ((SetSignalType(PULSED_SIGNAL) == resp_ok) &&
        (treatment_data.signal == PULSED_SIGNAL))
    {
        PrintOK();
    }
    else
        PrintERR();
        

    printf("\n");

    printf("Testing Frequency Setter: ");
    if ((SetFrequency(1) == resp_ok) &&
        (SetFrequency(10) == resp_ok))
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing Frequency Setter with errors: ");
    if ((SetFrequency(0) == resp_nok) &&
        (SetFrequency(11) == resp_nok) &&
        (SetFrequency(255) == resp_nok))        
    {
        PrintOK();
    }
    else
        PrintERR();
    
    
    printf("Testing Frequency Set 1: ");
    treatment_data.frequency = 0xFF;
    if ((SetFrequency(1) == resp_ok) &&
        (treatment_data.frequency == 1))
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing Frequency Set 10: ");
    treatment_data.frequency = 0xFF;
    if ((SetFrequency(10) == resp_ok) &&
        (treatment_data.frequency == 10))
    {
        PrintOK();
    }
    else
        PrintERR();

    printf("\n");

    printf("Testing PowerRed Set 0: ");
    treatment_data.power_red = 0xFF;
    if ((SetPowerRed(0) == resp_ok) &&
        (treatment_data.power_red == 10))
    {
        PrintOK();
    }
    else
        PrintERR();

    printf("Testing PowerRed Set 10: ");
    treatment_data.power_red = 0xFF;
    if ((SetPowerRed(10) == resp_ok) &&
        (treatment_data.power_red == 10))
    {
        PrintOK();
    }
    else
        PrintERR();

    
    printf("Testing PowerRed Set 100: ");
    treatment_data.power_red = 0xFF;
    if ((SetPowerRed(100) == resp_ok) &&
        (treatment_data.power_red == 100))
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing PowerRed Set 255: ");
    treatment_data.power_red = 0xFF;
    if ((SetPowerRed(255) == resp_ok) &&
        (treatment_data.power_red == 100))
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing Power conversion 100%: ");    
    if (Signal_Calculate_Pwm_From_Power(100) == DUTY_100_PERCENT)
        PrintOK();
    else
        PrintERR();


    printf("Testing Power conversion 10%: ");    
    if (Signal_Calculate_Pwm_From_Power(10) == DUTY_10_PERCENT)
        PrintOK();
    else
        PrintERR();


    printf("Testing Power conversion 0%: ");    
    if (Signal_Calculate_Pwm_From_Power(0) == DUTY_NONE)
        PrintOK();
    else
        PrintERR();
    
    
}


void Test_Signals_Waveforms (void)
{
    printf("\nTesting Signals Waveforms\n");

    printf("Testing CWave: \n");
    Signal_GenerateCWave_Reset();
    treatment_data.power_red = 100;
    treatment_data.power_ired = 50;

    for (int i = 0; i < 20; i++)
    {
        printf("loop: %d timer_signals: %d\n", i, timer_signals);        
        Signal_GenerateCWave();
    }


    printf("Testing Pulsed: \n");
    Signal_GeneratePulsed_Reset();
    treatment_data.power_red = 100;
    treatment_data.power_ired = 50;
    treatment_data.frequency = 10;

    for (int i = 0; i < 200; i++)
    {
        printf("loop: %d timer_signals: %d\n", i, timer_signals);
        Signal_GeneratePulsed();
        SIGNALS_Timeouts();
    }

    printf("Testing Triangular: \n");
    Signal_GenerateTriangular_Reset();
    treatment_data.power_red = 100;
    treatment_data.power_ired = 50;
    treatment_data.frequency = 10;

    for (int i = 0; i < 200; i++)
    {
        printf("loop: %d timer_signals: %d\n", i, timer_signals);
        Signal_GenerateTriangular();
        SIGNALS_Timeouts();
    }
    
}

void Update_TIM3_CH2 (unsigned short pwm)
{
    printf("TIM3_CH2: %d\n", pwm);
}

void Update_TIM3_CH1 (unsigned short pwm)
{
    printf("TIM3_CH1: %d\n", pwm);
}



//--- end of file ---//


