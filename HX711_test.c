#include <msp430g2553.h>
#include <hx711.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAYSIZE 200

void main(void) {


  // stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
  // set up bit 0 of P1 as output
	//P1DIR = 0x01;
	//P2DIR = 0x00;
  // intialize bit 0 of P1 to 0
	//P1OUT = 0x00;
	unsigned long reading;
	signed int cbReading = 0;
	unsigned int myArray[ARRAYSIZE] = { 0 };
	unsigned int counter = 0;
	unsigned int zeroed = 0;
	reading = ReadCount();
	zeroed = Tare(reading);
	while (1) // infinite loop
	{
		reading = ReadCount(); // calls function to return scale readings then assigns to variable reading
		cbReading = (reading / 1000) - 8229; // Calibration equation (10000 8124 is off 8232 is on)
		myArray[counter] = cbReading; // places calibrated readings into array for safekeeping
		counter++; //increments counter
		__delay_cycles(125000); // 8 readings per second
		if(counter > 200) // resets counter to 0 when past 200
		{
			counter = 0;
		}
	}
}
