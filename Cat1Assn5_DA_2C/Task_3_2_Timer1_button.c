/*
 * GccApplication2.c
 *
 * Created: 3/16/2019 2:02:12 PM
 * Author : cuicas
 * DA-2C -2 pushbutton
 * RUNNING ON 8MHZ
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

// initialize timer, interrupt and variable
void timer1_init()
{
	TCCR1B |= (1 << WGM12)|(1 << CS12)|(1 << CS10); // prescaler 1024 and CTC mode
	OCR1A = 9765;// initialize compare value
	OCR1B = 
	TIMSK1 |= (1 << OCIE1A) |(1 << OCIE1B); // enable compare interrupt
	sei(); 	// enable global interrupts

}

int main(void)
{
	DDRB |= (1 << 0);

	timer1_init();
	while(1)
	{
	}
}
ISR (TIMER1_COMPA_vect)
{
	if(PINC & _BV(PINC2))
	{
		PORTB ^=(1 << 0);
	}
}
