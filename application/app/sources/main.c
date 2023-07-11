#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"


volatile u8 flag = 0;
void func(void);

int main(void)
{
	RCC_voidInitSysClock();
	STK_voidInit();
	RCC_voidEnableClock(RCC_APB2, RCC_IOPA);
	GPIO_voidSetPinDirection(GPIOA, GPIO_PIN1, GPIO_OUTPUT_2MHZ_PP);
	STK_voidSetIntervalPeriodic(1000000, func);
	
	
	
	while (1)
	{
	   
		
	}
	return 0;
}

void func(void)
{
	if (flag == 0)
	{
		GPIO_voidSetPinValue(GPIOA,GPIO_PIN1,GPIO_HIGH);
		flag = 1;
		}
	else{
		GPIO_voidSetPinValue(GPIOA,GPIO_PIN1,GPIO_LOW);
		flag = 0;
	}
}
