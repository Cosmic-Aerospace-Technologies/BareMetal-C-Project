#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile static uint32_t ms_counter = 0;

void sysTime_init(void){
//1. Waveform settings
//millis => normal mode 0 - 255 | 1000ms 4x 250ms 24 ms
//millis => 1024ms,

//CTC mode : 249
//sysTime => 0 - 249 gives 250x4 =  1000ms


//Waveform generation mode
TCCR0A |= (1<<WGM01);
TCCR0A &= ~(1<<WGM00);
TCCR0B &= ~(1<<WGM02);

//2. Prescalers
//Ticks by default at 16MHz
//16 000 000 / 64 = 250 000 / 1000ms => 250ticks/1ms

//Prescaler set to 64
TCCR0B |= (1<<CS01);
TCCR0B |= (1<<CS00);
TCCR0B &= ~(1<<CS02);

//3. Calling Interrupts
OCR0A = 249; //Custom overflow flag

TIMSK0 |= (1<<OCIE0A);

sei(); //enables global interrupts

}

ISR(TIMER0_COMPA_vect){
ms_counter++;
}

uint32_t sysTime(void){
    uint32_t time;
    cli(); //stop all interrupts
    time = ms_counter;
    sei(); //start all interrupts
    return time;
}




