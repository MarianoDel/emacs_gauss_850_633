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
#include "tests_ok.h"

#include <stdio.h>
// #include <stdlib.h>
#include <string.h>


// Externals -------------------------------------------------------------------
extern treatment_params_t treatment_data;


// Globals ---------------------------------------------------------------------



// Module Auxialiary Functions -------------------------------------------------


// Module Functions for testing ------------------------------------------------
void Test_Signals_Functions (void);
    

// Module Functions ------------------------------------------------------------


int main(int argc, char *argv[])
{

    Test_Signals_Functions ();
    
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
    
    
    
    
           
    
}




//--- end of file ---//


