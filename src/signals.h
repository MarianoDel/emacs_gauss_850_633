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

// Module Configs --------------------------------------------------------------
#define USE_FUZZY_SYNCHRO    //synchronize the start of pulsed and triangular signals


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
#define MIN_POWER_TO_START_FAN    25
#define MIN_TIME_TO_WAIT_FOR_FAN    20000


// Module Exported Functions ---------------------------------------------------
// Setters
resp_t SetSignalType (signal_type_e signal);
resp_t SetFrequency (unsigned char freq);
resp_t SetPowerRed (unsigned char pwr_r);
resp_t SetPowerIRed (unsigned char pwr_ir);
void Signal_StopAll (void);

// Signals Generation
void Signal_GenerateCWave_Reset (void);
void Signal_GenerateCWave (void);
void Signal_GeneratePulsed_Reset (void);
void Signal_GeneratePulsed (void);
void Signal_GenerateTriangular_Reset (void);
void Signal_GenerateTriangular (void);

void SIGNALS_Timeouts (void);


#endif    /* _SIGNALS_H_ */

//--- end of file ---//

