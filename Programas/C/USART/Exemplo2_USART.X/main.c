//Uso de Interrupção para Recepção de Dados
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

volatile char received_data = 0;

void USART_Init() {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8); // Configura o baud rate
    UBRR0L = (uint8_t)(UBRR_VALUE);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // Habilita transmissão, recepção e interrupção na recepção
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Modo assíncrono, 8 bits de dados, 1 bit de parada, sem paridade
    sei(); // Habilita interrupções globais
}

void USART_Transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Aguarda o buffer de transmissão estar vazio
    UDR0 = data; // Envia o dado
}

ISR(USART_RX_vect) {
    received_data = UDR0; // Armazena o dado recebido
    USART_Transmit(received_data); // Retransmite o dado (echo)
}

int main(void) {
    USART_Init();

    while (1) {
        // O loop principal pode realizar outras tarefas
        _delay_ms(100); // Delay simples
    }
}