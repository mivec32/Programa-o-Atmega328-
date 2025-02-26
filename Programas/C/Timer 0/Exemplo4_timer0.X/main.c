//=============================================================================== //
// Este programa controla a pot�ncia entregue para uma carga resistiva usando PWM //
// O cruzamento por zero da tens�o da rede � identificada para posicionar a fase  //
// por meio do PWM.                                                               //
//=============================================================================== //
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Defini��es de macros para o trabalho com bits
#define set_bit(y,bit) (y|=(1<<bit))//coloca em 1 o bit x da vari�vel Y
#define cpl_bit(y,bit) (y^=(1<<bit))//troca o estado l�gico do bit x da vari�vel Y
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da vari�vel Y

#define F_CPU 8000000UL  // Frequ�ncia do clock interno (8 MHz)
#define TRIAC_PIN PB0   // Pino conectado ao gate do TRIAC
#define ZERO_CROSS_PIN PD2 // Pino de entrada para o cruzamento por zero (INT0)

// Vari�veis globais
 volatile uint8_t zero_cross_detected = 0; // Flag para o cruzamento por zero
 volatile uint8_t angulo_disparo = 0;      // �ngulo de disparo (0� a 180�)
 volatile uint16_t delay_ticks = 0;       // Ticks para o atraso desejado

// Inicializa��o do Timer 0
void timer0_init(void) {
    TCCR0A = 0x00; // Modo normal
    //Com preescaler de 1/8 teremos desbordamento do timer a cada 255us
    //T=(8*255)/(Fosc)
    set_bit(TCCR0B,CS01);  //Prescaler de 1:8
    set_bit(TIMSK0,TOIE0); // Habilita interrup��o por desbordamento do Timer 0
}

// Inicializa��o da interrup��o externa (cruzamento por zero)
void external_interrupt_init(void) {
    EICRA = (1 << ISC01); // Interrup��o na borda de descida (cruzamento por zero)
    EIMSK = (1 << INT0);  // Habilita interrup��o externa INT0
}

// Interrup��o de cruzamento por zero
ISR(INT0_vect) {
    zero_cross_detected = 1; // Marca que o cruzamento por zero ocorreu
    TCNT0 = 0;               // Reinicia o Timer 0
    delay_ticks = 0;         // Reinicia o contador de ticks
}

// Interrup��o de overflow do Timer 0
ISR(TIMER0_OVF_vect) {
    
    if (zero_cross_detected) {
        delay_ticks++;

        // Calcula o n�mero de ticks correspondente ao �ngulo de disparo
        // Cada tick do Timer 0 com prescaler de 1:8 e F_CPU = 8 MHz equivale a 1 �s, desbordando em 255 us
        // Para 60 Hz, um semiciclo dura 8.33 ms (8333 �s)
        // Em 8333 us / 255 us =32.67 desbordamentos de timer 0, atingiremos 180 graus da onda senoidal
        // Assim, o �ngulo de disparo � mapeado para a cuantidade de desbordamentos
        //=(firing_angle * 32.67) / 180 ;
        uint16_t target_ticks =(angulo_disparo * 32.67) / 180 ;;
        

        if (delay_ticks >= target_ticks) {
            set_bit(PORTB,TRIAC_PIN);  // Dispara o TRIAC
            _delay_us(10);             // Pulso de 10 �s
            clr_bit(PORTB,TRIAC_PIN);  // Desliga o pulso
            zero_cross_detected = 0;   // Reseta a flag
        }
    }
}

int main(void) {
    
    set_bit(DDRB,TRIAC_PIN);     // Configura o pino do TRIAC como sa�da
    clr_bit(PORTB,TRIAC_PIN);   // Garante que o TRIAC esteja inicialmente desligado

    // Inicializa o Timer 0 e a interrup��o externa
    timer0_init();
    external_interrupt_init();

    // Habilita interrup��es globais
    sei();

    while (1) {
        // O controle � gerenciado pelas interrup��es
        // Aqui voc� pode ajustar o �ngulo de disparo (firing_angle) conforme necess�rio
        // Exemplo: firing_angle = 90; // Define o �ngulo de disparo para 90�
        angulo_disparo =90 ;
    }

    return 0;
}