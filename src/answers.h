//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### ANSWERS.H #############################
//---------------------------------------------

#ifndef _ANSWERS_H_
#define _ANSWERS_H_

// Exported Types Constants and Macros -----------------------------------------
typedef enum {
    resp_ok = 0,
    resp_continue,
    resp_selected,
    resp_change,
    resp_change_all_up,
    resp_working,
    resp_error,
    resp_need_to_save,
    resp_finish,
    resp_nok,
    resp_timeout,
    resp_ready,
    resp_no_answer,
    resp_save

} resp_t;


#endif /* _ANSWERS_H_ */

//--- end of file ---//
