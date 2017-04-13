/* 8bit_lcd.h
* Created on: 01-29-2017
* Author: Sterling Collins
*/
#include <msp430.h>

#define DR          P2OUT = P2OUT | BIT0 // define RS high
#define CWR         P2OUT = P2OUT & (~BIT0) // define RS low
#define READ        P2OUT = P2OUT | BIT1 // define Read signal R/W = 1 for reading
#define WRITE       P2OUT = P2OUT & (~BIT1) // define Write signal R/W = 0 for writing
#define ENABLE_HIGH P2OUT = P2OUT | BIT2 // define Enable high signal
#define ENABLE_LOW  P2OUT = P2OUT & (~BIT2) // define Enable Low signal
unsigned int i;
unsigned int j;
void delay(unsigned int k)
 {
     for(j=0;j<=k;j++)
      {
          for(i=0;i<1000;i++);

      }


 }
void data_write(void)
 {
     ENABLE_HIGH;
     delay(2);
     ENABLE_LOW;
 }

void data_read(void)
 {
     ENABLE_LOW;
     delay(2);
     ENABLE_HIGH;
 }

void check_busy(void)
 {
      P1DIR &= ~(BIT7); // make P1.7 as input
while((P1IN&BIT7)==1)
{
      data_read();
   }
      P1DIR |= BIT7; // make P1.7 as output
 }

void send_command(unsigned char cmd)
{
    check_busy();
    WRITE;
    CWR;
    P1OUT = (P1OUT & 0X00)|(cmd);
    data_write(); // give enable trigger

}

void send_data(unsigned char data)
{
    check_busy();
    WRITE;
    DR;
    P1OUT = (P1OUT & 0X00)|(data);
    data_write(); // give enable trigger
}

void send_string(char *s)
{
    while(*s)
   {
        send_data(*s);
         s++;
       }
    }

    void lcd_init(void)
    {
    P2DIR |= 0xFF;
    P1DIR |= 0xFF;
    P2OUT &= 0X00;
    P1OUT &= 0X00;
    send_command(0x38); // 8 bit mode
    send_command(0x0E); // clear the screen
    send_command(0x01); // display on cursor on
    send_command(0x06);// increment cursor
    send_command(0x80);// cursor position
    }
