#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "sysTime.h"
#include "UART.h"
#include "ADC.h"
#include "PWM.h"

//Timer flags
uint32_t lastBlinkTime = 0;
uint32_t lastPressTime = 0;
uint32_t lastPotTime = 0;
uint32_t lastCheckTime = 0;

uint16_t BLINK_DURATION = 0;
uint8_t  BRIGHTNESS = 0;

uint16_t potVal0 = 0;
uint16_t potVal1 = 0;

bool messageState = false;

int main(void){
// SETUP
sei();
sysTime_init();
UART_init(9600);
ADC_init();
PWM_init();

DDRB |= (1<<PB1);  // D9 - GREEN
DDRB |= (1<<PB0);  // D8 - BLUE
DDRD &= ~(1<<PD7); // BUTTON
DDRC &= ~(1<<PC0); // POT 1
DDRC &= ~(1<<PC1); // POT 2

PORTD|= (1<<PD7);  // Button as Active High

// MAIN LOOP
while(1){

potVal0 = ADC_read(0);
potVal1 = ADC_read(1);

BLINK_DURATION = (625UL * potVal0)/125;
BRIGHTNESS = (255UL*potVal1)/1023;

if(potVal0 <= 20) BLINK_DURATION = 0;
if(potVal0 >= 1000) BLINK_DURATION = 5000;
if(potVal1 <= 20) BRIGHTNESS = 0;
if(potVal1 >= 1000) BRIGHTNESS = 255;
uint32_t currentTime = sysTime();

/* ================= SYSTEM TIME PRINTER ====================  */
if(currentTime - lastCheckTime >= 1000){
    printString("Time: "); printInt(currentTime); printString("\r\n");
    lastCheckTime = currentTime;
}

/* ================= LED BLINKER ==================== */
if(currentTime - lastBlinkTime >= BLINK_DURATION){
    static bool ledState = false;

    if (ledState) {
        LED_brightness(0); // OFF
    } else {
        LED_brightness(BRIGHTNESS); // ON
    }

    ledState = !ledState;
    lastBlinkTime = currentTime;
}


/* ================= 'HELLO WORLD BUTTON' ==================== */
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

/* ==================== PRINTING POT VALUES ====================== */
if(currentTime - lastPotTime >= 100){
    //printString("Pot Value: "); printInt(potVal0); printString("\r\n");
    lastPotTime = currentTime;
}



}

    return 0;
}
