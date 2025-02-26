#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
//Definições de macros - empregadas para o trabalho com bits
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) //ativa o bit x da variável
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da variável
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da variável
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) //troca o estado do bit x


    // Cálculo do número de estouros (overflows) necessários
    // Fórmula: (Frequência do Clock / Prescaler) / 256 * Tempo
    // Para 1 segundo: (16.000.000 / 1024) / 256 ? 61
    uint8_t overflows_needed = 61;
    uint8_t overflows = 0;
    unsigned int varr=0;
void delay_1s() {
    


//    while (overflows < 100) {
        
        while (TCNT0 <= 255) {
            // Espera o overflow
        }
//        //clr_bit(TIFR0,TOV0);      // Limpa o flag de overflow
//        overflows++;               // Incrementa a contagem de overflows
//    }
//    overflows = 0;
}

int  main(void) {
// Configuração do Timer0
    TCCR0A = 0x00;                      // Configuração do Timer 0 em Modo normal (contagem simples)
    //TCCR0B = 0B00000101;                  // Prescaler de 1024
    TCCR0B = (1<<CS02) | (1<<CS00);       //TC0 com prescaler de 1024, a 16 MHz gera uma
    TCNT0 =  0;                          // Inicializa o contador com 0
    //TIMSK0 = 1<<TOIE0; //habilita a interrupção do TC0
    sei(); //habilita a chave de interrupção global
    //set_bit(DDRB,DDB5);        // Configuração como saida do pino PB5
    DDRB=0B00100000;
    
    while (1) {
        set_bit(PORTB,PB5);  // troca estado no pino
        while (TCNT0 <= 255) {
           varr++; // Espera o overflow
        }
        TCNT0=0;
        while (TCNT0 <= 255) {
            // Espera o overflow
        }
        TCNT0=0;
        clr_bit(PORTB,PB5);
    }
    
    
    return 0;

}
