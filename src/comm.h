//----------------------------------------------------
// #### GAUSS 850-633nm Controller - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### COMM.H #######################################
//----------------------------------------------------
#ifndef _COMM_H_
#define _COMM_H_


// Exported Types Constants and Macros -----------------------------------------



// Module Exported Functions ---------------------------------------------------
void COMM_UpdateCommunications (void);
void COMM_ProcessMsg (void);
void COMM_SetOwnChannel (unsigned char);
char * COMM_GetOwnChannel (void);


#endif    /* _COMM_H_ */

//--- end of file ---//
