//=============================================================================== //
// Este programa controla a potência entregue para uma carga resistiva usando PWM //
// O cruzamento por zero da tensão da rede é identificada para posicionar a fase  //
// por meio do PWM.                                                               //
//=============================================================================== //
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Definições de macros para o trabalho com bits
#define set_bit(y,bit) (y|=(1<<bit))//coloca em 1 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit))//troca o estado lógico do bit x da variável Y
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da variável Y

#define F_CPU 8000000UL  // Frequência do clock interno (8 MHz)
#define TRIAC_PIN PB0   // Pino conectado ao gate do TRIAC
#define ZERO_CROSS_PIN PD2 // Pino de entrada para o cruzamento por zero (INT0)

// Variáveis globais
 volatile uint8_t zero_cross_detected = 0; // Flag para o cruzamento por zero
 volatile uint8_t angulo_disparo = 0;      // Ângulo de disparo (0° a 180°)
 volatile uint16_t delay_ticks = 0;       // Ticks para o atraso desejado

// Inicialização do Timer 0
void timer0_init(void) {
    TCCR0A = 0x00; // Modo normal
    //Com preescaler de 1/8 teremos desbordamento do timer a cada 255us
    //T=(8*255)/(Fosc)
    set_bit(TCCR0B,CS01);  //Prescaler de 1:8
    set_bit(TIMSK0,TOIE0); // Habilita interrupção por desbordamento do Timer 0
}

// Inicialização da interrupção externa (cruzamento por zero)
void external_interrupt_init(void) {
    EICRA = (1 << ISC01); // Interrupção na borda de descida (cruzamento por zero)
    EIMSK = (1 << INT0);  // Habilita interrupção externa INT0
}

// Interrupção de cruzamento por zero
ISR(INT0_vect) {
    zero_cross_detected = 1; // Marca que o cruzamento por zero ocorreu
    TCNT0 = 0;               // Reinicia o Timer 0
    delay_ticks = 0;         // Reinicia o contador de ticks
}

// Interrupção de overflow do Timer 0
ISR(TIMER0_OVF_vect) {
    
    if (zero_cross_detected) {
        delay_ticks++;

        // Calcula o número de ticks correspondente ao ângulo de disparo
        // Cada tick do Timer 0 com prescaler de 1:8 e F_CPU = 8 MHz equivale a 1 µs, desbordando em 255 us
        // Para 60 Hz, um semiciclo dura 8.33 ms (8333 µs)
        // Em 8333 us / 255 us =32.67 desbordamentos de timer 0, atingiremos 180 graus da onda senoidal
        // Assim, o ângulo de disparo é mapeado para a cuantidade de desbordamentos
        //=(firing_angle * 32.67) / 180 ;
        uint16_t target_ticks =(angulo_disparo * 32.67) / 180 ;;
        

        if (delay_ticks >= target_ticks) {
            set_bit(PORTB,TRIAC_PIN);  // Dispara o TRIAC
            _delay_us(10);             // Pulso de 10 µs
            clr_bit(PORTB,TRIAC_PIN);  // Desliga o pulso
            zero_cross_detected = 0;   // Reseta a flag
        }
    }
}

int main(void) {
    
    set_bit(DDRB,TRIAC_PIN);     // Configura o pino do TRIAC como saída
    clr_bit(PORTB,TRIAC_PIN);   // Garante que o TRIAC esteja inicialmente desligado

    // Inicializa o Timer 0 e a interrupção externa
    timer0_init();
    external_interrupt_init();

    // Habilita interrupções globais
    sei();

    while (1) {
        // O controle é gerenciado pelas interrupções
        // Aqui você pode ajustar o ângulo de disparo (firing_angle) conforme necessário
        // Exemplo: firing_angle = 90; // Define o ângulo de disparo para 90°
        angulo_disparo =90 ;
    }

    return 0;
}