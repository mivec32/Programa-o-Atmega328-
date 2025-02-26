//controla um motor de passo unipolar usando o driver ULN2003. 
//O código irá girar o motor para a direita se o pino PD0 for 1 lógico
//e para a esquerda se o pino PD1 for 1 lógico.

#include <avr/io.h>
#include <util/delay.h>

void motor_step(uint8_t step)
{
    // Define os pinos de controle (PB0 a PD3) de acordo com o passo
    PORTB = (PORTB & 0xC0) | (step & 0x3F);  // Limpa os 2 bits mais significativos e escreve os 6 bits inferiores
}

void rotate_right()
{
    // Gira o motor para a direita
    motor_step(0x01);  // Passo 1
    _delay_ms(200);
    motor_step(0x02);  // Passo 2
    _delay_ms(200);
    motor_step(0x04);  // Passo 3
    _delay_ms(200);
    motor_step(0x08);  // Passo 4
    _delay_ms(200);
}

void rotate_left()
{
    // Gira o motor para a esquerda (sequência invertida)
    motor_step(0x08);  // Passo 4
    _delay_ms(200);
    motor_step(0x04);  // Passo 3
    _delay_ms(200);
    motor_step(0x02);  // Passo 2
    _delay_ms(200);
    motor_step(0x01);  // Passo 1
    _delay_ms(200);
}

int main(void)
{
    // Configura os pinos PD0 e PD1 como entradas para direção
    DDRD &= ~(1 << PD0);  // PD0 como entrada (direção para a direita)
    DDRD &= ~(1 << PD1);  // PD1 como entrada (direção para a esquerda)
    
    // Configura os pinos PB0 a PB3 como saída para controlar o ULN2003
    DDRB = 0x0F;  // Define os pinos PB0 a PB3 como saída (controle do motor)
    
    while (1)
    {
        // Verifica se o pino PD0 está em 1 lógico (girar para a direita)
        if (PIND & (1 << PD0))
        {
            rotate_right();  // Gira o motor para a direita
        }
        // Verifica se o pino PD1 está em 1 lógico (girar para a esquerda)
        else if (PIND & (1 << PD1))
        {
            rotate_left();  // Gira o motor para a esquerda
        }
    }

    return 0;
}
