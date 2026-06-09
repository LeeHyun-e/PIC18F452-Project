# PIC18F452 Timer0 LED Control

## 프로젝트 개요

본 프로젝트는 PIC18F452 8-bit MCU에서 Timer0 인터럽트를 활용하여 PORTD에 연결된 LED를 주기적으로 토글하는 예제입니다.  
MCU 내부 레지스터를 직접 정의하고 제어함으로써 Timer0, Interrupt, Prescaler, GPIO 출력 동작을 학습하는 것을 목표로 했습니다.

## 사용 MCU

- MCU: PIC18F452
- Clock: 16 MHz
- Timer: Timer0
- Timer Mode: 8-bit Timer Mode
- Output Port: PORTD
- Development Level: Register-level programming

## 주요 학습 내용

- PIC18F452의 SFR 주소 기반 레지스터 직접 제어
- `union`과 bit-field를 이용한 레지스터 비트 단위 접근
- `TRISD` 레지스터를 이용한 GPIO 출력 설정
- `T0CON` 레지스터를 이용한 Timer0 설정
- `INTCON` 레지스터를 이용한 Timer0 interrupt enable
- Timer0 overflow interrupt를 이용한 주기적 LED 제어
- Polling 방식이 아닌 Interrupt 기반 제어 구조 이해

## 코드 동작 방식

1. `TRISD` 레지스터를 `0x00`으로 설정하여 PORTD 전체를 출력으로 설정합니다.
2. `PORTD` 초기값을 `0x00`으로 설정하여 LED 출력을 초기화합니다.
3. `INTCON` 레지스터에서 Global Interrupt, Peripheral Interrupt, Timer0 Interrupt를 활성화합니다.
4. `T0CON` 레지스터에서 Timer0를 8-bit Timer mode로 설정하고 내부 클럭을 사용하도록 설정합니다.
5. Timer0가 오버플로우될 때마다 interrupt service routine이 실행됩니다.
6. ISR 내부에서 overflow 횟수를 count하고, 특정 횟수에 도달하면 PORTD 전체 출력을 반전시켜 LED를 토글합니다.

## 핵심 코드 설명

### GPIO 설정

```c
My_TRISD.byte = 0x00;
My_PORTD.byte = 0x00;
```
### Interrupt 설정

```c
My_INTCON.GIE = 1;
My_INTCON.PEIE = 1;
My_INTCON.TMR0IF = 0;
My_INTCON.TMR0IE = 1;
```
GIE를 통해 전체 인터럽트를 허용하고, TMR0IE를 통해 Timer0 overflow interrupt를 활성화했습니다.
TMR0IF는 Timer0 overflow 발생 여부를 나타내는 flag이므로, 초기화 과정에서 0으로 clear했습니다.

### Timer0 설정
```c
My_T0CON.T0PS0 = 1;
My_T0CON.T0PS1 = 0;
My_T0CON.T0PS2 = 0;
My_T0CON.PSA = 0;
My_T0CON.T0CS = 0;
My_T0CON.T08BIT = 1;
My_T0CON.TMR0ON = 1;
```
T0CS = 0으로 설정하여 Timer0의 clock source로 내부 instruction cycle clock을 사용했습니다.
T08BIT = 1을 통해 Timer0를 8-bit mode로 설정했고, PSA = 0으로 prescaler를 Timer0에 할당했습니다.
마지막으로 TMR0ON = 1을 설정하여 Timer0 동작을 시작했습니다.

### Timer0 Interrupt Service Routine
```c
void __interrupt() Isr_Tmr0(void)
{
    if(My_INTCON.TMR0IF == 1)
    {
        My_INTCON.TMR0IF = 0;
        count++;

        if(count == 7812)
        {
            count = 0;
            My_PORTD.byte = ~My_PORTD.byte;
        }
    }
}
```
Timer0 overflow가 발생하면 TMR0IF flag가 set되고 ISR이 실행됩니다.
ISR 내부에서는 먼저 interrupt flag를 clear한 뒤, overflow 발생 횟수를 count 변수로 누적합니다.
지정한 횟수에 도달하면 PORTD 전체 값을 반전시켜 LED 상태를 토글합니다.

Timer0 주기 계산

본 코드에서는 16 MHz oscillator를 기준으로 Timer0를 내부 clock source로 사용했습니다.

Oscillator frequency: 16 MHz
Instruction clock: Fosc / 4 = 4 MHz
Prescaler: 1:4
Timer0 input clock: 1 MHz
Timer0 tick period: 1 us
8-bit overflow period: 256 us

따라서 Timer0 overflow가 7812회 발생하면 약 2초가 됩니다.

256 us × 7812 ≈ 1.999872 s

즉, 현재 설정에서는 약 2초마다 PORTD 출력이 반전됩니다.


