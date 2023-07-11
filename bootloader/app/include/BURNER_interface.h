#ifndef BURNER_INTERFACE_H
#define BURNER_INTERFACE_H
 
/************************************************************************
* @file BURNER_interface.h
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:19:59 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Definition of public datatypes go here */




/* ==================================================================== */
/* ======================== public Macros ============================= */
/* ==================================================================== */

/* Public Macro Definitions go here */




/* ==================================================================== */
/* ==================== public function prototypes ==================== */
/* ==================================================================== */

/* Public Functions Prototypes go here */
void BURNER_init(void);
void BURNER_sendData(u16 *data, u32 address, u8 count);
void BURNER_indicateData(void);
void BURNER_update(void);

#endif

