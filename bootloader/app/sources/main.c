#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "INT_interface.h"
#include "PARSER_interface.h"
#include "BURNER_interface.h"


int main(void)
{   
    // enable system clock
    RCC_voidInitSysClock();
	INIT_init();
	PARSER_init();
	BURNER_init();

	while(1)
	{
		INIT_update();
		PARSER_update();
		BURNER_update();
	}
return 0;
}
