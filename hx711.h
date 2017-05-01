#include <msp430g2553.h>

#ifndef HX711_H_
#define HX711_H_

unsigned long ReadCount(){
	unsigned long Count; // long = 4bytes/32bits Count == 25bits
	unsigned char i; //iterable
	P1DIR = 0x01;
	P2DIR &= ~BIT0;
	P1OUT = 0x00; // sets clock to low
	Count=0;
	for (i=0;i<24;i++) // Sends clock 25 clock pulses (Gain of 128)
	{
		P1OUT = 0x01; //clock high
		Count=Count<<1; //shifts bit
		P1OUT = 0x00; //clock low
		if(P2IN) Count++; // increment count if Dout is high
	}
	P1OUT = 0x01;
	Count=Count^0x800000; // ^ is xor operator 0x800000 = b100000000000000000000000
	P1OUT = 0x00;
	return(Count); // returns reading value from scale
}

unsigned int Tare(unsigned long Reading)
{
	unsigned int temp = 0;
	temp = (Reading / 1000);
	return temp;
}

#endif /* HX711_H_ */

