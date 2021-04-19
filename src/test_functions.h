//------------------------------------------------
// #### PROJECT: O3 TREATMENT - Custom Board #####
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.H #########################
//------------------------------------------------

// Prevent recursive inclusion -------------------------------------------------
#ifndef _TEST_FUNTIONS_H_
#define _TEST_FUNTIONS_H_

#include "hard.h"

// Exported Types Constants and Macros -----------------------------------------


// Exported Functions ----------------------------------------------------------
void TF_Led (void);
void TF_Led_Blinking (void);
void TF_Ctrl_Fan (void);
void TF_Usart1_Tx_Single (void);
void TF_Tim3_Channels (void);

#endif    /* _TEST_FUNTIONS_H_ */

//--- end of file ---//

