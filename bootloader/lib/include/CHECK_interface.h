#ifndef CHECK_INTERFACE_H
#define CHECK_INTERFACE_H
 
/************************************************************************
* @file CHECK_interface.h
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:21:12 +0300
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

/**
 * @brief   calculates length(number of charachters) of a string
 * @param   string the string that its length will be calculated
 * @return  the number of charachters in the string
 * @example
 *          ex1: int lenght = stringLength("Gomaa");
 *               the value of lenght will be 5
 */ 
u8 stringLength(u8 string[]);

/**
 * @brief   compare the similarity of two strings
 * @param   string1 the first string that will be compared
 * @param   string2 the seconed string that will be compared
 * @return  return 1 if the two strings are identical else it return 0
 * @example
 *          ex1: int check = stringCompare("Gomaa","Gomaa");
 *               the value of check will be 1
 *          ex2: int check = stringCompare("Gomaa","Hossam");
 *               the value of check will be 0
 */ 
u8 stringCompare(u8 string1[], u8 string2[]);

/**
 * @brief   convert any digit from asci code to a hex number
 * @param   Copy_u8Asci the digit that will be converted
 * @return  the converted digit in the form of hexadecimal
 * @example
 *          ex1: int hexnumber = asciToHex('A');
 *               the value of hexnumber will be 0xA
 */ 
u8 AsciToHex(u8 Copy_u8Asci);

/**
 * @brief   apply the CRC check of any recod in form of ihex and check it
 * @param   hexRecord the ihex record that will be checked
 * @return  return 1 if the record is correct else it return 0
 * @example
 *          ex1: int check = checkHex(":020000040800F2");
 *               the value of check will be 1
 *          ex2: int check = checkHex(":0200C0040800F2");
 *               the value of check will be 0
 */ 
u8 checkHex(u8 hexRecord[]);

void bubble_Sort(int array[],int size);
int linear_Search(int array[],int size,int element);
int binary_Search(int array[],int size,int element);
double power(double number, double power);
double factorial(int number);

#endif

