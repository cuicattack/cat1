;
; AssemblerApplication1.asm
;
; Created: 2/28/2019 5:46:51 PM
; Author : cuicas
;
; RUNNING ON 1MHz
	.org 0
	LDI R16,32 ;representing Port B pin 5
	OUT DDRB, R16 ;enable PB5 as output
	LDI R17,0 ;used to set or reset PB5
	LDI R20,5 ;set clock prescaler to 1024
	STS TCCR1B,R20 ; acutally set the prescaler

	Begin:		
		LDI R20,0x00 ;resetting the counter to 0
		STS TCNT1H,R20
		STS TCNT1L,R20
		OUT PORTB,R16 ;LED starts as high
		RJMP TimeLB1 ; jump to Time Lower Bite for clock one to that we check the time

	TimeLB1:
		 LDS R29, TCNT1H ;loading upper bit of counter to R29
		 LDS R28, TCNT1L ;loading lower bit of counter to R28
		 CPI R28,LOW(0x01A9) ;comparing if lower 8 bits of timer is LOW(0x01A8)
		 BRSH TimeHB1 ;check the upper bits
		 RJMP TimeLB1 ;keep checking lower bits
	TimeHB1:
		 CPI R29,HIGH(0x01A9) ;check to see if upper timer bits have reached the desired value
		 BRNE TimeLB1 ;go back and check the lower bits
		 RJMP Off ;once the timer reached the desired value, toggle the LED
	Off:
		LDI R20,0x00 ;resetting the counter to 0
		STS TCNT1H,R20
		STS TCNT1L,R20
		OUT PORTB,R17 ; turn off led pin 5
		RJMP TimeLB2 ; check the off time lower bits
	TimeLB2:
		 LDS R29, TCNT1H ;loading upper bit of counter to R29
		 LDS R28, TCNT1L ;loading lower bit of counter to R28
		 CPI R28,LOW(0x011B) ;comparing if lower 8 bits of timer is LOW(0x011C)
		 BRSH TimeHB2 ; check the upper bits
		 RJMP TimeLB2 ; keep checking lower bits
	TimeHB2:
		 CPI R29,HIGH(0x011B) ;check to see if upper timer bits have reached the desired value
		 BRNE TimeLB2 ;recheck lower bits
		 JMP Begin ;loop back to begining and start over again
	/*R29 holds upper bit of calculation. 
	  R28 holds lower bit of calculation.
	  TCNT = 1(MHz)*0.435(secs)/1024  -1  = 423.804 (decimal)= 0x01A8 (hex)*/
