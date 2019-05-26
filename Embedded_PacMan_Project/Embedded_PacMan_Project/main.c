/*
 * Embedded_PacMan_Project.c
 *
 * Created: 5/22/2019 2:56:52 PM
 * Author : Andrew Cruz
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include <math.h>

#include "io.h"
#include "scheduler.h"
#include "SM.h"
#include "led_matrix.h"


// Implement scheduler code from PES.
int main()
{
	// Set Data Direction Registers
	/*
	Input from JoyStick A0-A2
	Input from Buttons A3-A4
	*/
	DDRA = 0x00;PORTA = 0xFF;
	/*
	Output to speaker
	Output Data Lines to LCD B6-B7
	*/
	DDRB = 0xFF;PORTB = 0x00;
	/*
	Output to LCD Data Lines
	*/
	 DDRC = 0xFF; PORTC = 0x00;
	/*
	Output to LEDMatrix
	*/
	DDRD = 0xFF; PORTD = 0x00;

	// Period for the tasks
	unsigned long int SMTick1_calc = 50;
	unsigned long int SMTick2_calc = 500;
	unsigned long int SMTick3_calc = 1000;
	unsigned long int SMTick4_calc = 10;

	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
	tmpGCD = findGCD(tmpGCD, SMTick3_calc);
	tmpGCD = findGCD(tmpGCD, SMTick4_calc);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick1_period = SMTick1_calc/GCD;
	unsigned long int SMTick2_period = SMTick2_calc/GCD;
	unsigned long int SMTick3_period = SMTick3_calc/GCD;
	unsigned long int SMTick4_period = SMTick4_calc/GCD;

	//Declare an array of tasks
	static task task1, task2, task3, task4;
	task *tasks[] = { &task1, &task2, &task3, &task4 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = SMTick1_period;//Task Period.
	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
	task1.TickFct = &LCD_SM;//Function pointer for the tick.

	// Task 2
	task2.state = -1;//Task initial state.
	task2.period = SMTick2_period;//Task Period.
	task2.elapsedTime = SMTick2_period;//Task current elapsed time.
	task2.TickFct = &Button_SM;//Function pointer for the tick.

	// Task 3
	task3.state = -1;//Task initial state.
	task3.period = SMTick3_period;//Task Period.
	task3.elapsedTime = SMTick3_period; // Task current elasped time.
	task3.TickFct = &LED_SM; // Function pointer for the tick.

	// Task 4
	task4.state = -1;//Task initial state.
	task4.period = SMTick4_period;//Task Period.
	task4.elapsedTime = SMTick4_period; // Task current elasped time.
	task4.TickFct = &SMTick4; // Function pointer for the tick.

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	// Error: Program should not exit!
	return 0;
}



// int main(void)
// {

//
//
// 	// Initializes the LCD display
// 	LCD_init();
//
// 	// Starting at position 1 on the LCD screen, writes Hello World
// 	LCD_DisplayString(1, "Pac-Man");
// 	LCD_DisplayString(2, "Start | Reset");
//
// 	//PORTB = 0xFF;
// 	 adc_init();
//
// 	while(1) {
//
// 		unsigned char button0 = GetBit(~PINA,3);
// 		unsigned char button1 = GetBit(~PINA,4);
//
// 		//unsigned char x_axis = GetBit(PINA, 0);
// 		//unsigned char y_axis = GetBit(PINA,1);
// 		//unsigned char z_axis = GetBit(PINA, 2);
// 		/*
// 		if(button0 == 0x01) {
// 			PORTB = 0x01;
// 		}
// 		if(button1 == 0x01) {
// 			PORTB = 0x02;
// 		}
// 		*/
//
// 		int16_t x_axis = adc_read(0);  // Value of ADC register now stored in variable x. 0x 0000 0011 1111 1111
// 		int16_t y_axis = adc_read(1);
//
//
// 		if( y_axis >= 1023 && x_axis <= 1023 ) {
// 			PORTB = 0x08;
// 		} else if( y_axis <= 25 && x_axis <= 1023) {
// 			PORTB = 0x01;
// 		} else if(x_axis <= 225 && y_axis <= 1023) {
// 			PORTB = 0x04;
// 		} else if(x_axis >= 1023 && y_axis <= 1023) {
// 			PORTB = 0x02;
// 		} else if(GetBit(~PINA,2) == 0x01) {
// 			PORTB = 0x0F;
// 		} else {
// 			PORTB = 0x00;
// 		}
//
//
//
// 		//PORTB = lower;
// 		//PORTD = upper;
// 	}
//
// }
