; Programa para o ATmega328
; Multiplica dois registradores e exibe o resultado na porta D

.org 0x0000              ; Endereço inicial do programa
    rjmp RESET           ; Salta para o início do programa

RESET:
    ldi r16, 0xFF        ; Configura todos os bits da porta D como saída
    out DDRD, r16        ; Define DDRD (todos os bits da porta D como saída)

    ldi r17, 5           ; Carrega o valor 5 no registrador R17
    ldi r18, 5           ; Carrega o valor 3 no registrador R18

    mul r17, r18         ; Multiplica R17 * R18, resultado armazenado em R1:R0
    mov r16, r0          ; Move o byte menos significativo do resultado para R16
    out PORTD, r16       ; Exibe o byte menos significativo na porta D

LOOP:
    rjmp LOOP            ; Loop infinito para manter o programa ativo

