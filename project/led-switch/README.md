# Lab 2: Blinky-Buzzy Toy
Project controls msp430 using its four switches.
-Pressing SW1 turns GREEN LED on
-Pressing SW2 turns RED LED on.
-Pressing SW3 turns BOTH LEDs on at the same time.
-SW4 changes the state of the BUZZER.
     1. BUZZER will be off upon start up( state 0).
     2. Pressing SW4 once will activate BUZZER at a higher frequency(state 1)
     3. Pressing SW4 twice will activate BUZZER at a lower frequency(state 2).
     4. Pressing SW4 a third time will turn BUZZER off(state 0).

-Using libTimer to ensure everything is running as it should and as long as it
 needs to.
-File containing Assembly language is included, which builds the
 toggle_buzzer_state.
-Makefile helps run the program.
	  1. make: compiles all the codes
	  2. make load: loads all code into msp430.
	  3. make clean: cleans all compiled programs.

Brayan Mendoza, LAB 2
