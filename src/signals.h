//----------------------------------------------------
// #### GAUSS 850-633nm Controller - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### SIGNALS.H ####################################
//----------------------------------------------------
#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include "answers.h"

// Module Exported Types Constants and Macros ----------------------------------
typedef enum {
    CWAVE_SIGNAL = 0,
    PULSED_SIGNAL,
    TRIANGULAR_SIGNAL

} signal_type_e;


typedef struct {
    signal_type_e signal;

    unsigned char frequency;

    unsigned char power_red;
    unsigned char power_ired;
    
} treatment_params_t;


#define MIN_FREQ_ALLOWED    1
#define MAX_FREQ_ALLOWED    10
#define MIN_POWER_ALLOWED    10
#define MAX_POWER_ALLOWED    100


// Module Exported Functions ---------------------------------------------------
// Setters
resp_t SetSignalType (signal_type_e signal);
resp_t SetFrequency (unsigned char freq);
resp_t SetPowerRed (unsigned char pwr_r);
resp_t SetPowerIRed (unsigned char pwr_ir);
void Signal_StopAll (void);

// void GenerateSignalReset (void);

// resp_t AssertTreatmentParams (void);
// resp_t StartTreatment (void);
// void StopTreatment (void);
// error_t GetErrorStatus (void);
// void SetErrorStatus (error_t);
// void SendAllConf (void);
// void TreatmentManager (void);
// void Overcurrent_Shutdown (void);
// void TreatmentManager_IntSpeed (void);

// treatment_t GetTreatmentState (void);
// gen_signal_state_t GetGenSignalState (void);

#endif    /* _SIGNALS_H_ */

//--- end of file ---//

