/************************************************************************
* @file CHECK_program.c
* @author Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version V0.1   
* @date Mon, 05 Jun 2023 18:21:12 +0300
* @brief A description of the module’s purpose.
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of Standard Types and Bit Math header files goes here */
#include "STD_TYPES.h"
/* Inclusion of Module header files goes here */
#include "CHECK_interface.h"
#include "CHECK_private.h"
#include "CHECK_config.h"

/* Inclusion of interface header files of the Other Modules goes here */




/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */




/* ==================================================================== */
/* =================== Public functions definition ==================== */
/* ==================================================================== */

/* Functions definitions public functions go here */

// function to calculates length of a string
u8 stringLength(u8 string[]){
    // variable to hold the length
    u8 length = 0;
    // loop on the string until reach the null charachter \0(end of the string)
    while (string[length] != '\0')
    {   // increment the length
        length++;
    }
    // return the length of the passed string
    return length;
}

// function to compare the simirarity of two strings
u8 stringCompare(u8 string1[],u8 string2[]){
    // claculate the length of the two strings
    u8 length1 = stringLength(string1);
    u8 length2 = stringLength(string2);
    // flag to check
    u8 compareFlag = 0;
    // of the length of the two strings the same continue 
    if (length1 == length2)
    {
        // loop on the two strings
        for (u8 i = 0; i < length1; i++)
        {   // if all charachters of the two strings is identical compareFlag = 1
            if (string1[i]==string2[i])
            {
                compareFlag = 1;
            }
            // else if one of the charachters is not identical compareFlag = 0 and break
            else{
                compareFlag = 0;
                break;
            }
        }
        
    }
    // return the state of the two strings
    return compareFlag;
}

// function to convert any charchter and number in ascii to hexadecimal
u8 AsciToHex(u8 Copy_u8Asci)
{
    // variable to hold the converted value
	u8 Result;
    // check if it is a number from 0 to 9
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{   // subtracte the offset of ascii
		Result = Copy_u8Asci - 48;
	}
    // else if it is a character from A to Z
	else
	{   // subtracte the offset of ascii
		Result = Copy_u8Asci - 55;
	}
    // return the converted value
	return Result;
}

// function to check if the hex record is correct or not
u8 checkHex(u8 hexRecord[]){
    // flag to hold the state
    u8 checkFlag = 0;
    // variable to hold the incremental value of the checksum
    u8  checkSum = 0;
    // apply the algorithm on the address and data records only
    if (hexRecord[8] == '0' || hexRecord[8] == '1' || hexRecord[8] == '4' || hexRecord[8] == '5')
    {
        // calculate the length of the ihex record
        u8 Len1 = AsciToHex(hexRecord[1]);
        u8 Len0 = AsciToHex(hexRecord[2]);
        u8 length = ((Len1 << 4) | (Len0))*2 + 0xB;
        //int length = stringLength(hexRecord);
        // take the incremental summation of all bytes of the ihex recors
        for (int i=1; i < length-3; i+=2)
        {   // adjust every two digits in one byte
            u8 Digit1 = AsciToHex(hexRecord[i]);
            u8 Digit0 = AsciToHex(hexRecord[i + 1]);
            u8 Temp = (Digit1 << 4) | (Digit0);
            checkSum += Temp;
        }
        // make the 2'nd complement on the summation
        checkSum = (~checkSum) + 1;
        // extract the checksum from the ihex record
        u8 Digit1 = AsciToHex(hexRecord[length-2]);
        u8 Digit0 = AsciToHex(hexRecord[length-1]);
        u8 Temp = (Digit1 << 4) | (Digit0);
        // compare the calculated checksum and the extrcated one
        if (checkSum == Temp)
        {
            checkFlag = 1;
        }
        }
        // return the state
        return checkFlag;
}

// function to be used to sort array of integers
void bubble_Sort(int array[],int size){
    int temp = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size-i-1; j++)
        {
             if (array[j] > array[j+1])
             {
                //swap array[j] and array[j+1]
                temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
             }
             else
             {
                //do nothing
             }
                }
    }  
}

// function to be used to search for an integer number in an array
int linear_Search(int array[],int size,int element){
    int retval = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == element)
        {
             retval = 1;
             break;
        }
        else
        {
            //do nothing
        }
    }
    return retval;
}

// function to be used to search for an integer number in an array
int binary_Search(int array[],int size,int element){
    int  start=0,end=size-1,middle=(end+start)/2;
    int retval = 0;
        //repeat til start == end
        while (start != end)
        {
        middle = (end + start) / 2;
        if (element == array[middle])
        {
             retval = 1;
             break;
        }
        else if(element > array[middle])
        {
             start = element + 1;
        }
        else
        {
             end = element - 1;
        }
        }
       return retval; 
    }
    
double power(double number, double power)
{
  double result = 1;
  for (int i = 0; i < power; i++)
  {
    result *= number;
  }
  return result;
}
double factorial(int number){
  double result = 1;
  for (int i = 1; i <= number; i++)
  {
    result *= i;
  }
  return result;
}

/* ==================================================================== */
/* =============== private functions definition ======================= */
/* ==================================================================== */

/* Function Definitions for private (static) functions go here */






