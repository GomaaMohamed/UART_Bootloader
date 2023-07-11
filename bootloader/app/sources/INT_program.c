/************************************************************************
* @file INT_program.c
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:18:23 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of Standard Types and Bit Math header files goes here */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* Inclusion of Module header files goes here */
#include "INT_interface.h"
#include "INT_private.h"
#include "INT_config.h"

/* Inclusion of interface header files of the Other Modules goes here */
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "USART_interface.h"
#include "PARSER_interface.h"





/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */




/* ==================================================================== */
/* =================== Public functions definition ==================== */
/* ==================================================================== */

// function to initialize the module
void INIT_init(void){

    // initialize UART
    USART_voidInit();
    // initialize system timer
    STK_voidInit();
    // set the period that the bootloader will wait bafor jumbing to the application
    STK_voidSetIntervalSingle(5000000,check_time);
    // data initialization of the module
    status = NOT_OK;
    addr_to_call = 0;
    u8RecCounter = 0;
    jumbFlag = 0;
    first_record = 1;
}

// task to be called periodicly to do the logic of the module
void INIT_update(void){

        // ACTION1: listen over uart and recieve data
		u8 Local_u8RecStatus = USART_u8Receive( &(u8RecBuffer[u8RecCounter]) );
        // check if there are recieved data or not
		if (Local_u8RecStatus == 1)
		{   
            // stop timer
			STK_voidStopInterval();
            // check if a full recored was recieved or not
			if(u8RecBuffer[u8RecCounter] == '\n')
			{
                // check if the recived record is the first record or not
                if (first_record == 1)
                {
                    // check flashing key is autherized or not
                    if (u8RecBuffer[0]=='b'&&u8RecBuffer[1]=='u'&&u8RecBuffer[2]=='r'&&u8RecBuffer[3]=='n')
                    {
                        // set OK event to send it to host application
                        status = OK;
                        first_record = 0;
                    } 
                }
                else{
                    // send the recieved record to the PARSER Module
                    PARSER_setRecord(u8RecBuffer);
                    // send a recieved record indication
                    PARSER_indicateRecievedData();
                }   
            }
			else
			{
                // increase the index counter of the data buffer
				u8RecCounter++ ;
			}
            // start timer stop timer
			STK_voidSetIntervalSingle(5000000,check_time);
		}

        // ACTION2: if the record was successfully flashed send ok message over UART
        if(status == OK)
        {
            USART_voidTransmit("C");
            u8RecCounter = 0;
            status = NOT_OK;
        }
        
        // ACTION3: jumb to application at specific condition
        if (jumbFlag == 1)
        {   
            jumbFlag = 0;
            u8RecCounter = 0;
            first_record = 1;
            jumb_to_app();
        }
}

// function to be called from the other modules to set OK event
void INIT_sendOkStatus(t_status status_value){
    status = status_value;
}

/* ==================================================================== */
/* =============== private functions definition ======================= */
/* ==================================================================== */

// function to jump to the Application
void jumb_to_app(void)
{   
    // disable all interrupts and faults
	asm("CPSID i");
    asm("CPSID f");
    // jumb to application code  
    addr_to_call = *(Function_t *)(0x08002004);      
    addr_to_call();
}

// function to be called if timeout without recieving any thing over UART
void check_time(void){
    jumbFlag = 1;
}
