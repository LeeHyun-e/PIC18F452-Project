// 필요한 레지스터 타입 정의
#ifndef PIC18F452_REGISTERS_H
#define PIC18F452_REGISTERS_H

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

#endif
