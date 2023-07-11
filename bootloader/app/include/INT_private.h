#ifndef INT_PRIVATE_H
#define INT_PRIVATE_H
 
/************************************************************************
* @file INT_private.h
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:18:23 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ====================== private data types ========================== */
/* ==================================================================== */

/* Definition of private datatypes go here */
static volatile t_status status ;
typedef void (*Function_t)(void);
Function_t addr_to_call;
volatile u8  u8RecCounter;
volatile u8 jumbFlag;
volatile u8 first_record;
u8 u8RecBuffer[100];

/* ==================================================================== */
/* ======================== private constants ========================= */
/* ==================================================================== */

/* #define, constants and enums statements go here */




/* ==================================================================== */
/* ==================== private function prototypes =================== */
/* ==================================================================== */

/* Private Functions Prototypes go here */
void jumb_to_app(void);
void check_time(void);

#endif

