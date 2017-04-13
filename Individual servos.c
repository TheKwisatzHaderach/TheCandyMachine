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












/*#include "msp430g2553.h" // make sure you change the header to suit your particular device.

// Connect the servo SIGNAL wire to P1.2 through a 1K resistor.

#define MCU_CLOCK			1000000
#define PWM_FREQUENCY		50		// In Hertz, ideally 50Hz.

#define SERVO_STEPS			180		// Maximum amount of steps in degrees (180 is common)
#define SERVO_MIN			600	// The minimum duty cycle for this servo
#define SERVO_MAX			2500	// The maximum duty cycle

unsigned int PWM_Period		= (MCU_CLOCK / PWM_FREQUENCY);	// PWM Period
unsigned int PWM_Duty		= 0;							// %


void main (void){

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
	WDTCTL	= WDTPW + WDTHOLD;     // Kill watchdog timer
	TACCTL1	= OUTMOD_7;            // TACCR1 reset/set
	TACTL	= TASSEL_2 + MC_1;     // SMCLK, upmode
	TACCR0	= PWM_Period-1;        // PWM Period
	TACCR1	= PWM_Duty;            // TACCR1 PWM Duty Cycle
	P1DIR	|= BIT2;               // P1.2 = output
	P1SEL	|= BIT2;               // P1.2 = TA1 output

	// Main loop
	while (1){


		TACCR1 = servo_lut[0]; //0
		__delay_cycles(1000000);
		TACCR1 = servo_lut[40]; //40
  		__delay_cycles(1000000);


	}
}
*/
