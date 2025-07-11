#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void UART_init(uint32_t baud){

uint16_t ubrr_value = (F_CPU/(16UL * baud))-1;
UBRR0H = (uint8_t)(ubrr_value>>8);
UBRR0L = (uint8_t)(ubrr_value);
UCSR0B = (1<<TXEN0); //TX enable
UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); //8-data bits

}

void UART_sendByte(uint8_t data){
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

void printString(const char* str){ //printString("H[0]e[1]l[2]lo World")
    while(*str){
        UART_sendByte(*str++);
    }
}

void printInt(uint32_t value){
char buffer[12];
ultoa(value, buffer, 10);
printString(buffer);
}