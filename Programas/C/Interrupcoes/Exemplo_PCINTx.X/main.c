#define F_CPU 16000000UL //frequ�ncia de trabalho
#include <avr/io.h> //defini��es do componente especificado
#include <avr/interrupt.h> //define algumas macros para as interrup��es
#include <util/delay.h> //biblioteca para o uso das rotinas de delay
//Defini��es de macros para o trabalho com bits
#define set_bit(y,bit) (y|=(1<<bit))//coloca em 1 o bit x da vari�vel Y
#define clr_bit(y,bit) (y&=~(1<<bit))//coloca em 0 o bit x da vari�vel Y
#define cpl_bit(y,bit) (y^=(1<<bit))//troca o estado l�gico do bit x da vari�vel Y
#define tst_bit(y,bit) (y&(1<<bit))//retorna 0 ou 1 conforme leitura do bit
#define LED0 PD5
#define LED1 PD6
#define LED2 PD7

ISR(PCINT1_vect)
{
//quando houver mais de um pino que possa gerar a interrup��o � necess�rio testar qual foi
if(!tst_bit(PINC,PC0))
cpl_bit(PORTD,LED0);
else if(!tst_bit(PINC,PC1))
cpl_bit(PORTD,LED1);
else if(!tst_bit(PINC,PC2))
cpl_bit(PORTD,LED2);
_delay_ms(200);
}

int main()
{
DDRC = 0x00; //PORTC como entrada, 3 bot�es
PORTC = 0xFF; //habilita pull-ups
DDRD = 0b11100000; //pinos PD5:7 do PORTC como sa�da (leds)
PORTD = 0xFF; //apaga leds e habilita pull-ups dos pinos n�o utilizados
PCICR = 0b00000010; //habilita interrup��o por qualquer mudan�a de sinal no PORTC
PCMSK1 = 0b00000111; //habilita os pinos PCINT8:10 para gerar interrup��o
sei(); //habilita as interrup��es
while(1){}
}