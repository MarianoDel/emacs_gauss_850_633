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


// Globals ---------------------------------------------------------------------



// Module Auxialiary Functions -------------------------------------------------
void Signal_StopAll (void);
void ChangeLed (unsigned char a);
void Signal_GenerateCWave_Reset (void);


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
    do {
        TreatmentManager();
        printf("loop num: %d\n", loop);
        loop++;
    } while (TreatmentGetState() == TREATMENT_INIT_FIRST_TIME);

    TreatmentManager_Reset();
    printf("Treatment Reset: ");
    if (TreatmentGetState() == TREATMENT_INIT_FIRST_TIME)
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing Treatment Start CWave\n");
    treatment_data.signal = CWAVE_SIGNAL;
    treatment_data.frequency = 1;
    treatment_data.power_red = 10;
    treatment_data.power_ired = 10;    
    
    do {
        TreatmentManager();
        printf("loop num: %d\n", loop);
        loop++;
    } while (TreatmentGetState() == TREATMENT_INIT_FIRST_TIME);


    TreatmentStart();
    do {
        TreatmentManager();
        printf("loop num: %d\n", loop);
        loop++;
    } while (TreatmentGetState() != TREATMENT_GENERATING_CWAVE);

    printf("Treatment Generate CWave: ");
    if (TreatmentGetState() == TREATMENT_GENERATING_CWAVE)
    {
        PrintOK();
    }
    else
        PrintERR();


    printf("Testing Treatment Start Pulsed\n");
    treatment_data.signal = PULSED_SIGNAL;
    treatment_data.frequency = 1;
    treatment_data.power_red = 10;
    treatment_data.power_ired = 10;    
    
    do {
        TreatmentManager();
        printf("loop num: %d\n", loop);
        loop++;
    } while (TreatmentGetState() == TREATMENT_INIT_FIRST_TIME);


    TreatmentStart();
    do {
        TreatmentManager();
        printf("loop num: %d\n", loop);
        loop++;
    } while ((TreatmentGetState() != TREATMENT_GENERATING_PULSED);

    printf("Treatment Generate Pulsed: ");
    if (TreatmentGetState() == TREATMENT_GENERATING_PULSED)
    {
        PrintOK();
    }
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


void Signal_StopAll (void)
{
    printf("stopping all pwms\n");
}


void ChangeLed (unsigned char a)
{
    printf("Led on %d state\n", a);
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


//--- end of file ---//


