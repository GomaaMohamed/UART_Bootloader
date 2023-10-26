#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "USONIC_interface.h"
#include "GPIO_interface.h"

int main(void)
{
	RCC_initSysClock();
	RCC_enableClock(RCC_APB2, RCC_IOPA);
	GPIO_setPinDirection(GPIOA, GPIO_PIN2, GPIO_OUTPUT_10MHZ_PP);
	GPIO_setPinValue(GPIOA, GPIO_PIN2, GPIO_HIGH);
	// USONIC_init();
	// u32 Distance = 0;
	while (1)
	{
		// if (USONIC_getDistance(&Distance) == VALID_DISTANCE)
		// {
		// 	if (Distance <= 50 )
		// 	{
		// 		GPIO_setPinValue(GPIOA, GPIO_PIN2, GPIO_HIGH);
		// 	}
		// 	else 
		// 	{
		// 		GPIO_setPinValue(GPIOA, GPIO_PIN2, GPIO_LOW);
		// 	}
		// }

	 }
	return 0;
}


