#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL  // Frequência do clock interno (8 MHz)

#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y



// Configuração do TIMER 0


// Interrupção do TIMER 0
ISR(TIMER0_OVF_vect) { 
cpl_bit(PORTB,PORTB0);  // Alterna o estado do LED 
TCNT0 = 131;   // carrega contador para 1m s
}

int main(void) {
    // Configura o pino PB0 como saída
    DDRB =0B00000001;
    // Garante que o LED esteja inicialmente desligado
    PORTB=0B00000000;
    // Configuração do TIMER 0
    //configura do TIMER 0 com interrupção de overflow para criar a base de tempo
    TCCR0A = 0x00; // Modo normal
    TCCR0B = 0x03; // Prescaler de 1:64
    TIMSK0 = 0x01; // Habilita interrupção do timer 0
    TCNT0 = 131; // Inicializa o contador para iniciar em 131, assim teremos 1ms
    //T=(prescaler*(MAX-TCNT0))/Fclock, onde max neste casso 256
    sei(); // Habilita interrupções globais
    
    

    while (1) {
        // Loop principal vazio, a lógica está na interrupção
    }

    return 0;
}
