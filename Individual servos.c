#include "msp430g2553.h"
#include "Servos.h"

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	while(1)
	{
		ServoONE();
		ServoTWO();
		ServoTHREE();
		ServoFOUR();

	}

}











