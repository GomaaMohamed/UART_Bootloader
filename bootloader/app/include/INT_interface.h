#ifndef INT_INTERFACE_H
#define INT_INTERFACE_H
 
/************************************************************************
* @file INT_interface.h
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:18:23 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Definition of public datatypes go here */
typedef enum
{
    OK,
    NOT_OK
} t_status;

/* ==================================================================== */
/* ======================== public Macros ============================= */
/* ==================================================================== */

/* Public Macro Definitions go here */




/* ==================================================================== */
/* ==================== public function prototypes ==================== */
/* ==================================================================== */

/* Public Functions Prototypes go here */
void INIT_init(void);
void INIT_update(void);
void INIT_sendOkStatus(t_status status_value);

#endif

