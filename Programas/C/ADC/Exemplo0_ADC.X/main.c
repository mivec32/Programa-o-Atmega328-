//*Este exemplo faz a leitura de um �nico canal ADC (ADC0) e envia os 8 bits    *//
//mais significativos da convers�o pela porta PORTD                             *//

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//Defini��es de macros - empregadas para o trabalho com bits
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) //ativa o bit x da vari�vel
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da vari�vel
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da vari�vel
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) //troca o estado do bit x



void ADC_Init() {
    set_bit(ADMUX,REFS0);                       // Refer�ncia de tens�o AVcc
    ADCSRA=0B10001111;                          // Habilita ADC e configura prescaler para 128 (16MHz/128 = 125kHz)
}

uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // Seleciona o canal ADC setando nos 4 bits menos significativos do ADMUX
    set_bit(ADCSRA,ADSC);                      // Inicia a convers�o
    while (tst_bit(ADCSRA,ADSC)==1);           // Aguarda o fim da convers�o
    return ADC;                                // Retorna o valor convertido
}

int main(void) {
    DDRD = 0xFF; // Configura PORTD como sa�da (para simular um display ou LED)
    ADC_Init();

    while (1) {
        uint16_t adc_value = ADC_Read(0); // L� o valor do ADC0
        PORTD = adc_value >> 2; // Ajusta o valor de 10 bits para 8 bits e envia para PORTD
        _delay_ms(100); // Delay simples
    }
}