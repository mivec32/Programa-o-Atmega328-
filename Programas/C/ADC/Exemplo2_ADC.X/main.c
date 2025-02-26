//* Convers�o ADC � realizada utilizando interrup��o por fim de convers�o do ADC

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//Defini��es de macros - empregadas para o trabalho com bits
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) //ativa o bit x da vari�vel
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da vari�vel
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da vari�vel
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) //troca o estado do bit x


volatile uint16_t adc_value = 0;

void ADC_Init() {
    set_bit(ADMUX,REFS0);       // Refer�ncia de tens�o AVcc
    ADCSRA=0B10001111;          // Habilita ADC e configura prescaler para 128 (16MHz/128 = 125kHz)
    set_bit(ADCSRA,ADIE);       // Habilita interrup��o do ADC
    sei();                      // Habilita interrup��es globais
}

ISR(ADC_vect) {
    cpl_bit(PORTB,PB0);         // Podemos observar o periodo de amostragem( leva 13 clocks do adc =8u*13))
    adc_value = ADC;            // L� o valor do ADC quando a convers�o � conclu�da
    set_bit(ADCSRA,ADSC);       // Inicia uma nova convers�o
}

int main(void) {
    DDRD = 0xFF;                // Configura PORTD como sa�da
    DDRB = 0x0F;                // Configura PORTB como sa�da
    ADC_Init();
    set_bit(ADCSRA,ADSC);       // Inicia a primeira convers�o
    while (1) {
        PORTD = adc_value >> 2; // Envia o valor do ADC para PORTD
        _delay_ms(100);         // Delay simples
    }
}