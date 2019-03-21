/*
 * GccApplication2.c
 *
 * Created: 3/16/2019 2:02:12 PM
 * Author : cuicas
 * RUNNING OFF 1MHZ
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
void timer1_init()
{
	TCCR1B |= (1 << WGM12)|(1 << CS12)|(1 << CS10); //prescaler = 1024 and CTC mode
	OCR1A = 424;//0x01A8;// on time initialize compare value
	OCR1B = 0x011A; // off time
	TIMSK1 |= (1 << OCIE1A)|(1 << OCIE1B); // enable compare interrupt
	sei(); 	// enable global interrupts

}
int main(void)
{
	DDRB |= (1 << 1); // set portb pin1 as output
	timer1_init();
	while(1)
	{
	}
}
ISR (TIMER1_COMPA_vect)
{	
	PORTB = 0x02; // turn on LED
}
ISR (TIMER1_COMPB_vect)
{
	PORTB = 0x00; // Turn off LED
}