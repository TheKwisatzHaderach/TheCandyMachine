#include "msp430g2553.h"

#define TXD BIT2
#define RXD BIT1

const char string[] = { "$GPGGA,120033.15,3334.80219630,N,10152.200000,W,1,05,2.87,992.40,M,-21.3213,M,,*6F" };
char Sent[90];

volatile char rxData = "a";
unsigned int i; //Counter
int j=0; //Sent character counter

/*
 * main.c
 */
int main(void) {
    //WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    DCOCTL = 0; // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ; // Set DCO, smclk set as master clk 1Mhz
    DCOCTL = CALDCO_1MHZ;

    P2DIR |= 0xFF; // All P2.x outputs
    P2OUT &= 0x00; // All P2.x reset this disables port 2
    P1SEL |= RXD + TXD ; // P1.1 = RXD, P1.2=TXD  0x06
    P1SEL2 |= RXD + TXD ; // P1.1 = RXD, P1.2=TXD 0x06

    UCA0CTL1 |= UCSSEL_2; // select the SMCLK as the clock source for the UART module, used to generate the desired baud rate
    UCA0BR0 = 0x08; // 1MHz 115200 1MHz/8= 125000
    UCA0BR1 = 0x00; // 1MHz 115200
    UCA0MCTL = UCBRS2 + UCBRS0; // Modulation UCBRSx = 5 This register in fact is in control of the "modulation": it will select the divider between 8 and 9, therefore switching baud rate during communication to contain the accumulated error. page 424
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
    UC0IE |= UCA0TXIE; // Enable USCI_A0 TX interrupt
    UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt
    UCA0TXBUF = string[i++]; //sends value in rxData
    __bis_SR_register(CPUOFF + GIE); // Enter LPM0 w/ int until Byte RXed

    while (1)
    {

    }

}


#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void) //needs an initial enable
{
	UCA0TXBUF = string[i++]; // TX next character
	if (i == sizeof string - 1) // TX over?
		UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
	//UCA0TXBUF = rxData; //sends value in rxData
    //UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) // triggered when something is in rx
{
	Sent[j++]=UCA0RXBUF;
	UC0IE |= UCA0TXIE;
   //rxData = UCA0RXBUF; //load next character into sent from RX buffer
   //UC0IE |= UCA0TXIE; //enables Tx interupt
}

