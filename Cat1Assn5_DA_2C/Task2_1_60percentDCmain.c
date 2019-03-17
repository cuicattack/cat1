/*Gabriela Cucas
 *RUNNING OFF 1MHZ
 * 2C-2 - which is 2A-1: period of .725 s 
*/
#include <avr/io.h>
#include <avr/interrupt.h>
int main ()
{
	DDRB = 0xff; //set all of portB to output
	TCCR1B = (1<<CS12) | (1<<CS10);//setting these bits specifically 5 so that pre-scaler is 1024
	
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
		int count = 0; //this is how I will control the sequence of events so LED is on first.
		while(1)
		{
			if (count %2 == 0) //this is how I will control the sequence of events so LED is on first.
			{
				PORTB = 0x02; // turn on LED
				TCNT1 = 0x00; // restart clock
				while (TCNT1<=0x01A8) //the amount of time in hex = 0.435s LED is on
				{
				}
				count+=1; // increase count so that next event turns off LED
			}
			else
			{
				PORTB = 0x00; // turn off LED
				TCNT1 = 0x00; // restart clock
				while (TCNT1<=0x011A) // desired off time in hex = 0.29
				{
				}
				count+=1; // increase count so that next event turns on LED
			}	
		}
	}

// on time 0x1A8 = 0.435 s
// off time 0x11A = 0.29 s, but after simulating closer to 0x11C