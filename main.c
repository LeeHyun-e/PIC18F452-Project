#include "pic18f452_registers.h"

#define _XTAL_FREQ 16000000   // Define the crystal oscillator frequency as 16 MHz

#pragma config OSC = HS     // Configure oscillator: High-Speed PLL enabled
#pragma config WDT = OFF    // Turn off Watchdog Timer to prevent unexpected resets during development
#pragma config PWRT = OFF   // Disable Power-up Timer to speed up startup time during development
#pragma config BOR = OFF    // Disable Brown-out Reset to avoid resets when voltage dips slightly during development

unsigned int count = 0;

void INTCON_Init();
void T0CON_Init();

void main(void) {
    
    My_TRISD.byte = 0x00; //pin output setup
    My_PORTD.byte = 0x00; //reset pin
    
    INTCON_Init(); 
    T0CON_Init(); 

    while(1)
    {

    }

}

void INTCON_Init() 
{
    My_INTCON.GIE = 1;       // Global Interrupt Enable bit
    My_INTCON.PEIE = 1;      // Peripheral Interrupt Enable bit
    //My_INTCON.RBIF      
    //My_INTCON.INT0IF
    My_INTCON.TMR0IF = 0;   // Timer0 Overflow Interrupt Flag bit
    //My_INTCON.RBIE      
    //My_INTCON.INT0IE    
    My_INTCON.TMR0IE = 1;  // Timer0 Overflow Interrupt Enable bit
}
void T0CON_Init()
{

    My_T0CON.T0PS0 = 1;  
    My_T0CON.T0PS1 = 0;
    My_T0CON.T0PS2 = 0; 
    // Timer0 Prescaler Select bits
    // T0PS2:T0PS0 = 001 → Prescaler 1:4
    
    My_T0CON.PSA = 0; // Prescaler Assignment bit to Timer0
    My_T0CON.T0SE = 0; // Increment on low-to-high transition (rising edge)
    My_T0CON.T0CS = 0; // Clock source = internal instruction cycle clock (Fosc/4)
    My_T0CON.T08BIT = 1;  //Timer0 8-bit/16-bit Control bit
    My_T0CON.TMR0ON = 1;  // Timer0 On/Off Control bit 

}
void __interrupt() Isr_Tmr0(void)
{
    
    if(My_INTCON.TMR0IF == 1)
    {
        My_INTCON.TMR0IF = 0;
        count++;
        
        // Timer0 clock = Fosc/4/2 = 16MHz/4/2 = 2MHz (0.5us period)
        // 8-bit overflow period = 256 * 0.5us = 128us
        // 1 second = 1,000,000us / 128us ≈ 7812 overflow counts
        if(count == 7812)
        {
            count = 0;
           
            My_PORTD.byte = ~My_PORTD.byte;  //LED Toggle
        }
    }
}





