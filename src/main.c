#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "sysTime.h"
#include "UART.h"
#include "ADC.h"

//Timer flags
uint32_t lastBlinkTime = 0;
uint32_t lastPressTime = 0;
uint32_t lastPotTime = 0;
uint32_t lastCheckTime = 0;


uint16_t potVal0 = 0;
uint16_t potVal1 = 0;

bool messageState = false;

int main(void){
sei();
ADC_init();
sysTime_init();
UART_init(9600);
DDRB |= (1<<PB1); //PB1 OUTPUT
DDRB |= (1<<PB0); 
DDRD &= ~(1<<PD7); //Button Input
PORTD |= (1<<PD7);
PORTC &= ~(1<<PC0);
//DDRB = DDRB | (1<<PB1);  DDRB = 0b00000000 | 0b00000010 = 0b00000010

    while(1){

//time 0 | current = 0, last = 0
//time 1 | current = 1, last = 0 => last = currentTime
//time 2 | current = 2, last = 1 => last = currentTime

potVal0 = ADC_read(0);
potVal1 = ADC_read(1);
int BLINK_DURATION = (625 * potVal0)/125;
if(potVal0 <= 20) BLINK_DURATION = 0;
if(potVal0 >= 1010) BLINK_DURATION = 5000;

uint32_t currentTime = sysTime();

//Blink - LED

if(currentTime - lastCheckTime >= 1000){
    printString("Time: "); printInt(currentTime); printString("\r\n");
    lastCheckTime = currentTime;
}

if(currentTime - lastBlinkTime >= BLINK_DURATION){
PORTB ^= (1<<PB1);
lastBlinkTime = currentTime;
}

//Button - LED
if(currentTime - lastPressTime >= 5){ //Debounce
if(!(PIND & (1<<PD7))){
    PORTB |= (1<<PB0); //ON
    if(messageState == false){
        printString("Hello World! \r\n");
        messageState = true;
    }
    
    lastPressTime = currentTime;
}else{
    PORTB &= ~(1<<PB0); //OFF
    messageState = false;
}
}

if(currentTime - lastPotTime >= 100){
    //printString("Pot Value: "); printInt(potVal1); printString("\r\n");
    lastPotTime = currentTime;
}

}

    return 0;
}
