#include "msp430g2553.h"

#ifndef SERVOS_H_
#define SERVOS_H_

#define MCU_CLOCK			1000000
#define PWM_FREQUENCY		50		// In Hertz, ideally 50Hz.

#define SERVO_STEPS			180		// Maximum amount of steps in degrees (180 is common)
#define SERVO_MIN			600	// The minimum duty cycle for this servo
#define SERVO_MAX			2500	// The maximum duty cycle

unsigned int PWM_Period		= (MCU_CLOCK / PWM_FREQUENCY);	// PWM Period
unsigned int PWM_Duty		= 0;							// %

void positionServos(void)
{
	unsigned int servo_stepval, servo_stepnow;
		unsigned int servo_lut[ SERVO_STEPS+1 ];
		unsigned int i;


		// Calculate the step value and define the current step, defaults to minimum.
		servo_stepval 	= ( (SERVO_MAX - SERVO_MIN) / SERVO_STEPS );
		servo_stepnow	= SERVO_MIN;

		// Fill up the LUT
		for (i = 0;i<SERVO_STEPS; i++) {
			servo_stepnow += servo_stepval;
			servo_lut[i] = servo_stepnow;
		}
		// Setup the PWM, etc.  // Kill watchdog timer           // P1.2 = TA1 output
		TA0CCTL1	= OUTMOD_7;            // TACCR1 reset/set
		TA0CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
		TA0CCR0	= PWM_Period-1;        // PWM Period
		TA0CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
		P2DIR &= ~BIT6;
		P2REN &= ~BIT6;
		P1DIR	|= BIT6;               // P1.2 = output
		P1SEL	|= BIT6;
		TA0CCR1 = servo_lut[40]; //40
		__delay_cycles(1000);

		// Setup the PWM, etc.
		TA1CCTL1	= OUTMOD_7;            // TACCR1 reset/set
		TA1CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
		TA1CCR0	= PWM_Period-1;        // PWM Period
		TA1CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
		P2DIR &= ~BIT2;
		P2REN &= ~BIT2;
		P2DIR	|= BIT1;               // P2.1 = output
		P2SEL	|= BIT1;               // P2.1 = TA1 output

		TA1CCR1 = servo_lut[40]; //40
	    __delay_cycles(1000);

	    // Setup the PWM 3
	    TA0CCTL1	= OUTMOD_7;            // TACCR1 reset/set
		TA0CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
		TA0CCR0	= PWM_Period-1;        // PWM Period
		TA0CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
		//TA0CCTL1	= OUTMOD_7;            // TACCR1 reset/set
		P1DIR &= ~BIT6;
		P1REN &= ~BIT6;
		P2DIR |= BIT6;                                   //Set xin as output
		P2SEL &= ~BIT7;                              //Reset Xout select1
		P2SEL |= BIT6;                                  //Set xin select1
		TA0CCR1 = servo_lut[40]; //40
		__delay_cycles(1000);

		// Setup the PWM 4
		TA1CCTL1	= OUTMOD_7;        // Reset/Set PWM
		TA1CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
		TA1CCR0	= PWM_Period-1;        // PWM Period
		TA1CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
		P2DIR &= ~BIT1;				   //Set 2.1 to input
		P2REN &= ~BIT1;                // pull up resistor
		P2DIR	|= BIT2;               // P2.2 = output
		P2SEL	|= BIT2;               // P2.2 = TA1 output
		TA1CCR1 = servo_lut[90]; //0
		__delay_cycles(1000);
}

void ServoONE(void){

	unsigned int servo_stepval, servo_stepnow;
	unsigned int servo_lut[ SERVO_STEPS+1 ];
	unsigned int i;


	// Calculate the step value and define the current step, defaults to minimum.
	servo_stepval 	= ( (SERVO_MAX - SERVO_MIN) / SERVO_STEPS );
	servo_stepnow	= SERVO_MIN;

	// Fill up the LUT
	for (i = 0;i<SERVO_STEPS; i++) {
		servo_stepnow += servo_stepval;
		servo_lut[i] = servo_stepnow;
	}

	// Setup the PWM, etc.  // Kill watchdog timer           // P1.2 = TA1 output
	TA0CCTL1	= OUTMOD_7;            // TACCR1 reset/set
	TA0CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
	TA0CCR0	= PWM_Period-1;        // PWM Period
	TA0CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
	P2DIR &= ~BIT6;
	P2REN &= ~BIT6;
	P1DIR	|= BIT2;               // P1.2 = output
	P1SEL	|= BIT2;


	// Main loop


	TA0CCR1 = servo_lut[0]; //0
	__delay_cycles(1000000);
	TA0CCR1 = servo_lut[40]; //40
  	__delay_cycles(1000000);



}

void ServoTWO(void){

	unsigned int servo_stepval, servo_stepnow;
	unsigned int servo_lut[ SERVO_STEPS+1 ];
	unsigned int i;


	// Calculate the step value and define the current step, defaults to minimum.
	servo_stepval 	= ( (SERVO_MAX - SERVO_MIN) / SERVO_STEPS );
	servo_stepnow	= SERVO_MIN;

	// Fill up the LUT
	for (i = 0;i<SERVO_STEPS; i++) {
		servo_stepnow += servo_stepval;
		servo_lut[i] = servo_stepnow;
	}

	// Setup the PWM, etc.
	TA1CCTL1	= OUTMOD_7;            // TACCR1 reset/set
	TA1CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
	TA1CCR0	= PWM_Period-1;        // PWM Period
	TA1CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
	P2DIR &= ~BIT2;
	P2REN &= ~BIT2;
	P2DIR	|= BIT1;               // P2.1 = output
	P2SEL	|= BIT1;               // P2.1 = TA1 output

	// Main loop


	TA1CCR1 = servo_lut[0]; //0
	__delay_cycles(1000000);
	TA1CCR1 = servo_lut[40]; //40
  	__delay_cycles(1000000);



}

void ServoTHREE(void){

	unsigned int servo_stepval, servo_stepnow;
	unsigned int servo_lut[ SERVO_STEPS+1 ];
	unsigned int i;


	// Calculate the step value and define the current step, defaults to minimum.
	servo_stepval 	= ( (SERVO_MAX - SERVO_MIN) / SERVO_STEPS );
	servo_stepnow	= SERVO_MIN;

	// Fill up the LUT
	for (i = 0;i<SERVO_STEPS; i++) {
		servo_stepnow += servo_stepval;
		servo_lut[i] = servo_stepnow;
	}

	// Setup the PWM, etc.
	TA0CCTL1	= OUTMOD_7;            // TACCR1 reset/set
	TA0CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
	TA0CCR0	= PWM_Period-1;        // PWM Period
	TA0CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
	//TA0CCTL1	= OUTMOD_7;            // TACCR1 reset/set
	P1DIR &= ~BIT2;
	P1REN &= ~BIT2;
	P2DIR |= BIT6;                                   //Set xin as output
	P2SEL &= ~BIT7;                              //Reset Xout select1
	P2SEL |= BIT6;                                  //Set xin select1
	//P2DIR	|= BIT6;               // P1.2 = output
	//P2SEL	|= BIT6;


	// Main loop


	TA0CCR1 = servo_lut[0]; //0
	__delay_cycles(1000000);
	TA0CCR1 = servo_lut[40]; //40
  	__delay_cycles(1000000);



}

void ServoFOUR(topping){

	unsigned int servo_stepval, servo_stepnow;
	unsigned int servo_lut[ SERVO_STEPS+1 ];
	unsigned int i;


	// Calculate the step value and define the current step, defaults to minimum.
	servo_stepval 	= ( (SERVO_MAX - SERVO_MIN) / SERVO_STEPS );
	servo_stepnow	= SERVO_MIN;

	// Fill up the LUT
	for (i = 0;i<SERVO_STEPS; i++) {
		servo_stepnow += servo_stepval;
		servo_lut[i] = servo_stepnow;
	}

	// Setup the PWM, etc.
	TA1CCTL1	= OUTMOD_7;        // Reset/Set PWM
	TA1CTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
	TA1CCR0	= PWM_Period-1;        // PWM Period
	TA1CCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
	P2DIR &= ~BIT1;				   //Set 2.1 to input
	P2REN &= ~BIT1;                // pull up resistor
	P2DIR	|= BIT2;               // P2.2 = output
	P2SEL	|= BIT2;               // P2.2 = TA1 output

	// Main loop

	if(topping == 1)
	{
		TA1CCR1 = servo_lut[170]; //40
	  	__delay_cycles(1000000);
	  	TA1CCR1 = servo_lut[90]; //0
	  	__delay_cycles(1000000);
	}
	else
	{
		TA1CCR1 = servo_lut[10]; //40
		__delay_cycles(1000000);
		TA1CCR1 = servo_lut[90]; //0
		__delay_cycles(1000000);

	}
}

#endif /* SERVOS_H_ */
