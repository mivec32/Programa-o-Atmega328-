; Programa para o ATmega328
; Lê os estados da porta D e os espelha na porta B

.org 0x0000              ; Endereço inicial do programa
    rjmp RESET           ; Salta para o início do programa

RESET:
    ldi r16, 0x00        ; Configura todos os bits da porta D como entrada
    out DDRD, r16        ; Define DDRD (todos os bits da porta D como entrada)
    ldi r16, 0xFF        ; Configura todos os bits da porta B como saída
    out DDRB, r16        ; Define DDRB (todos os bits da porta B como saída)

MAIN_LOOP:
    in r16, PIND         ; Lê os estados dos pinos da porta D
    out PORTB, r16       ; Espelha os estados da porta D na porta B
    rjmp MAIN_LOOP       ; Repete o loop principal

