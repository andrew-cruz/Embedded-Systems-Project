/*
 * Embedded_PacMan_Project.c
 *
 * Created: 5/22/2019 2:56:52 PM
 * Author : Andrew Cruz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "io.c"


int main(void)
{
	
	 DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	 DDRA = 0xFF; PORTA = 0x00; // LCD control lines
	 DDRB = 0xFF; PORTB = 0x00;
	 
	 // Initializes the LCD display
	 LCD_init();
	 
	 // Starting at position 1 on the LCD screen, writes Hello World
	 LCD_DisplayString(1, "Hello World");
	 
	 //PORTB = 0xFF;
	 
	 while(1) {continue;}
		 
}

