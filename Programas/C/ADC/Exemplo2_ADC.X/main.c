//* Conversão ADC é realizada utilizando interrupção por fim de conversão do ADC

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//Definições de macros - empregadas para o trabalho com bits
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) //ativa o bit x da variável
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da variável
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da variável
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) //troca o estado do bit x


volatile uint16_t adc_value = 0;

void ADC_Init() {
    set_bit(ADMUX,REFS0);       // Referência de tensão AVcc
    ADCSRA=0B10001111;          // Habilita ADC e configura prescaler para 128 (16MHz/128 = 125kHz)
    set_bit(ADCSRA,ADIE);       // Habilita interrupção do ADC
    sei();                      // Habilita interrupções globais
}

ISR(ADC_vect) {
    cpl_bit(PORTB,PB0);         // Podemos observar o periodo de amostragem( leva 13 clocks do adc =8u*13))
    adc_value = ADC;            // Lê o valor do ADC quando a conversão é concluída
    set_bit(ADCSRA,ADSC);       // Inicia uma nova conversão
}

int main(void) {
    DDRD = 0xFF;                // Configura PORTD como saída
    DDRB = 0x0F;                // Configura PORTB como saída
    ADC_Init();
    set_bit(ADCSRA,ADSC);       // Inicia a primeira conversão
    while (1) {
        PORTD = adc_value >> 2; // Envia o valor do ADC para PORTD
        _delay_ms(100);         // Delay simples
    }
}