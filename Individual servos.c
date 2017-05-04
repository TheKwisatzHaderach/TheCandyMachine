#include "msp430g2553.h"
#include "Servos.h"

#define A 1
#define B 0

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	while(1)
	{
		// calls servo function from hearder file, to run one servo comment others out
		ServoONE();
		ServoTWO();
		ServoTHREE();
		ServoFOUR(A);
		ServoFOUR(B);
	}

}











