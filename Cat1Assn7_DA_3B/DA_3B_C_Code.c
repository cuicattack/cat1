/*
 * GccApplication1.c
 *
 * Created: 3/30/2019 2:56:14 PM
 * Author : cuicas
 */ 
#define F_CPU 8000000UL //running on 8MHz
#define BAUD 9600 //baud rate
#define UBRR  (F_CPU/(16UL * BAUD)) - 1 // to set up UBRR0H and UBRR0L
#define ADC5 0x05 // reading
#define AVCC 5000 //5V
#define PRECISION 1024
#define scale (AVCC/PRECISION)//5000/1024
#include <avr/io.h>
#include <util/delay.h>

void usart_Transmit(uint8_t data);
void usart_Message(uint8_t* msg);
uint8_t  usart_Receive(void);
uint16_t readADC(uint8_t ADCchannel);

void main (void)
{
	uint16_t volt; //declare variable
	uint8_t temp; //declare variable
	TCCR1B = (1<<CS12)|(1<<CS10); //Start timer, set prescaler to 1024
	
	UBRR0H = (uint8_t)(UBRR>>8); //setting baud rate
	UBRR0L = (uint8_t)UBRR; //setting baud rate
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);//Enable receiver and transmitter
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);   // 8bit data format
	
	ADMUX |= (1<<REFS0)|(1<<MUX2)|(1<<MUX0); // AVCC with ext capacitor at AREF pin and input ADC5
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //enable ADC, set prescaler to 128
	
	while(TCNT1<=0x0F42)//ADD a half a second DELAY
	{
	}
	usart_Transmit('Temperature in Degrees Celsius \n\r');
	while(1){
		volt = readADC(ADC5); //read voltage from this pin
		volt = ((scale*volt)/10) + 2; //convert the voltage
		if (volt >= 100){
			temp = (volt % 100)/10;
		}
		else{
			temp = volt / 10;
		}
		usart_Transmit(temp + 48); //voltage in Celsius 
		TCNT1 = 0x00; //reset timer
		while(TCNT1<=0x1E84)//ADD a second DELAY
		{
		}
	}
}
void usart_Transmit(uint8_t data){
	while (!( UCSR0A & (1<<UDRE0))) ; // wait till reg is free
	UDR0 = data;  // load data in the register
}
uint8_t  usart_Receive(void)
{	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
void usart_Message(uint8_t* msg)
{
	while(*msg){
		usart_Transmit(*msg); //transmit message
		msg ++;	
	}
}
uint16_t readADC(uint8_t ADCchannel){
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);//reset the ADMUX to adjust reading
	ADCSRA |= (1 << ADSC);//start conversion
	while(ADCSRA & (1<<ADSC));	//Wait until ADC conversation complete. ADSC will be ZERO after completion.
	return ADC; //return ADC value 
}