//----------------------------------------------------
// #### GAUSS 850-633nm Controller - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### COMM.C #######################################
//----------------------------------------------------

#include "comm.h"
#include "signals.h"
#include "answers.h"
#include "uart.h"

#include "hard.h"    //for hard soft

#include "utils.h"

#include <string.h>
#include <stdio.h>


// Module Private Types Constants and Macros -----------------------------------
//strings de comienzo o lineas intermedias
const char s_ch1 [] = {"ch1"};
const char s_ch2 [] = {"ch2"};
const char s_ch3 [] = {"ch3"};
const char s_ch4 [] = {"ch4"};
const char s_ch5 [] = {"ch5"};
const char s_chf [] = {"chf"};

//--- Available Settings
const char s_set_signal [] = {"signal"};
const char s_frequency [] = {"frequency"};
const char s_power_red [] = {"power red"};
const char s_power_ired [] = {"power ired"};

//--- Available Signals
const char s_cwave [] = {"cwave"};
const char s_pulsed [] = {"pulsed"};
const char s_triangular [] = {"triangular"};

const char s_start_treatment [] = {"start treatment"};
const char s_stop_treatment [] = {"stop treatment"};
const char s_status [] = {"status"};
const char s_getall [] = {"get all conf"};
const char s_soft_version [] = {"soft version"};


// Externals -------------------------------------------------------------------
//--- from uart
extern unsigned char usart1_have_data;

// Globals ---------------------------------------------------------------------
char buffMessages [100];
const char * p_own_channel;



// Module functions ------------------------------------------------------------
void COMM_SetOwnChannel (unsigned char own_ch)
{
    switch (own_ch)
    {
    case 1:
        p_own_channel = s_ch1;
        break;

    case 2:
        p_own_channel = s_ch2;
        break;

    case 3:
        p_own_channel = s_ch3;
        break;

    case 4:
        p_own_channel = s_ch4;
        break;

    case 5:
        p_own_channel = s_ch5;
        break;

    default:
        p_own_channel = s_ch1;
        break;
    }
}


char * COMM_GetOwnChannel (void)
{
    return (char *) p_own_channel;
}


void COMM_UpdateCommunications (void)
{
    unsigned char bytes_readed = 0;
    
    if (usart1_have_data)
    {
        usart1_have_data = 0;
        bytes_readed = Usart1ReadBuffer((unsigned char *) buffMessages, sizeof(buffMessages));
        if (bytes_readed > 2)
            COMM_ProcessMsg();
    }
}


void COMM_ProcessMsg (void)
{
    resp_t resp = resp_nok;
    unsigned char broadcast = 0;
    char * pStr = buffMessages;
    char b [30];

    //broadcast or own channel
    if ((strncmp(pStr, p_own_channel, sizeof(s_chf) - 1) == 0) ||
        (strncmp(pStr, s_chf, sizeof(s_chf) - 1) == 0))
    {
        resp = resp_ok;

        //its broadcast?
        if (*(pStr + 2) == 'f')
            broadcast = 1;

        pStr += sizeof(s_chf);    // payload normalize

        //-- Signal Setting
        if (strncmp(pStr, s_set_signal, sizeof(s_set_signal) - 1) == 0)
        {
            pStr += sizeof(s_set_signal);    // payload normalize

            //cwave
            if (strncmp(pStr, s_cwave, sizeof(s_cwave) - 1) == 0)
            {
                resp = SetSignalType (CWAVE_SIGNAL);
            }

            //triangular
            else if (strncmp(pStr, s_triangular, sizeof(s_triangular) - 1) == 0)
            {
                resp = SetSignalType (TRIANGULAR_SIGNAL);
            }

            //pulsed
            else if (strncmp(pStr, s_pulsed, sizeof(s_pulsed) - 1) == 0)
            {
                resp = SetSignalType (PULSED_SIGNAL);
            }
            else
                resp = resp_error;
        }

        //-- Frequency Setting
        else if (strncmp(pStr, s_frequency, sizeof(s_frequency) - 1) == 0)
        {
            pStr += sizeof(s_frequency);		//normalizo al payload, hay un espacio

            //lo que viene es E o EE
            unsigned short new_freq = 0;
            unsigned char digits = 0;

            digits = StringIsANumber(pStr, &new_freq);

            if ((digits) && (digits < 3))
            {
                resp = SetFrequency ((unsigned char) new_freq);
            }
            else
                resp = resp_error;            

        }

        //-- Power Red Setting
        else if (strncmp(pStr, s_power_red, sizeof(s_power_red) - 1) == 0)
        {
            pStr += sizeof(s_power_red);		//normalizo al payload, hay un espacio

            //lo que viene son 2 o 3 bytes
            unsigned short new_power = 0;
            unsigned char digits = 0;

            digits = StringIsANumber(pStr, &new_power);
            if ((digits > 1) && (digits < 4))
            {
                resp = SetPowerRed ((unsigned char) new_power);
            }
            else
                resp = resp_error;
        }

        //-- Power IRed Setting
        else if (strncmp(pStr, s_power_ired, sizeof(s_power_ired) - 1) == 0)
        {
            pStr += sizeof(s_power_ired);		//normalizo al payload, hay un espacio

            //lo que viene son 2 o 3 bytes
            unsigned short new_power = 0;
            unsigned char digits = 0;

            digits = StringIsANumber(pStr, &new_power);
            if ((digits > 1) && (digits < 4))
            {
                resp = SetPowerIRed ((unsigned char) new_power);
            }
            else
                resp = resp_error;
        }
        
        // //-- Start Treatment
        // else if (strncmp(pStr, s_start_treatment, sizeof(s_start_treatment) - 1) == 0)
        // {
        //     //se puede empezar
        //     if (GetTreatmentState() == TREATMENT_STANDBY)
        //     {
        //         resp = StartTreatment();
        //     }
        //     else
        //         resp = resp_error;
        // }

        // //-- Stop Treatment
        // else if (strncmp(pStr, s_stop_treatment, sizeof(s_stop_treatment) - 1) == 0)
        // {
        //     StopTreatment();
        // }

        //-- Soft Version
        else if (!strncmp(pStr, "hard soft", sizeof("hard soft") - 1))
        {
            char to_send [80];
            sprintf(to_send, "%s\r\n%s\r\n", HARD, SOFT);
            Usart1Send(to_send);
        }
        
        // else if (strncmp(pStr, s_soft_version, sizeof(s_soft_version) - 1) == 0)
        // {
        //     sprintf(b,"[%s] %s\n", __FILE__, xstr_macro(SOFT_ANNOUNCEMENT));
        //     Usart1Send(b);
        // }


        // //-- Get All Configuration
        // else if (strncmp(pStr, s_getall, sizeof(s_getall) - 1) == 0)
        // {
        //     SendAllConf();
        // }

        // //-- Ninguno de los anteriores
        else
            resp = resp_error;

    }	//fin if chx

    if (!broadcast)
    {
        if (resp == resp_ok)
            Usart1Send("OK\n");

        if (resp == resp_error)
            Usart1Send("NOK\n");
    }

    // return resp;
}

//--- end of file ---//
