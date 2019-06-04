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

#include "io.c"
#include "scheduler.c"
#include "SM.c"
#include "led_matrix.c"


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
	unsigned long int SMTick1_calc = 100;
	unsigned long int SMTick2_calc = 100;
	unsigned long int SMTick3_calc = 5;
	unsigned long int SMTick4_calc = 100;
	unsigned long int joyStickSM_calc = 100;

	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
	tmpGCD = findGCD(tmpGCD, SMTick3_calc);
	tmpGCD = findGCD(tmpGCD, SMTick4_calc);
	tmpGCD = findGCD(tmpGCD, joyStickSM_calc);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick1_period = SMTick1_calc/GCD;
	unsigned long int SMTick2_period = SMTick2_calc/GCD;
	unsigned long int SMTick3_period = SMTick3_calc/GCD;
	unsigned long int SMTick4_period = SMTick4_calc/GCD;
	unsigned long int joyStickSM_period = joyStickSM_calc/GCD;

	//Declare an array of tasks
	static task task1, task2, task3, task4, task5;
	task *tasks[] = { &task1, &task2, &task3, &task4, &task5 };
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
	task3.TickFct = &LED_Matrix_SM; // Function pointer for the tick.

	// Task 4
	task4.state = -1;//Task initial state.
	task4.period = SMTick4_period;//Task Period.
	task4.elapsedTime = SMTick4_period; // Task current elasped time.
	task4.TickFct = &LED_Light_SM; // Function pointer for the tick.

	// Task 5
	task5.state = -1;//Task initial state.
	task5.period = joyStickSM_period;//Task Period.
	task5.elapsedTime = joyStickSM_period; // Task current elasped time.
	task5.TickFct = &joyStickSM; // Function pointer for the tick.

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; // Scheduler for-loop iterator

	//shiftInit();

		 adc_init();
		 LCD_init();

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
