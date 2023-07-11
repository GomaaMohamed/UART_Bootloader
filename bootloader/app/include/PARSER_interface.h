#ifndef PARSER_INTERFACE_H
#define PARSER_INTERFACE_H
 
/************************************************************************
* @file PARSER_interface.h
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:19:15 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Definition of public datatypes go here */
typedef enum
{
    RECIEVED,
    UNRECIEVED
} t_recived;

/* ==================================================================== */
/* ======================== public Macros ============================= */
/* ==================================================================== */

/* Public Macro Definitions go here */




/* ==================================================================== */
/* ==================== public function prototypes ==================== */
/* ==================================================================== */

/* Public Functions Prototypes go here */
void PARSER_init(void);
void PARSER_setRecord(u8 *Record);
void PARSER_indicateRecievedData();
void PARSER_update(void);

#endif

