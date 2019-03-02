/*
 * GccApplication3.c
 * Created: 2/28/2019 11:22:17 AM
 * Author : cuicas
 * HW: #2 in C
 */ 

#include <avr/io.h>
//RUNNING ON 8MHZ
int main (void)
{
	DDRB = _BV(PINB2); //all other pins on PORT b are inputs, but we are setting Pin2 as output
	TCCR1B = (1<<CS12) | (1<<CS10);//setting these bits specifically to 5 so pre-scaler is 1024
	
	while (1)
	{
			if(1)//if(PINC & _BV(PINC2)) // if the button is pressed then perform the following events
			{
				TCNT1 = 0x00; // restart clock so that we can wait until 1.25
				PORTB = _BV(PINB2); //turn on pin B
				
				while(TCNT1 <= 0x2625 ) // while the clock is less than 1.25 s
				{
				}
				
				PORTB = 0x00; // ONCE 1.25 s are over turn off LED
			}
	}
		
		return 0;
	}
