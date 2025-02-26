// Recepção de Dados e Echo
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
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

char USART_Receive() {
    while (!(UCSR0A & (1 << RXC0))); // Aguarda o dado ser recebido
    return UDR0; // Retorna o dado recebido
}

int main(void) {
    USART_Init();

    while (1) {
        char received_data = USART_Receive(); // Recebe um caractere
        USART_Transmit(received_data); // Retransmite o caractere (echo)
    }
}