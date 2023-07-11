/************************************************************************
* @file PARSER_program.c
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:19:15 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of Standard Types and Bit Math header files goes here */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CHECK_interface.h"
/* Inclusion of Module header files goes here */
#include "PARSER_interface.h"
#include "PARSER_private.h"
#include "PARSER_config.h"

/* Inclusion of interface header files of the Other Modules goes here */
#include "BURNER_interface.h"
#include "INT_interface.h"




/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */




/* ==================================================================== */
/* =================== Public functions definition ==================== */
/* ==================================================================== */

// function to initialize the module
void PARSER_init(void){

    // data initialization of the module
    data_recieved_indication = UNRECIEVED;
    data_buffer =NULL;
    data_count = 0;
    Address = 0x08000000;
	data_address_flag = 0;
}

// function to be called from the other modules to send the data that will be parsed
void PARSER_setRecord(u8 *Record){
    data_buffer = Record;
}

// function to be called from the other modules to set the event of the recieved data
void PARSER_indicateRecievedData(void){
    data_recieved_indication = RECIEVED;
}

// task to be called periodicly to do the logic of the module
void PARSER_update(void){
	// check that there is a record must be parsed
    if (data_recieved_indication == RECIEVED)
    {
        // check the Record
		u8 sumCheck = checkHex(data_buffer);
		if (sumCheck == 1)
		{
			// Analyse the Record
			Parser_voidParseRecord(data_buffer);
       		if (data_address_flag == 1)
       	    {
        		// send the Data Record to Burner to flash it
        		BURNER_sendData(parsed_data,Address,data_count);
        		// indicate the burner with the record
       			 BURNER_indicateData();
        		data_address_flag == 0;
            }
			else{
				INIT_sendOkStatus(OK);
			}
			
		}
		
		// set the UNRECIEVED state
        data_recieved_indication = UNRECIEVED;
    }
    
}

/* ==================================================================== */
/* =============== private functions definition ======================= */
/* ==================================================================== */

// function to parse the data record(remove the extra data and set the endianess)
static void ParseData(u8* Copy_u8BufData)
{
	// auxilary variables
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;
	/* get character count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;
	/* get the address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);
	/* clear low part of address */
	Address = Address & 0xFFFF0000;
	// set low part
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);
    // loop on all the recieved data, set the endianess and store it in a new buffer 
	for (i=0;i<CC/2; i++)
	{  
		// get current data
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);
	    // set the endianess and store the data
		parsed_data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}
	// set the number of half words
	data_count = CC/2;
}

// function to parse the address record
static void ParseUpperAddress(u8* Copy_u8BufData)
{
	// auxilary variables
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	/* get address */
	DataDigit0 = AsciToHex (Copy_u8BufData[9]);
	DataDigit1 = AsciToHex (Copy_u8BufData[10]);
	DataDigit2 = AsciToHex (Copy_u8BufData[11]);
	DataDigit3 = AsciToHex (Copy_u8BufData[12]);
	/* clear high part of address */
	Address = Address & (u32)0x0000FFFF;
	// set the address
	Address = Address | (u32)((u32)(DataDigit0 << 28) | (u32)(DataDigit1 << 24) | (u32)(DataDigit2 << 20) | (u32)(DataDigit3 << 16));
}

// function to parse the record based on its type
static void Parser_voidParseRecord(u8* Copy_u8BufData)
{
	switch (Copy_u8BufData[8])
	{
	case '0': 
        ParseData(Copy_u8BufData);
        data_address_flag = 1;
        break;
    case '4': 
        ParseUpperAddress(Copy_u8BufData);
    	data_address_flag = 0;
    	break;
    }
}







