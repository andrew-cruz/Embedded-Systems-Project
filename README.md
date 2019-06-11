# Boundless Pac-Mam

## Youtube Link

https://youtu.be/2JLbczwtcHg

## Introduction

### Description

Boundless Pac-Man is a Pac-Man inspired game. There are four enemies in the game
which are the ghost colored red, blue, magenta, and cyan. Pac-Man needs to collect the green
pellets without colliding with any of the ghost.The more pellets that Pac-Man collects the higher
his score goes. The game is over once Pac-Man collides with any of the four ghost.


### User Guide

Once you turn on the game you will be greeted with Pac-Man being chased by his
enemies. The LCD Screen will say Click to start and will show the most recent highscore. Once
you click the joystick down the game will begin.
Push the joystick in any direction to move Pac-Man in that direction. Once Pac-Man
collects a green pellet the score will increase.
If anytime the game needs to be paused you click the joystick down and the game will
freeze. The LCD will say the game is paused. To unpause click the joystick again and the game
will continue.
If Pac-Man touches a ghost(red, blue, magenta, cyan) the game will end. Once the game
ends the score will be displayed on the LCD Screen. The LCD screen will indicate if the score is
a new highscore.
To go back to the home screen click the joystick again.


## Hardware

### Parts List

The hardware that was used in this design is listed below. The equipment that was not
taught in this course has been bolded.
* ATMega1284 microcontroller
* LCD Screen
* __Joystick__
* __Four 74HC595 Shift Register__
* __8x8 RGB LED Dot Matrix__

### Pinout
**PORTA ​(Joystick and Photoresistor)**
PA0: Joystick VRX
PA1: Joystick VRY
PA2: Photoresistor
**PORTB ​(Joystick and LCD Control)**
PB0: Joystick SW
PB5: LCD Control Bus
PB7: LCD Control Bus
**PORTC ​(LCD Data)**
PC0 - PC7: LCD Data Bus
**PORTD ​(Shift Register)**
PD0: SER Input
PD1: RCLK
PD2: SRCLK
PD3: SRCLR
PD4: OE


## Software

### State Machines




### Source Code
● main.c
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;○ Initializes required PORTs
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;○ Schedules and runs tasks
● Io.c​ / ​io.h
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;○ Functions for working with hardware
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;■ LCD Screen
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;■ ADC
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;■ Timer
● led_matrix.c​ / ​led_matrix.h
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;○ Functions for sending data to LED Matrix
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;○ Holds LED Matrix global variables
● SM.c​ / ​SM.h
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;○ Holds all State Machines used
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;○ Controls Joystick, Player, and Enemy movement

## Complexities

### Completed Complexities:
● Implementing the joystick
● Implementing LED Screen
● Implementing shift registers
● Implementing LCD Screen
● Game Logic
● Pseudorandom number generator

## Known Bugs and Shortcomings
● When the game is playing sometimes enemies overlap and make it seem like they’ve
disappeared. This happens because in my enemy move function because I do not check
for collisions between the enemies or pellet. I can begin to debug this by adding another
collision detection inside of the enemy move function.
● Pac-Man seems to move a little too fast. This is because of the period of the joystick
read. I can begin to debug this by manipulating joystick period time.
● Some dots on the LED Matrix are brighter than the others. This is caused by the order
that I send the data to the LED Matrix. I can begin to debug this by switching the order of
the data.
## Future work

I would like to extend the LED Matrix screen to a 16x16 screen for better viewing. I would also
like to implement sound into the game for a more immersive experience. Also I would like to add
EEPROM so I could save the high score without it resetting after turning the game off.
