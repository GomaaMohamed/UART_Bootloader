#ifndef BURNER_PRIVATE_H
#define BURNER_PRIVATE_H
 
/************************************************************************
* @file BURNER_private.h
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:19:59 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ====================== private data types ========================== */
/* ==================================================================== */

/* Definition of private datatypes go here */
static u16 *data_to_be_flashed;
static u32 address_of_data;
static u8 count_of_data;
u8 first_record_flag;
typedef enum
{
    DATA_RECIEVED,
    DATA_UNRECIEVED
} t_burner_recieved;
t_burner_recieved indicator;

/* ==================================================================== */
/* ======================== private constants ========================= */
/* ==================================================================== */

/* #define, constants and enums statements go here */




/* ==================================================================== */
/* ==================== private function prototypes =================== */
/* ==================================================================== */

/* Private Functions Prototypes go here */
static u8 Burner_writeVerification(u32 Address, u8 HalfWord_Count);
#endif
