//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    TEST PLATFORM FOR FIRMWARE
// ##
// #### TESTS.C ###############################
//---------------------------------------------

// Includes Modules for tests --------------------------------------------------
#include "comm.h"
#include "signals.h"

//helper modules
#include "tests_ok.h"
#include "tests_mock_usart.h"

#include <stdio.h>
#include <string.h>


// Externals -------------------------------------------------------------------
extern treatment_params_t treatment_data;

// Globals ---------------------------------------------------------------------


// Module Auxialiary Functions -------------------------------------------------


// Module Functions for testing ------------------------------------------------
void Test_Own_Channel (void);
void Test_Comms (void);
void Test_Signals_Conf (void);
void Test_Frequency_Conf (void);
void Test_PowerRed_Conf (void);
void Test_PowerIRed_Conf (void);
void Test_HardSoft (void);
    

// Module Functions ------------------------------------------------------------


int main(int argc, char *argv[])
{

    Test_Own_Channel ();
    Test_Signals_Conf ();
    Test_Frequency_Conf ();
    Test_PowerRed_Conf ();
    Test_PowerIRed_Conf ();
    Test_HardSoft ();
    
}


void Test_Own_Channel (void)
{
    char * my_channel;

    printf("Set own channel 0 -> 1: ");
    COMM_SetOwnChannel(0);
    my_channel = COMM_GetOwnChannel();
    if (strncmp(my_channel, "ch1", sizeof("ch1") - 1) == 0)
        PrintOK();
    else
        PrintERR();

    printf("Set own channel 6 -> 1: ");    
    COMM_SetOwnChannel(6);
    my_channel = COMM_GetOwnChannel();
    if (strncmp(my_channel, "ch1", sizeof("ch1") - 1) == 0)
        PrintOK();
    else
        PrintERR();

    printf("Set own channel 1: ");    
    COMM_SetOwnChannel(1);
    my_channel = COMM_GetOwnChannel();
    if (strncmp(my_channel, "ch1", sizeof("ch1") - 1) == 0)
        PrintOK();
    else
        PrintERR();

    printf("Set own channel 2: ");    
    COMM_SetOwnChannel(2);
    my_channel = COMM_GetOwnChannel();
    if (strncmp(my_channel, "ch2", sizeof("ch2") - 1) == 0)
        PrintOK();
    else
        PrintERR();

    printf("Set own channel 3: ");    
    COMM_SetOwnChannel(3);
    my_channel = COMM_GetOwnChannel();
    if (strncmp(my_channel, "ch3", sizeof("ch3") - 1) == 0)
        PrintOK();
    else
        PrintERR();

    printf("Set own channel 4: ");    
    COMM_SetOwnChannel(4);
    my_channel = COMM_GetOwnChannel();
    if (strncmp(my_channel, "ch4", sizeof("ch4") - 1) == 0)
        PrintOK();
    else
        PrintERR();

    printf("Set own channel 5: ");    
    COMM_SetOwnChannel(5);
    my_channel = COMM_GetOwnChannel();
    if (strncmp(my_channel, "ch5", sizeof("ch5") - 1) == 0)
        PrintOK();
    else
        PrintERR();
    
}


void Test_Signals_Conf (void)
{
    printf ("\nStart of comms tests on ch1...\n");
    COMM_SetOwnChannel(1);
    
    Usart1FillRxBuffer("ch1 signal cwave\n");
    COMM_UpdateCommunications();

    printf("Signal set cwave: ");
    if (treatment_data.signal == CWAVE_SIGNAL)
        PrintOK();
    else
        PrintERR();

    
    Usart1FillRxBuffer("ch1 signal triangular\n");
    COMM_UpdateCommunications();

    printf("Signal set triangular: ");
    if (treatment_data.signal == TRIANGULAR_SIGNAL)
        PrintOK();
    else
        PrintERR();

    
    Usart1FillRxBuffer("ch1 signal pulsed\n");
    COMM_UpdateCommunications();

    printf("Signal set pulsed: ");
    if (treatment_data.signal == PULSED_SIGNAL)
        PrintOK();
    else
        PrintERR();
    
}


void Test_Frequency_Conf (void)
{
    printf ("\nStart of comms tests on ch2...\n");
    COMM_SetOwnChannel(2);

    treatment_data.frequency = 0xff;
    Usart1FillRxBuffer("ch2 frequency 1\n");
    COMM_UpdateCommunications();
    
    printf("Frequency set 1: ");
    if (treatment_data.frequency == 1)
        PrintOK();
    else
        PrintERR();

    treatment_data.frequency = 0xff;    
    Usart1FillRxBuffer("ch2 frequency 0\n");
    COMM_UpdateCommunications();

    printf("Frequency set 0: ");
    if (treatment_data.frequency == 0xff)
        PrintOK();
    else
        PrintERR();


    treatment_data.frequency = 0xff;    
    Usart1FillRxBuffer("ch2 frequency 10\n");
    COMM_UpdateCommunications();

    printf("Frequency set 10: ");
    if (treatment_data.frequency == 10)
        PrintOK();
    else
        PrintERR();


    treatment_data.frequency = 0xff;    
    Usart1FillRxBuffer("ch2 frequency 25\n");
    COMM_UpdateCommunications();

    printf("Frequency set 25: ");
    if (treatment_data.frequency == 0xff)
        PrintOK();
    else
        PrintERR();
    
}


void Test_PowerRed_Conf (void)
{
    printf ("\nStart of comms tests on ch3...\n");
    COMM_SetOwnChannel(3);

    treatment_data.power_red = 0xff;
    Usart1FillRxBuffer("ch3 power red 0\n");
    COMM_UpdateCommunications();
    
    printf("PowerRed set 0: ");
    if (treatment_data.power_red == 0xff)
        PrintOK();
    else
        PrintERR();


    treatment_data.power_red = 0xff;
    Usart1FillRxBuffer("ch3 power red 10\n");
    COMM_UpdateCommunications();
    
    printf("PowerRed set 10: ");
    if (treatment_data.power_red == 10)
        PrintOK();
    else
        PrintERR();


    treatment_data.power_red = 0xff;
    Usart1FillRxBuffer("ch3 power red 000\n");
    COMM_UpdateCommunications();
    
    printf("PowerRed set 000: ");
    if (treatment_data.power_red == 10)
        PrintOK();
    else
        PrintERR();


    treatment_data.power_red = 0xff;
    Usart1FillRxBuffer("ch3 power red 100\n");
    COMM_UpdateCommunications();
    
    printf("PowerRed set 100: ");
    if (treatment_data.power_red == 100)
        PrintOK();
    else
        PrintERR();

    treatment_data.power_red = 0xff;
    Usart1FillRxBuffer("ch3 power red 255\n");
    COMM_UpdateCommunications();
    
    printf("PowerRed set 255: ");
    if (treatment_data.power_red == 100)
        PrintOK();
    else
        PrintERR();
    
}


void Test_PowerIRed_Conf (void)
{
    printf ("\nStart of comms tests on ch4...\n");
    COMM_SetOwnChannel(4);

    treatment_data.power_ired = 0xff;
    Usart1FillRxBuffer("ch4 power ired 0\n");
    COMM_UpdateCommunications();
    
    printf("PowerIred set 0: ");
    if (treatment_data.power_ired == 0xff)
        PrintOK();
    else
        PrintERR();


    treatment_data.power_ired = 0xff;
    Usart1FillRxBuffer("ch4 power ired 10\n");
    COMM_UpdateCommunications();
    
    printf("PowerIred set 10: ");
    if (treatment_data.power_ired == 10)
        PrintOK();
    else
        PrintERR();


    treatment_data.power_ired = 0xff;
    Usart1FillRxBuffer("ch4 power ired 000\n");
    COMM_UpdateCommunications();
    
    printf("PowerIred set 000: ");
    if (treatment_data.power_ired == 10)
        PrintOK();
    else
        PrintERR();


    treatment_data.power_ired = 0xff;
    Usart1FillRxBuffer("ch4 power ired 100\n");
    COMM_UpdateCommunications();
    
    printf("PowerIred set 100: ");
    if (treatment_data.power_ired == 100)
        PrintOK();
    else
        PrintERR();

    treatment_data.power_ired = 0xff;
    Usart1FillRxBuffer("ch4 power ired 255\n");
    COMM_UpdateCommunications();
    
    printf("PowerIred set 255: ");
    if (treatment_data.power_ired == 100)
        PrintOK();
    else
        PrintERR();
    
}


void Test_HardSoft (void)
{
    printf("Ask for hard soft on ch5\n");
    COMM_SetOwnChannel(5);

    Usart1FillRxBuffer("ch5 hard soft\n");
    COMM_UpdateCommunications();    
}



//--- end of file ---//


