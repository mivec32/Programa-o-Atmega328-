#include <avr/io.h>
#include <util/delay.h>

void motor_step(uint8_t step)
{
    // Define os pinos de controle (PD0 a PD3) de acordo com o passo
    PORTB = (PORTB & 0xF0) | (step & 0x0F);  // Limpa os 4 bits inferiores e escreve o passo
    
}

int main(void)
{
    // Configura os pinos PB0 a PB3 como saída para controlar o ULN2003
    DDRB = 0B00001111;
    while (1)
    {
        // Gira o motor para frente
        motor_step(0x01);  // Passo 1  0B0000 0001
        _delay_ms(800);    // Atraso para o motor avançar
        motor_step(0x02);  // Passo 2  0B 0000 0010
        _delay_ms(800);    // Atraso para o motor avançar
        motor_step(0x04);  // Passo 3  0B 0000 0100
        _delay_ms(800);    // Atraso para o motor avançar
        motor_step(0x08);  // Passo 4 0B 0000 1000
        _delay_ms(800);    // Atraso para o motor avançar
        
    }

    return 0;
}
