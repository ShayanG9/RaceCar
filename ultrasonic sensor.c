/*
 * Ultrasonic sensor.c
 *
 * Created: 2022-02-10 20:28:31
 * Author : han_c
 */ 
#define BAUD 9600
#define F_CPU 16000000

#define trigPin 4
#define echoPin 3

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/setbaud.h>

static volatile int pulse = 0;
static volatile int i = 0;

void initUSART(){
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (3<<UCSZ00) | (1<<UCSZ01);
}

void USART_Transmit(char character){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = character;
}

void USART_Output(char *text){
	for(int i=0; i<255;i++)
	{
		if(text[i] != 0)
		{
			USART_Transmit(text[i]);
		}
		else
		{
			break;
		}
	}
}


int main(void)
{
	int16_t count = 0;
	char string[16];
	DDRC = 1<<PINC3 | 0 << PINC2;

	EICRA |= 1 << ISC00;
	PCMSK1 |= 1 << PCINT10 | 1 << PCINT11;
	PCICR |= 1 << PCIE1;
	
	initUSART();
	sei();
    while (1) 
    {
		PORTC |= 1<<PINC3;
		_delay_ms(15);
		PORTC &= ~(1<<PINC3);
		count = pulse/100;
		USART_Output("Distance: ");
		itoa(count, string, 10);
		USART_Output(string);
		USART_Output(" cm\n");
    }
	return 0;
}

ISR(PCINT1_vect){
	if(i == 0)
	{
		TCCR1B |= 1<<CS11;
		i = 1;
	}
	else
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}
}

