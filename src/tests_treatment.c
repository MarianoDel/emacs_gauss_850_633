//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    TEST PLATFORM FOR FIRMWARE
// ##
// #### TESTS.C ###############################
//---------------------------------------------

// Includes Modules for tests --------------------------------------------------
#include "treatment.h"
#include "signals.h"
#include "answers.h"
#include "tests_ok.h"

#include <stdio.h>
// #include <stdlib.h>
#include <string.h>


// Externals -------------------------------------------------------------------
treatment_params_t treatment_data;
extern volatile unsigned short timer_treatment;

// Globals ---------------------------------------------------------------------



// Module Auxialiary Functions -------------------------------------------------
void Signal_StopAll (void);
void ChangeLed (unsigned char a);
void Signal_GenerateCWave_Reset (void);

void Test_Treat_Loop (int * current_loop, int max_loops, int out_condition);
// Module Functions for testing ------------------------------------------------
void Test_Treatment_Functions (void);
void Test_Treatment_Assert (void);
    

// Module Functions ------------------------------------------------------------


int main(int argc, char *argv[])
{

    Test_Treatment_Functions ();
    Test_Treatment_Assert();
    
}


void Test_Treatment_Functions (void)
{
    int loop = 0;
    resp_t resp = resp_nok;

    printf("Testing Treatment Reset\n");

    Test_Treat_Loop(&loop, 10, TREATMENT_STANDBY);
    TreatmentManager_Reset();
    printf("Treatment Reset: ");
    if (TreatmentGetState() == TREATMENT_INIT_FIRST_TIME)
        PrintOK();
    else
        PrintERR();


    printf("Testing Treatment Start CWave\n");
    treatment_data.signal = CWAVE_SIGNAL;
    treatment_data.frequency = 1;
    treatment_data.power_red = 10;
    treatment_data.power_ired = 10;    

    TreatmentStop();
    Test_Treat_Loop(&loop, 10, TREATMENT_STANDBY);

    TreatmentStart();
    Test_Treat_Loop(&loop, 10, TREATMENT_GENERATING_CWAVE);
    printf("Treatment Generate CWave: ");
    if (TreatmentGetState() == TREATMENT_GENERATING_CWAVE)
        PrintOK();
    else
        PrintERR();


    printf("Testing Treatment Start Pulsed\n");
    treatment_data.signal = PULSED_SIGNAL;
    treatment_data.frequency = 1;
    treatment_data.power_red = 10;
    treatment_data.power_ired = 10;    

    TreatmentStop();
    Test_Treat_Loop(&loop, 10, TREATMENT_STANDBY);
    
    TreatmentStart();
    Test_Treat_Loop(&loop, 10, TREATMENT_GENERATING_PULSED);    
    printf("Treatment Generate Pulsed: ");
    if (TreatmentGetState() == TREATMENT_GENERATING_PULSED)
        PrintOK();
    else
        PrintERR();


    printf("Testing Treatment Start Triangular\n");
    treatment_data.signal = TRIANGULAR_SIGNAL;
    treatment_data.frequency = 1;
    treatment_data.power_red = 10;
    treatment_data.power_ired = 10;    

    TreatmentStop();
    Test_Treat_Loop(&loop, 10, TREATMENT_STANDBY);

    TreatmentStart();
    Test_Treat_Loop(&loop, 10, TREATMENT_GENERATING_TRIANGULAR);        
    printf("Treatment Generate Triangular: ");
    if (TreatmentGetState() == TREATMENT_GENERATING_TRIANGULAR)
        PrintOK();
    else
        PrintERR();
    

    printf("\n");
}


void Test_Treatment_Assert (void)
{
    printf("Testing Treatment Assert Params no errors: ");
    treatment_data.signal = 0;
    treatment_data.frequency = 1;
    treatment_data.power_red = 10;
    treatment_data.power_ired = 10;    
    if (TreatmentAssertParams() == resp_ok)
    {
        PrintOK();
    }
    else
        PrintERR();

    printf("Testing Treatment Assert Params with freq error: ");
    treatment_data.frequency = 0;    
    if (TreatmentAssertParams() == resp_nok)
    {
        treatment_data.frequency = 11;
        if (TreatmentAssertParams() == resp_nok)
            PrintOK();
        else
            PrintERR();
    }
    else
        PrintERR();


    treatment_data.frequency = 1;
    printf("Testing Treatment Assert Params with power_red error: ");
    treatment_data.power_red = 9;
    if (TreatmentAssertParams() == resp_nok)
    {
        treatment_data.power_red = 101;
        if (TreatmentAssertParams() == resp_nok)
            PrintOK();
        else
            PrintERR();
    }
    else
        PrintERR();


    printf("Testing Treatment Assert Params with power_ired error: ");
    treatment_data.power_ired = 9;
    if (TreatmentAssertParams() == resp_nok)
    {
        treatment_data.power_ired = 101;
        if (TreatmentAssertParams() == resp_nok)
            PrintOK();
        else
            PrintERR();
    }
    else
        PrintERR();


    printf("Testing Treatment Assert Params with power_red shut off: ");
    treatment_data.power_red = 0;
    if (TreatmentAssertParams() == resp_ok)
        PrintOK();
    else
        PrintERR();


    printf("Testing Treatment Assert Params with power_ired shut off: ");
    treatment_data.power_ired = 0;
    if (TreatmentAssertParams() == resp_ok)
        PrintOK();
    else
        PrintERR();
    

    treatment_data.power_ired = 10;
    treatment_data.power_red = 10;    
    printf("Testing Treatment Assert Params with signal error: ");
    treatment_data.signal = 4;
    if (TreatmentAssertParams() == resp_nok)
    {
        PrintOK();
    }
    else
        PrintERR();

    printf("\n");    
}    


void Test_Treat_Loop (int * current_loop, int max_loops, int out_condition)
{
    int start_loop = *current_loop;

    printf("loops start: %d\n", *current_loop);
    do {
        if (timer_treatment)
            timer_treatment = 0;
        
        TreatmentManager();
        printf("loop: %d\n", *current_loop);
        (*current_loop)++;
        if ((start_loop + max_loops) < *current_loop)
        {
            printf("\nquitting loops abnormal cond.!\n");
            break;
        }
    } while (TreatmentGetState() != out_condition);
    
}


void Signal_StopAll (void)
{
    printf("stopping all pwms\n");
}


void ChangeLed (unsigned char a)
{
    switch (a)
    {
    case 0:
        printf("Led on %d state %s\n", a, "LED_NO_BLINKING");
        break;

    case 1:
        printf("Led on %d state %s\n", a, "LED_TREATMENT_STANDBY");        
        break;

    case 2:
        printf("Led on %d state %s\n", a, "LED_TREATMENT_GENERATING");        
        break;

    case 3:
        printf("Led on %d state %s\n", a, "LED_TREATMENT_PAUSED");        
        break;

    case 4:
        printf("Led on %d state %s\n", a, "LED_TREATMENT_BRIDGE_MODE");        
        break;

    default:
        printf("Led on ERROR state!!!\n");
        break;
    }
}



void Signal_GenerateCWave_Reset (void)
{
    printf("reset cwave\n");    
}


void Signal_GenerateCWave (void)
{
    printf("generate cwave\n");    
}


void Signal_GeneratePulsed_Reset (void)
{
    printf("reset pulsed\n");    
}


void Signal_GeneratePulsed (void)
{
    printf("generate pulsed\n");    
}


void Signal_GenerateTriangular_Reset (void)
{
    printf("reset triangular\n");    
}


void Signal_GenerateTriangular (void)
{
    printf("generate triangular\n");    
}

int fan_state = 0;
void FanOn (void)
{
    fan_state = 0;
    printf("FAN in on\n");
}


void FanOff (void)
{
    fan_state = 1;    
    printf("FAN in off\n");    
}


unsigned char FanIsActive (void)
{
    if (fan_state)
        return 1;
    else
        return 0;
}



//--- end of file ---//


