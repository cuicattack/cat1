

 /*
 * AssemblerApplication1.asm
 *
 *  Created: 2/8/2019 3:15:14 PM
 *   Author: cuicas
 */ 


	 .include "m328Pdef.inc"
	 .ORG 0000

	 LDI R23,0 ; This Register stays zero for ADC opperations later
	 
	 LDI R20,0 ; R20-18 will hold values of result
	 LDI R19,0
	 LDI R18,0 
	 
	 LDI R25,0x00 ; R25-R24 hold the 16 bit multiplicand
	 LDI R24,0xFF ; 

	 LDI R22,0xFF; R22 holds 8 bit multiplier 

	loop: 
		;Addding 
		ADD R18,R24
		ADC R19,R25
		ADC R20,R23

		dec R22 ; Decrement to keep track of number of loops(multiplier)
		brne loop ; Branch until R22 = 0 is 0
	Done: jmp Done ; loop



	 LDI R23,0 ; This Register stays zero for ADC opperations later
	 
	 LDI R20,0 ; R20-18 will hold values of result
	 LDI R19,0
	 LDI R18,0 
	 
	 LDI R25,0xFF ; These hold multiplicand
	 LDI R24,0xFF 

	 LDI R22,0xFF; R25-R24 hold the 16 bit multiplicand

	MUL R24, R22 ; Mul the lower bytes. Answer stored in R0 carry in R1
	ADD R18, R0 ; This will store the answer in R18 bc R18 was 0
	ADC R19, R1 ; Carry from MUL added to R19, setting it to 1 if carry or 0 otherwise

	MUL R25,R22 ; Mul the top byte of 16bit. Answer stored in R0 carry in R1
	ADD R19, R0 ; This will store the answer in R19 
	ADC R20, R1 ; in case there is a cary in the MUL opperation
	Done: jmp Done ; loop 