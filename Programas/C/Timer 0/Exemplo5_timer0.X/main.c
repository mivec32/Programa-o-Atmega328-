//Gera dois sinais PWM pelos pinos PD5 e PD6
#include <avr/io.h>

#define F_CPU 16000000UL // Frequência do microcontrolador
#define PWM_FREQUENCY 1000 // Frequência do PWM em Hz

void init_pwm_timer0() {
    // Configurar pinos OC0A (PD6) e OC0B (PD5) como saída
    DDRD |= (1 << PD6) | (1 << PD5);

    // Configurar Timer 0 no modo Fast PWM
    TCCR0A = (1 << WGM00) | (1 << WGM01); // Modo Fast PWM
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1); // Clear OC0A/OC0B on compare match, set at BOTTOM
    TCCR0B = (1 << CS01); // Prescaler de 8

    // Inicializar registradores de comparação
    OCR0A = 127; // Ciclo de trabalho inicial (50% para OC0A)
    OCR0B = 64;  // Ciclo de trabalho inicial (25% para OC0B)
}

void set_pwm_duty_cycle(uint8_t channel, uint8_t duty_cycle) {
    // Ajustar ciclo de trabalho (duty_cycle: 0-100%)
    if (channel == 0) {
        OCR0A = (duty_cycle * 255) / 100; // Canal OC0A (PD6)
    } else if (channel == 1) {
        OCR0B = (duty_cycle * 255) / 100; // Canal OC0B (PD5)
    }
}

int main() {
    // Inicializar PWM
    init_pwm_timer0();

    // Loop principal
    while (1) {
        // Ciclo de trabalho ajustável (exemplo)
        set_pwm_duty_cycle(0, 75); // 75% no canal OC0A
        set_pwm_duty_cycle(1, 50); // 50% no canal OC0B
    }

    return 0;
}
