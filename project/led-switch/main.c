#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (LED_RED | LED_GREEN)

//switches are 2.0, .1, .2, .3
#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

#define BUZZER BIT6
//used to store buzzer_state as well, since I had problems keeping the leds/buzzer on
extern char toggle_buzzer_state();

void switch_init();
void switch_interrupt_handler();
void handle_buzzer_button();
char buzzer_state = 0;

//sets the switches/toggles
void switch_init() {
  P2REN |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  P2IE |= SWITCHES;
  P2IES |= SWITCHES;
  P2IFG &= ~SWITCHES;

}

//from chat GPT. Buzzer would not turn on at all
void __attribute__((interrupt(PORT2_VECTOR))) Port_2() {
  switch_interrupt_handler();
  P2IFG &= ~SWITCHES;

}
//sets buzzer
void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR |= BIT6;
}
//frequency for the buzzer
void buzzer_set_frequency(int frequen){
  CCR0 = frequen;
  CCR1 = frequen >> 1;
}
//sets the state of buzzer, which then changes the frequency
void handle_buzzer_button(){
  toggle_buzzer_state();
  if(buzzer_state ==1){
    //higher pitch
    buzzer_set_frequency(1000);
  }else if(buzzer_state == 2){
    //lower pitch
    buzzer_set_frequency(2000);
  }else{
    //off
    buzzer_set_frequency(0);
    buzzer_state = 0;
  }
}
//switches fot the leds and buzzer.
void switch_interrupt_handler() {
  char p2val = P2IN;
  char switches = ~p2val & SWITCHES;
  //turns green led on
  if (!(p2val & SW1)) {
    P1OUT ^= LED_RED;
  }
  //turns red led on
  if (!(p2val & SW2)) {
    P1OUT ^= LED_GREEN;
  }
  //turns both leds on
  if(!(p2val & SW3)){
    P1OUT ^= LED_GREEN;
    P1OUT ^= LED_RED;
  }
  //looking for buzzer button
  if(switches & SW4){
    handle_buzzer_button();
  }
  P2IFG &= ~SWITCHES;
}
int main(void){
  WDTCTL = WDTPW | WDTHOLD;
  configureClocks();
  BCSCTL1 = CALBC1_1MHZ; //not sure what these are or how they work but after looking around
  DCOCTL = CALDCO_1MHZ; //this fixed my issues with the buzzer
  buzzer_init();
  
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
  switch_init();
 
  __enable_interrupt();
   or_sr(0x18);
   while(1);
}
