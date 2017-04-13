/* LCD_Test.c
* Created on: 4/8/2017
* Author: Sterling Collins
* In this program we interface the lcd in 8 bit mode. We send strings and display it on the LCD.
*/


#include "8bit_lcd.h"

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer


	while(1)
	{
		lcd_init();
		send_string(" Candy Machine");
		send_command(0xC0);
		send_string("    Press #");
		delay(100);
		send_command(0xC0);
		lcd_init();
		send_string("Jelly Beans");
		send_command(0xC0);
		send_string("Enter Weight:");
		//send_data(55);
		delay(100);
		send_command(0xC0);
		lcd_init();
		send_string("Skittles");
		send_command(0xC0);
		send_string("Enter Weight:");
		delay(100);
		send_command(0xC0);
		lcd_init();
		send_string("Cherry Sours");
		send_command(0xC0);
		send_string("Enter Weight:");
		delay(100);
		send_command(0xC0);
		lcd_init();
		send_string("Sugar");
		send_command(0xC0);
		send_string("*==No and #==Yes");
		delay(100);
		send_command(0xC0);
		lcd_init();
		send_string("Sprinkles");
		send_command(0xC0);
		send_string("*==No and #==Yes");
		delay(100);
		send_command(0xC0);
		lcd_init();
		send_string("Dispensing...");
		send_command(0xC0);
		send_string("");
		delay(100);
		send_command(0xC0);
		lcd_init();
		send_string("Enjoy!!!");
		send_command(0xC0);
		send_string("");
		delay(100);

	}
}

