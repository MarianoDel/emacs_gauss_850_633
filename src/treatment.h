//----------------------------------------------------
// #### GAUSS 850-633nm Controller - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TREATMENT.H ##################################
//----------------------------------------------------
#ifndef _TREATMENT_H_
#define _TREATMENT_H_

#include "answers.h"


// Module Exported Types Constants and Macros ----------------------------------
typedef enum {
    TREATMENT_INIT_FIRST_TIME = 0,
    TREATMENT_STANDBY,
    TREATMENT_START_TO_GENERATE,
    TREATMENT_GENERATING_CWAVE,
    TREATMENT_GENERATING_PULSED,
    TREATMENT_GENERATING_TRIANGULAR,
    TREATMENT_STOPPING,
    TREATMENT_STOPPING2

} treatment_state_e;

// typedef struct {
//     signal_type_e signal;

//     unsigned char frequency;

//     unsigned char power_red;
//     unsigned char power_ired;
    
// } treatment_params_t;



// Module Exported Functions ---------------------------------------------------
void TreatmentManager_Reset (void);
void TreatmentManager (void);
treatment_state_e TreatmentGetState (void);
resp_t TreatmentStart (void);
void TreatmentStop (void);
void TREATMENT_Timeouts (void);


#endif    /* _TREATMENT_H_ */

//--- end of file ---//

