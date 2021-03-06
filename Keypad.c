#include  <msp430g2553.h>


#define arraySizeKey 20
#define tagInputCount 5

    const char keyMap[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'},
    };

    const char rowPins[4] = {BIT4, BIT5, BIT3, BIT7}; //bit1
    const char colPins[3] = {BIT3, BIT4, BIT5};
    volatile int arrayInputs[arraySizeKey] = {0};
    volatile char arrayInputsC[arraySizeKey] = {0};
    volatile int value;
    volatile int candyA;
    volatile int candyB;
    volatile int candyC;
    volatile int toppingA;
    volatile int toppingB;
    volatile int x = 0;
    unsigned int tagcount = 0;


    void main(void)
    {
            WDTCTL = WDTPW + WDTHOLD;
            //Port Setup
           // P1SEL |= BIT4 + BIT5 + BIT3 + BIT1;
            //P1DIR |= BIT4 + BIT5 + BIT3 + BIT1;         // Enable P1 outputs used for row scanning
            //P1OUT &= ~(BIT4 + BIT5 + BIT3 + BIT1);   // Set outputs to LOW
            P2SEL &= ~(BIT3 + BIT4 + BIT5);
            P2DIR &= ~(BIT3 + BIT4 + BIT5);
            P2OUT |= 0xFF;
            P2REN |= BIT3 + BIT4 + BIT5;              // Enable weak pull up resistors on the P2 inputs used for column scanning.
            P1DIR |= BIT4 + BIT5 + BIT3 + BIT7;         // Enable P1 outputs used for row scanning bit1
            P1OUT &= ~(BIT4 + BIT5 + BIT3 + BIT7);// Set outputs to LOW bit1
            P2IN |= BIT3 + BIT4 + BIT5;
            //P2REN |= BIT3 + BIT4 + BIT5;                // Enable weak pull up resistors on the P2 inputs used for column scanning.
            //Timer interrupt used to read the keypad to see if a key is being pressed
            CCTL0 = CCIE; //CCR0 interrupt enabled
            CCR0 = 30000;
            TACTL = TASSEL_2 + MC_1; // smclk count up
            int d;

            _BIS_SR(GIE); // LPM0 + interrupt

            while(tagcount < tagInputCount)
            {
            	tagcount = 0;
            	for(d = 0; d<arraySizeKey; d++)
            	{
            		if(arrayInputs[d] == 35)
            		{
            			tagcount = tagcount + 1;
            		}
            	}
            }
            _BIC_SR(GIE); // Disables interupt
            while(1)
            {
            	candyB = arrayInputs[4];
            	if(candyB > 1)
            	{
            		while(1){}
            	}
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
                                    arrayInputsC[x] = (char) value;
                                    x = x +1;
                                    if(x > arraySizeKey)
                                    {
                                    	x = 0;
                                    }
                                    while(!(P2IN & colPins[j])); //blocking while a key is held down
                            }
                    }
                    P1OUT |= rowPins[i]; //row HIGH
            }
    }


//old P2In not properly set up occassionaly dosent work
/*
#include  <msp430g2553.h>


#define arraySizeKey 20

    const char keyMap[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'},
    };

    const char rowPins[4] = {BIT4, BIT5, BIT3, BIT7};
    const char colPins[3] = {BIT3, BIT4, BIT5};
    volatile int arrayInputs[arraySizeKey] = {0};
    volatile char arrayInputsC[arraySizeKey] = {0};
    volatile int value;
    volatile int x = 0;

    void main(void)
    {
            WDTCTL = WDTPW + WDTHOLD;
            //Port Setup
            P1DIR |= BIT4 + BIT5 + BIT3 + BIT7;         // Enable P1 outputs used for row scanning
            P1OUT &= ~(BIT4 + BIT5 + BIT3 + BIT7);   // Set outputs to LOW
            P2REN |= BIT3 + BIT4 + BIT5;                // Enable weak pull up resistors on the P2 inputs used for column scanning.
            //Timer interrupt used to read the keypad to see if a key is being pressed
            CCTL0 = CCIE;
            CCR0 = 30000;
            TACTL = TASSEL_2 + MC_1;
            _BIS_SR(GIE); // LPM0 + interrupt

            while(1){}

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
                                    arrayInputsC[x] = (char) value;
                                    x = x +1;
                                    while(!(P2IN & colPins[j])); //blocking while a key is held down
                            }
                    }
                    P1OUT |= rowPins[i]; //row HIGH
            }
    }

/*#include  <msp430g2553.h> // Only volatile input
#define ArraySize 100

    const char keyMap[4][3] = {
   {'1','2','3'},
   {'4','5','6'},
   {'7','8','9'},
   {'*','0','#'},
   };
    const char rowPins[4] = {BIT4 + BIT5 + BIT6 + BIT7};
    //const char rowPins[4] = {BIT4, BIT5, BIT6, BIT7};
    const char colPins[3] = {BIT0, BIT1, BIT2};
    int myArray[ArraySize] = {0};
    volatile int value;
    volatile int flag;
    volatile int x;

    void main(void)
    {
            //Kill WDT and setup clocks
            WDTCTL = WDTPW + WDTHOLD;
            BCSCTL1 = CALBC1_1MHZ;
            DCOCTL = CALDCO_1MHZ;
            //Port Setup
            //P1DIR = BIT2 + BIT3 + BIT4 + BIT5;
            //P1OUT &= ~(BIT2 + BIT3 + BIT4 + BIT5);
            P1DIR = BIT4 + BIT5 + BIT6 + BIT7;         // Enable P1 outputs used for row scanning
            P1OUT &= ~(BIT4 + BIT5 + BIT6 + BIT7);
            // Set outputs to LOW
            P2REN |= BIT0 + BIT1 + BIT2;                // Enable weak pull up resistors on the P2 inputs used for column scanning.
            //Timer interrupt used to read the keypad to see if a key is being pressed
            CCTL0 = CCIE;
            CCR0 = 30000;
            TACTL = TASSEL_2 + MC_1;
            //int myArray[ArraySize] = {0};
            value =0;
            flag = 0;
            x = 0;

            _BIS_SR(GIE);                 // LPM0 + interrupt
            while(1)
            {
            }
    }

    // TimerA0 ISR
    #pragma vector=TIMER0_A0_VECTOR
    __interrupt void Timer_A (void)
    {
            char i;
            char j;
            for(i=1; i < 4; i++){
                    P1OUT &= ~rowPins[i];  //row LOW
                    for(j=0; j < 3; j++){
                            if(!(P2IN & colPins[j])){
                                    value = keyMap[i][j];
                                    x = x+1;
                                    //myArray[x] = value;
                                    //flag = i;
                                    //__delay_cycles(10000);
                            }
                    }
                    P1OUT |= rowPins[i]; //row HIGH
            }
}
*/
