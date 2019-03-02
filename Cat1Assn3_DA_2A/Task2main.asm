; AssemblerApplication1.asm
;
; Created: 2/28/2019 5:46:51 PM
; Author : cuicas
; RUNNING ON 8 MHz
.org 0

	SBI DDRB, 2 ;pin 2 is output

	LDI R20,5 ;set clock prescaler to 1024
	STS TCCR1B,R20
	Main:
		IN R16, PINC ; read all pins
		ANDI R16, 0b00000100; only care about pin 2
		//LDI R16, 4 // for simulation purposes 
		CPI R16, 4 ; if the button is pressed values are the same
		BRNE Main ; if values are not the same then jump back to main and keep reading pinC
		RJMP Pressed ; otherwise it is pressed and start timer
	
	Pressed:
		LDI R20,0x00 ;resetting the counter to 0
		STS TCNT1H,R20
		STS TCNT1L,R20
		SBI PORTB,2 ; turn on LED
		RJMP Time1 ; Check the counter for the lower bits we want

	Time1:
		LDS R29, TCNT1H ;loading upper bit of counter to R29
		LDS R28, TCNT1L ;loading lower bit of counter to R28
		CPI R28, LOW(0x2625) ;comparing if lower 8 bits of timer is 0x08
		BRSH Time2 ; check higher bits
		//RJMP Time1 ; keep checking lower bits

	Time2:
		CPI R29, HIGH(0x2625) ;check to see if upper timer bits have reached the desired value
		BRNE Time1 ;if not, recheck the lower bits
		RJMP Turnoff ;once the timer reached the desired value, toggle the LED

	Turnoff:
		LDI R21, 0 ;
		OUT PORTB, R21 ; turn off led and restart process
		RJMP Main ; restart process. 
