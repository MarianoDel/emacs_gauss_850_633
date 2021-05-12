//----------------------------------------------------------
// #### PROYECTO DEXEL 6CH BIDIRECCIONAL - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### PWM.H ##############################################
//----------------------------------------------------------

// Prevent recursive inclusion -------------------------------------------------
#ifndef __PWM_H_
#define __PWM_H_

#include "tim.h"

// Exported Types --------------------------------------------------------------



// Exported Constants or Macros ------------------------------------------------
// #define POWER_CONTROL_GENERAL_THRESHOLD    512    // este es un valor total de dmx no pwm

#define EnablePreload_PWM1    EnablePreload_TIM3_CH4
#define EnablePreload_PWM2    EnablePreload_TIM3_CH3
#define EnablePreload_PWM3    EnablePreload_TIM3_CH1
#define EnablePreload_PWM4    EnablePreload_TIM3_CH2
#define EnablePreload_PWM5    EnablePreload_TIM1_CH2
#define EnablePreload_PWM6    EnablePreload_TIM1_CH1

#define DisablePreload_PWM1    DisablePreload_TIM3_CH4
#define DisablePreload_PWM2    DisablePreload_TIM3_CH3
#define DisablePreload_PWM3    DisablePreload_TIM3_CH1
#define DisablePreload_PWM4    DisablePreload_TIM3_CH2
#define DisablePreload_PWM5    DisablePreload_TIM1_CH2
#define DisablePreload_PWM6    DisablePreload_TIM1_CH1

#define PWM_Update_IR(X)    Update_TIM3_CH1(X)
#define PWM_Update_R(X)    Update_TIM3_CH2(X)



// Exported Functions ----------------------------------------------------------
void PWMChannelsReset (void);
unsigned short PWM_Map_From_Dmx (unsigned char);
// void PWM_Set_PwrCtrl (unsigned char *, unsigned char, unsigned short);


#endif    /* __PWM_H_ */

//--- end of file ---//

