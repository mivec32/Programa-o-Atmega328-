//criando uma temporização de 100ms
#include <avr/io.h>
#include <avr/interrupt.h>

//Definições de macros para o trabalho com bits 
#define set_bit(y,bit) (y|=(1<<bit))//coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit))//coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit))//troca o estado lógico do bit x da variável Y



#define F_CPU 8000000UL  // Frequência do clock interno (8 MHz)
unsigned int x=0;        //criamos a variavel para contar os milisegundos

// Interrupção do TIMER 0
ISR(TIMER0_OVF_vect) {
    cpl_bit(PORTB,PORTB0);      // Alterna o estado do LED 
    x=x+1;                      //incrementa seu valor a cada 1ms
    if(x>=100)                  // compara se for maior que 100ms, entao
    {

       cpl_bit(PORTB,PORTB1);   // Alterna o estado do LED 
        x=0;                    // reseta o contador
    }
 
TCNT0 = 131;   // carrega contador para 1m s
}

int main(void) {
    
    set_bit(DDRB,DDB0);     // Configura o pino PB0 como saída
    clr_bit(PORTB,PORTB0);  // Garante que o LED esteja inicialmente desligado
    set_bit(DDRB,DDB1);     // configura o pino PB1 como saida
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
