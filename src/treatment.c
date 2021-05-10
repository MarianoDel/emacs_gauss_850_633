//----------------------------------------------------
// #### GAUSS 850-633nm Controller - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TREATMENT.C ##################################
//----------------------------------------------------

// Includes --------------------------------------------------------------------
#include "treatment.h"
#include "signals.h"
#include "hard.h"


// Private Types Constants and Macros ------------------------------------------


// Externals -------------------------------------------------------------------
extern treatment_params_t treatment_data;

// Globals ---------------------------------------------------------------------
treatment_state_e treat_state;
volatile unsigned short timer_treatment = 0;



// Private Module Functions ----------------------------------------------------
resp_t TreatmentAssertParams (void);


// Module Functions ------------------------------------------------------------
void TreatmentManager_Reset (void)
{
    treat_state = TREATMENT_INIT_FIRST_TIME;
}


void TreatmentManager (void)
{
    switch (treat_state)
    {
        case TREATMENT_INIT_FIRST_TIME:
            Signal_StopAll();
            ChangeLed(LED_TREATMENT_STANDBY);
            treat_state++;
            break;

        case TREATMENT_STANDBY:
            break;

        case TREATMENT_START_TO_GENERATE:    
            if (treatment_data.signal == CWAVE_SIGNAL)
            {
                Signal_GenerateCWave_Reset();
                treat_state = TREATMENT_GENERATING_CWAVE;
            }

            if (treatment_data.signal == PULSED_SIGNAL)
            {
                Signal_GeneratePulsed_Reset();                
                treat_state = TREATMENT_GENERATING_PULSED;
            }

            if (treatment_data.signal == TRIANGULAR_SIGNAL)
            {
                Signal_GenerateTriangular_Reset();
                treat_state = TREATMENT_GENERATING_TRIANGULAR;
            }

            ChangeLed(LED_TREATMENT_GENERATING);
            break;

        case TREATMENT_GENERATING_CWAVE:
            Signal_GenerateCWave();
            break;

        case TREATMENT_GENERATING_PULSED:
            Signal_GeneratePulsed();
            break;

        case TREATMENT_GENERATING_TRIANGULAR:
            Signal_GenerateTriangular();
            break;
            
        case TREATMENT_STOPPING:
            Signal_StopAll();
            
            timer_treatment = 1000;
            treat_state = TREATMENT_STOPPING2;
            break;

        case TREATMENT_STOPPING2:
            if (!timer_treatment)
                treat_state = TREATMENT_INIT_FIRST_TIME;

            break;

        default:
            treat_state = TREATMENT_INIT_FIRST_TIME;
            break;
    }
}


treatment_state_e TreatmentGetState (void)
{
    return treat_state;
}


resp_t TreatmentStart (void)
{
    if (treat_state == TREATMENT_STANDBY)
    {
        if (TreatmentAssertParams() == resp_ok)
        {
            treat_state = TREATMENT_START_TO_GENERATE;
            return resp_ok;
        }
    }
    
    return resp_error;
}


void TreatmentStop (void)
{
    if (treat_state != TREATMENT_STANDBY)
        treat_state = TREATMENT_STOPPING;
}


resp_t TreatmentAssertParams (void)
{
    resp_t resp = resp_nok;

    if ((treatment_data.frequency < MIN_FREQ_ALLOWED) ||
        (treatment_data.frequency > MAX_FREQ_ALLOWED))
        return resp;

    if ((treatment_data.signal != CWAVE_SIGNAL) &&
        (treatment_data.signal != PULSED_SIGNAL) &&
        (treatment_data.signal != TRIANGULAR_SIGNAL))
        return resp;

    if ((treatment_data.power_red < MIN_POWER_ALLOWED) ||
        (treatment_data.power_red > MAX_POWER_ALLOWED))
        return resp;

    if ((treatment_data.power_ired < MIN_POWER_ALLOWED) ||
        (treatment_data.power_ired > MAX_POWER_ALLOWED))
        return resp;
    
    return resp_ok;
    
}


void TREATMENT_Timeouts (void)
{
    if (timer_treatment)
        timer_treatment--;
}
//--- end of file ---//
