; Programa para o ATmega328
; Faz o LED conectado ao pino 3 da porta D piscar

.org 0x0000              ; Endereço inicial do programa
    rjmp RESET           ; Salta para o início do programa

RESET:
    ; Configuração inicial
    ldi r16, 0x08        ; Configura o pino 3 da porta D como saída (0x08 = 00001000)
    out DDRD, r16        ; Define o pino PD3 como saída na porta D

    ; Loop principal
MAIN_LOOP:
    sbi PORTD, PD3       ; Acende o LED no pino PD3 (seta o bit)
    rcall DELAY          ; Chama a sub-rotina de delay
    cbi PORTD, PD3       ; Apaga o LED no pino PD3 (limpa o bit)
    rcall DELAY          ; Chama a sub-rotina de delay
    rjmp MAIN_LOOP       ; Retorna ao loop principal

; Sub-rotina de delay
DELAY:
    ldi r18, 0xFF        ; Carrega o valor 255 no registrador r18 (contagem externa)
    ldi r19, 0xFF        ; Carrega o valor 255 no registrador r19 (contagem interna)

DELAY_LOOP:
    dec r19              ; Decrementa o valor de r19
    brne DELAY_LOOP      ; Se r19 não for zero, repete o loop
    dec r18              ; Decrementa o valor de r18
    brne DELAY_LOOP      ; Se r18 não for zero, repete o loop
    ret                  ; Retorna da sub-rotina de delay


