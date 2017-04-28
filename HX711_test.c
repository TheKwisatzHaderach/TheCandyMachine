#include <msp430g2553.h>
#include "hx711.h"
#include <stdlib.h>
#include <stdio.h>

#define ARRAYSIZE 100

void main(void) {

	WDTCTL = WDTPW | WDTHOLD;
	unsigned long reading = 0;
	unsigned int cReading = 0;
	unsigned int tReading = 0;
	unsigned int temp = 0;
	unsigned int myArray[ARRAYSIZE] = { 0 };
	unsigned int myArrayR[ARRAYSIZE] = { 0 };
	unsigned int counter = 0;
	unsigned int zeroed = 0;


	reading = ReadCount() / 1;
	zeroed = Tare(reading);
	temp = (reading/1000);
	//__delay_cycles(2000000);// must wait to read
	//cReading = (reading / 1000) - temp;



	while (1) // infinite loop
	{
		__delay_cycles(125000);//8 readings
		reading = ReadCount(); // calls function to return scale readings then assigns to variable reading
		cReading = (reading / 1000) - 8100; // Calibration equation (add a failsafe?)
		tReading = (reading / 1000) - zeroed;
		myArray[counter] = cReading; // places calibrated readings into array for safekeeping
		myArrayR[counter] = tReading;
		counter++; //increments counter
		if(counter > 100) // resets counter to 0 when past 200
		{
			counter = 0;
		}
	}


}
