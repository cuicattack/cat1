


 	/*
	 * AssemblerApplication1.asm
	 *
	 *  Created: 2/20/2019 5:41:01 PM
	 *   Author: cuicas
	 */ 
	 .org 0

	 LDI xl, low(0x0200) ; low byte in x memory
	 LDI xh, high(0x0200) ; high byte in x memory

	 LDI yl, low(0x0400) ; low byte in y memory
	 LDI yh, high(0x0400) ; high byte in y memory

	 LDI zl, low(0x0600) ; low byte in z memory
	 LDI zh, high(0x0600) ; high byte in z memory

	 LDI R20, 10 ; initalize with 10, but after incremented start register x with value 11
	 LDI R22, 0 ; always stays zero

	 LDI R16, 0 ; high byte of sum of y
	 LDI R17, 0 ; low byte of sum of y

	 LDI R18, 0 ; high byte of sum of z
	 LDI R19, 0 ; low byte of sum of z

	 num99: 
		INC R20	;increment value in register everytime loop begins
		ST x+,R20 ; increments place in x after storing. 
		MOV R21, R20 ; copy the value of R20 without making changes to R20 so that we can manipulate value
		JMP div ; now we want to check if the number is divisable by 3
	div:
		SUBI R21, 3 ; subtract the value by 3 
		CPI R21, 3 ; Compare the subtracted value by 3
		BRSH div ; keep subtracting if  = 3 or greater

		CPI R21, 3 ; compare if value is equal to 3
		BRLO remainders ; if it is lower go to remainders label
	remainders: 
		CPI R21, 0 ; compare if value if equal to zero
		BREQ remzero ; if so branch to remzero, because the number is visible by 3
		JMP remanum ; other wise we do have a remainder and go to remanum

	remzero:
		ADD R17, R20 ; add all numbers that are divisable by 3
		ADC R16, R22 ; add all numbers that are divisable by 3
		ST y+, R20 ; store all the numers that are divisable by 3 in the y array
		JMP compare ; finally jump to compare to see if we are in the last number of the 99 numbers
	remanum:
		ADD R19, R20 ; add all numbers that are not divisable by 3
		ADC R18, R22 ; add all numbers that are not divisable by 3
		ST z+, R20 ; store all the numers that are not divisable by 3 in the z array
		JMP compare ; finally jump to compare to see if we are in the last number of the 99 numbers
	compare: 
		CPI R20, 109 ; compares with 110 to see if it is the final value of the last 99th number
		BRNE num99 ; if not start process all over again
		JMP loop ; otherwise exit the process and jump into the loop and do nothing 
	loop:
		RJMP loop