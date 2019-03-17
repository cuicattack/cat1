/*
 * GccApplication2.c
 *
 * Created: 3/16/2019 2:02:12 PM
 * Author : cuicas
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
//RUNNING ON 8MHZ
int main (void)
{
	DDRB = _BV(PINB2); //all other pins on PORT b are inputs, but we are setting Pin2 as output
	TCCR1B = (1<<CS12) | (1<<CS10);//setting these bits specifically to 5 so pre-scaler is 1024
		
	PORTD |= (1 << PORTD2);    // turn On the Pull-up// PD2 is now an input with pull-up enabled
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0);     // Turns on INT0
	sei();                    // turn on interrupts
	TIMSK1 = (1<<TOIE1);
	while (1)
	{
	}
}

ISR(TIMER1_OVF_vect)
{
	while(1)
	{
		if(PINC & _BV(PINC2)) // if the button is pressed then perform the following events
		{
			TCNT1 = 0x00; // restart clock so that we can wait until 1.25
			PORTB = _BV(PINB2); //turn on pin B	
			while(TCNT1 <= 0x2625 ) // while the clock is less than 1.25 s
			{
			}	
			PORTB = 0x00; // ONCE 1.25 s are over turn off LED
		}
	}
}
