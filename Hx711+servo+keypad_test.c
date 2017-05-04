#include  <msp430g2553.h>
#include "Servos.h"

#define arraySizeKey 50
#define tagInputCount 1 //minimum of 1

#define A 1//toppingA
#define B 0//toppingB

static unsigned int Tare(unsigned long AReading);
static unsigned long ReadCount();

    const char keyMap[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'},
    };

    const char rowPins[4] = {BIT4, BIT5, BIT3, BIT1};
    const char colPins[3] = {BIT3, BIT4, BIT5};
    volatile int arrayInputs[arraySizeKey] = {0};
    volatile int value;
    unsigned int candyA;
    unsigned int candyB;
    unsigned int candyC;
    unsigned int toppingA;
    unsigned int toppingB;
    volatile int x;
    unsigned int tagcount;
    unsigned int tagFlag;



    void main(void)
    {
    	while(1)
    	{
            WDTCTL = WDTPW + WDTHOLD;
            //Port Setup
            P1DIR |= BIT4 + BIT5 + BIT3 + BIT1;         // Enable P1 outputs used for row scanning
            P1OUT &= ~(BIT4 + BIT5 + BIT3 + BIT1);   // Set outputs to LOW
            P2REN |= BIT3 + BIT4 + BIT5;                // Enable weak pull up resistors on the P2 inputs used for column scanning.
            //Timer interrupt used to read the keypad to see if a key is being pressed
            CCTL0 = CCIE;
            CCR0 = 30000;
            TACTL = TASSEL_2 + MC_1;
            unsigned int i;
            unsigned int p;
            unsigned int z;
            unsigned int b;
            x = 0;
            tagcount = 0;
            int doneFlag = 0;
            int aFlag = 0;
            int bFlag = 0;
            int cFlag = 0;
            int tAFlag = 0;
            int tBFlag = 0;

            //hx711

            for(z = 0; z<arraySizeKey; z++) // clears array
            {
            	arrayInputs[z] = 0;
            }
            _BIS_SR(GIE); // interrupt


            while(tagcount < tagInputCount)
            {
            	tagcount = 0;
            	for(i = 0; i<arraySizeKey; i++)
            	{
            		if(arrayInputs[i] == 35)
            		{
            			tagcount = tagcount + 1;
            		}
            	}
            }
            tagFlag = x -1;
            while(doneFlag == 0)
            {
            	for(p = tagFlag; p<x; p++)
            	{
            		if(arrayInputs[p] == 35)
            		{
            			if((arrayInputs[p-1] > 47)&& (arrayInputs[p-2] > 47)&&((arrayInputs[p-3] == 42)||(arrayInputs[p-3] == 35)))
            				if(candyA < 1)
            				{
            					candyA = ((arrayInputs[p-1])-48) + (((arrayInputs[p-2])-48)*10);
            					aFlag = p;
            				}
            				else if((candyB < 1)&&((p - aFlag)> 2)&&(aFlag != 0))
            			    {
            					candyB = ((arrayInputs[p-1])-48) + (((arrayInputs[p-2])-48)*10);
            					bFlag = p;
            			    }
            				else if((candyC < 1)&&((p - bFlag)> 2)&&(!(bFlag > p))&&(bFlag != 0))
            				{
            				    candyC = ((arrayInputs[p-1])-48) + (((arrayInputs[p-2])-48)*10);
            				    cFlag = p;
            				}
            		}
            		else if((candyA > 1)&&(candyB > 1)&&(candyC > 1))
            			doneFlag = 1;
            	}
            }
            while((tBFlag == 0))
            {
            	for(b = (cFlag+1); b<x; b++)
            	{
            		if((arrayInputs[b] == 35)&&(tAFlag == 0))
            		{
            			toppingA = 1;
            			tAFlag = b;
            		}
            		else if((arrayInputs[b] == 42)&&(tAFlag == 0))
            		{
            			toppingA = 0;
            			tAFlag = b;
            		}
            		else if((tAFlag != 0)&&(arrayInputs[b] == 35)&&((b - tAFlag) != 0 ))
            		{
            			toppingB = 1;
            			tBFlag = 1;
            		}
            		else if((tAFlag != 0)&&(arrayInputs[b] == 42)&&((b - tAFlag) != 0 ))
            		{
            			toppingB = 0;
            		    tBFlag = 1;
            		}
            	}
            }
            _BIC_SR(GIE); //disable interupt
    		unsigned long reading = 0;
    		signed int cReading = 0;
    		static unsigned int zeroed;

            reading = ReadCount();
            zeroed = Tare(reading);

            positionServos();// positions servos

    		while(cReading < candyA)
    		{
    			ServoONE();
    			cReading = (ReadCount() / 1000) - zeroed;
    			__delay_cycles(1000000);
   			}
    		while(cReading < (candyB+candyA))
    		{
    				ServoTWO();
    				cReading = (ReadCount() / 1000) - zeroed;
    				__delay_cycles(1000000);
    		}
    		while(cReading < (candyC + candyB + candyA))
    		{
    				ServoTHREE();
    				cReading = (ReadCount() / 1000) - zeroed;
    				__delay_cycles(1000000);
    		}
    		if(toppingA == 1)
    		{
    			ServoFOUR(A); //need to pass in value for specific topping
    		}
    		if(toppingB == 1)
    		{
    			ServoFOUR(B); //need to pass in value for specific topping
   			}
    	cReading = 0;


    	}
    }

    // TimerA0 ISR
    #pragma vector=TIMER0_A0_VECTOR
    __interrupt void Timer_A (void)
    {
            char i;
            char j;
            for(i=0; i < 4; i++){
                    P1OUT &= ~rowPins[i];  //row LOW
                    for(j=0; j < 3; j++){
                            if(!(P2IN & colPins[j])){
                                    value = keyMap[i][j];
                                    arrayInputs[x] = value;
                                    x = x +1;
                                    if(x >= arraySizeKey)
                                    {
                                    	x = 0;
                                    }
                                    while(!(P2IN & colPins[j])); //blocking while a key is held down
                            }
                    }
                    P1OUT |= rowPins[i]; //row HIGH
            }
    }

    static unsigned int Tare(unsigned long AReading)
    {
    	return (AReading / 1000);
    }

    static unsigned long ReadCount()// Must have 125000 clck cycles between readings
    {
    	unsigned long Count; // long = 4bytes/32bits Count == 25bits
    	unsigned char i; //iterable
    	P1SEL &= (~BIT0); // Set P1.0 SEL for GPIO
    	P1DIR |= BIT0; // Set P1.0 as Output
    	P2SEL &= (~BIT0);
    	P2DIR &= (~BIT0); // Set P2.0 SEL as Input
    	P1OUT &= (~BIT0); // sets clock to low
    	Count=0;
    	for (i=0;i<24;i++) // Sends clock 25 clock pulses (Gain of 128)
    	{
    		P1OUT |= BIT0; // Set P1.0 HIGH
    		Count=Count<<1; //shifts bit
    		P1OUT &= (~BIT0); //clock low
    		if(P2IN & BIT0) Count++; // increment count if Dout is high
    	}
    	P1OUT |= BIT0; // Set P1.0 HIGH
    	Count=Count^0x800000; // ^ is xor operator 0x800000 = b100000000000000000000000
    	P1OUT &= (~BIT0);
    	return(Count); // returns reading value from scale
    }


