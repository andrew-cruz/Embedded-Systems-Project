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
#include "SM.c"
#include "led_matrix.c"

// Implement scheduler code from PES.
int main()
{
	// Set Data Direction Registers
	/*
	Input from JoyStick A0-A2
	Input from Light Sensor A3
	*/
	DDRA = 0x00;PORTA = 0xFF;
	/*
	Input from Joysti
	Output to speaker
	Output Data Lines to LCD B6-B7
	*/
	DDRB = 0xFE;PORTB = 0x01;
	/*
	Output to LCD Data Lines
	*/
	DDRC = 0xFF; PORTC = 0x00;
	/*
	Output to LEDMatrix
	Shift regs
	*/
	DDRD = 0xFF; PORTD = 0x00;

	// Period for the tasks
	unsigned long int game_sm_period = 100;
	unsigned long int joystick_sm_period = 100;
	unsigned long int button_sm_period = 100;
	unsigned long int player_sm_period = 100;
	unsigned long int enemy_sm_period = 350;
	unsigned long int led_sm_period = 5;
	unsigned long int lcd_sm_period = 100;
	unsigned long int sound_sm_period = 100;

	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(game_sm_period, joystick_sm_period);
	tmpGCD = findGCD(tmpGCD, button_sm_period);
	tmpGCD = findGCD(tmpGCD, player_sm_period);
	tmpGCD = findGCD(tmpGCD, enemy_sm_period);
	tmpGCD = findGCD(tmpGCD, led_sm_period);
	tmpGCD = findGCD(tmpGCD, lcd_sm_period);
	tmpGCD = findGCD(tmpGCD, sound_sm_period);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	game_sm_period = game_sm_period/GCD;
	joystick_sm_period = joystick_sm_period/GCD;
	button_sm_period = button_sm_period/GCD;
	player_sm_period = player_sm_period/GCD;
	enemy_sm_period = enemy_sm_period/GCD;
	led_sm_period = led_sm_period/GCD;
	lcd_sm_period = lcd_sm_period/GCD;
	sound_sm_period = sound_sm_period/GCD;

	//Declare an array of tasks
	static task task_game, task_joystick, task_button, task_player, task_enemy, task_led, task_lcd, task_sound;
	task *tasks[] = { &task_game, &task_joystick, &task_button, &task_player, &task_enemy, &task_led, &task_lcd, &task_sound};
	const unsigned short num_tasks = sizeof(tasks)/sizeof(task*);

	// Game task
	task_game.state = -1;//Task initial state.
	task_game.period = game_sm_period;//Task Period.
	task_game.elapsedTime = game_sm_period;//Task current elapsed time.
	task_game.TickFct = &GameSM;//Function pointer for the tick.
	// Joystick task
	task_joystick.state = -1;//Task initial state.
	task_joystick.period = joystick_sm_period;//Task Period.
	task_joystick.elapsedTime = joystick_sm_period;//Task current elapsed time.
	task_joystick.TickFct = &JoystickSM;//Function pointer for the tick.
	// Button task
	task_button.state = -1;//Task initial state.
	task_button.period = button_sm_period;//Task Period.
	task_button.elapsedTime = button_sm_period;//Task current elapsed time.
	task_button.TickFct = &ButtonSM;//Function pointer for the tick.
	// Player task
	task_player.state = -1;//Task initial state.
	task_player.period = player_sm_period;//Task Period.
	task_player.elapsedTime = player_sm_period;//Task current elapsed time.
	task_player.TickFct = &PlayerSM;//Function pointer for the tick.
	// Enemy task
	task_enemy.state = -1;//Task initial state.
	task_enemy.period = enemy_sm_period;//Task Period.
	task_enemy.elapsedTime = enemy_sm_period;//Task current elapsed time.
	task_enemy.TickFct = &EnemySM;//Function pointer for the tick.
	// LED Matrix task
	task_led.state = -1;//Task initial state.
	task_led.period = led_sm_period;//Task Period.
	task_led.elapsedTime = led_sm_period;//Task current elapsed time.
	task_led.TickFct = &LEDMatrixSM;//Function pointer for the tick.
	// LCD Screen task
	task_lcd.state = -1;//Task initial state.
	task_lcd.period = lcd_sm_period;//Task Period.
	task_lcd.elapsedTime = lcd_sm_period;//Task current elapsed time.
	task_lcd.TickFct = &LCDScreenSM;//Function pointer for the tick.
	// Sound task
	task_sound.state = -1;//Task initial state.
	task_sound.period = sound_sm_period;//Task Period.
	task_sound.elapsedTime = sound_sm_period;//Task current elapsed time.
	task_sound.TickFct = &SoundSM;//Function pointer for the tick.

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();
	//Initializes PORTA for ADC
	ADCInit();
	//Initializes PORTC for LCD Screen
	LCDInit();
	// Scheduler for-loop iterator
	unsigned short i;
	unsigned char seed = RandomNum();
	srand(seed);

	while(1) {
		// Scheduler code
		for ( i = 0; i < num_tasks; i++ ) {
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
