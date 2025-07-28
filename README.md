# PIC18F452_LED_Flow_Timer0_8bit-Project
제어 연구실 레지스터 제어 프로젝트


// Definition of necessary register typedefs

//TMR0L
typedef union 
{
    struct{
        unsigned            :1;
        unsigned            :1;
        unsigned            :1;
        unsigned            :1;
        unsigned            :1;
        unsigned            :1;
        unsigned            :1;
        unsigned            :1;

    };
    unsigned char byte;
}TMR0L_t;

extern volatile TMR0L_t My_TMR0L               __at(0xFD6);

//T0CON
typedef union 
{
    struct{
        unsigned T0PS0      :1;
        unsigned T0PS1      :1;
        unsigned T0PS2      :1;
        unsigned PSA        :1;
        unsigned T0SE       :1;
        unsigned T0CS       :1;
        unsigned T08BIT     :1;
        unsigned TMR0ON     :1;

    };
    unsigned char byte;
}T0CON_t;

extern volatile T0CON_t My_T0CON                __at(0xFD5);

//INTCON - PEIE/GIE
typedef union 
{
    struct{

        unsigned RBIF       :1;
        unsigned INT0IF     :1;
        unsigned TMR0IF     :1;
        unsigned RBIE       :1;
        unsigned INT0IE     :1;
        unsigned TMR0IE     :1;
        unsigned PEIE       :1;
        unsigned GIE        :1;

    };
    unsigned char byte;
}INTCON_t;

extern volatile INTCON_t My_INTCON              __at(0xFF2);

//TRISD
typedef union 
{
    struct{
        unsigned TRISD0     :1;
        unsigned TRISD1     :1;
        unsigned TRISD2     :1;
        unsigned TRISD3     :1;
        unsigned TRISD4     :1;
        unsigned TRISD5     :1;
        unsigned TRISD6     :1;
        unsigned TRISD7     :1;

    };
        unsigned char byte;
}TRISD_t;

extern volatile TRISD_t My_TRISD               __at(0xF95);

//PORTD
typedef union 
{
    struct{
        unsigned PORTD0     :1;
        unsigned PORTD1     :1;
        unsigned PORTD2     :1;
        unsigned PORTD3     :1;
        unsigned PORTD4     :1;
        unsigned PORTD5     :1;
        unsigned PORTD6     :1;
        unsigned PORTD7     :1;

    };
    unsigned char byte;
}PORTD_t;

extern volatile PORTD_t My_PORTD               __at(0xF83);


// Start of code //LED_Flow_Timer0_8bit

#define _XTAL_FREQ 16000000   // Define the crystal oscillator frequency as 16 MHz

#pragma config OSC = HS     // Configure oscillator: High-Speed PLL enabled
#pragma config WDT = OFF    // Turn off Watchdog Timer to prevent unexpected resets during development
#pragma config PWRT = OFF   // Disable Power-up Timer to speed up startup time during development
#pragma config BOR = OFF    // Disable Brown-out Reset to avoid resets when voltage dips slightly during development


unsigned int count = 0;


void INTCON_Init();
void T0CON_Init();




void main(void) {
    
    My_TRISD.byte = 0x00;
    My_PORTD.byte = 0x00;
    

    INTCON_Init();
    T0CON_Init();

    while(1)
    {

    }

}




void INTCON_Init() 
{
    My_INTCON.GIE = 1;   
    My_INTCON.PEIE = 1;  
    //My_INTCON.RBIF      
    //My_INTCON.INT0IF
    My_INTCON.TMR0IF = 0;     
    //My_INTCON.RBIE      
    //My_INTCON.INT0IE    
    My_INTCON.TMR0IE = 1;  
}



void T0CON_Init()
{

    My_T0CON.T0PS0 = 1;  // Timer0 Prescaler Select bits
    My_T0CON.T0PS1 = 0;
    My_T0CON.T0PS2 = 0; 
    My_T0CON.PSA = 0; // Prescaler assigned to Timer0
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
