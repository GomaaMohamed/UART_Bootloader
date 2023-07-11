/************************************************************************
* @file BURNER_program.c
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:19:59 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of Standard Types and Bit Math header files goes here */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* Inclusion of Module header files goes here */
#include "BURNER_interface.h"
#include "BURNER_private.h"
#include "BURNER_config.h"

/* Inclusion of interface header files of the Other Modules goes here */
#include "FPEC_interface.h"
#include "INT_interface.h"



/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */




/* ==================================================================== */
/* =================== Public functions definition ==================== */
/* ==================================================================== */

// function to initialize the module
void BURNER_init(void){
    data_to_be_flashed = 0;
    address_of_data = 0x08002000;
    count_of_data = 0;
    indicator = DATA_UNRECIEVED;
    first_record_flag = 1;
}

// function to be called from the other modules to send the data that will be flashed
void BURNER_sendData(u16 *data,u32 address,u8 count){
    data_to_be_flashed = data;
    address_of_data = address;
    count_of_data = count;
}

// function to be called from the other modules to set the event of the recieved data
void BURNER_indicateData(void){
    indicator = DATA_RECIEVED;
}

// task to be called periodicly to do the logic of the module
void BURNER_update(void){
    // check the recieved record event
    if (indicator == DATA_RECIEVED)
    {
        // check if the recived record is the first record or not
        if (first_record_flag == 1)
        {
            // erase Application Area
            FPEC_voidEraseNumberOfPages(8,64);
            // reset first record flag
            first_record_flag = 0;
        }
        // flash the recieved data
        FPEC_voidFlashWrite(address_of_data,data_to_be_flashed,count_of_data);
        // verify the flashed data
        u8 verify = Burner_writeVerification(address_of_data,count_of_data);
        while(verify != 1)
        {
            FPEC_voidFlashWrite(address_of_data,data_to_be_flashed,count_of_data);
            verify = Burner_writeVerification(address_of_data,count_of_data);
        }
        // send an OK event to INTERFACE Module 
        INIT_sendOkStatus(OK);
        // reset the recieved data event
        indicator = DATA_UNRECIEVED;
    }
}




/* ==================================================================== */
/* =============== private functions definition ======================= */
/* ==================================================================== */

// function to read the flashed data and verify it 
static u8 Burner_writeVerification(u32 Address,u8 HalfWord_Count){
    // variable to hold the state 
    u8 writeVerification_Flag = 0;
    // loop on all the flashed half words
    for (u8 i = 0; i < HalfWord_Count; i++)
    {   // check the equality with the actual data
        if (*(((volatile u16*)Address)+i)==data_to_be_flashed[i])
        {  
            // set write verification flag
            writeVerification_Flag = 1;
        }
        else{
            // reset write verification flag
            writeVerification_Flag = 0;
            break;
        }
    }
    // return write verification flag
    return writeVerification_Flag;
}
