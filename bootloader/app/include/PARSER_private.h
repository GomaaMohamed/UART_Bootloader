#ifndef PARSER_PRIVATE_H
#define PARSER_PRIVATE_H
 
/************************************************************************
* @file PARSER_private.h
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:19:15 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ====================== private data types ========================== */
/* ==================================================================== */

/* Definition of private datatypes go here */
t_recived data_recieved_indication = UNRECIEVED;
u8 *data_buffer =NULL;
static u16 parsed_data[100] = {0};
static u8 data_count = 0;
static u32 Address = 0x08000000;
volatile u8 data_address_flag;

/* ==================================================================== */
/* ======================== private constants ========================= */
/* ==================================================================== */

/* #define, constants and enums statements go here */




/* ==================================================================== */
/* ==================== private function prototypes =================== */
/* ==================================================================== */

/* Private Functions Prototypes go here */
static void Parser_voidParseRecord(u8 *Copy_u8BufData);
static void ParseUpperAddress(u8 *Copy_u8BufData);
static void ParseData(u8 *Copy_u8BufData);
//static u8 AsciToHex(u8 Copy_u8Asci);

#endif

