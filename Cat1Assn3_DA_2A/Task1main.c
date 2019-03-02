/*
 * GccApplication1.c
 * Created: 2/27/2019 6:54:28 PM
 *  Author: cuicas
 */ 
//RUNNING OFF 1MHZ
	#include <avr/io.h>
	int main ()
	{
		DDRB = 0xff; //set all of portB to output
		TCCR1B = (1<<CS12) | (1<<CS10);//setting these bits specifically 5 so that pre-scaler is 1024
		int count = 0; //this is how I will control the sequence of events so LED is on first.
		
		while (1)
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
		return 0;}
		// on time 0x1A8 = 0.435 s
		// off time 0x11A = 0.29 s, but after simulating closer to 0x11C