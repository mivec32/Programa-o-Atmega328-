//Configuração Básica do USART e Transmissão de Dados
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void USART_Init() {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8); // Configura o baud rate
    UBRR0L = (uint8_t)(UBRR_VALUE);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Habilita transmissão e recepção
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Modo assíncrono, 8 bits de dados, 1 bit de parada, sem paridade
}

void USART_Transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Aguarda o buffer de transmissão estar vazio
    UDR0 = data; // Envia o dado
}

void USART_TransmitString(const char *str) {
    while (*str) {
        USART_Transmit(*str++); // Envia cada caractere da string
    }
}

int main(void) {
    USART_Init();

    while (1) {
        USART_TransmitString("Hello, World!\r\n"); // Envia a string
        _delay_ms(1000); // Delay de 1 segundo
    }
}