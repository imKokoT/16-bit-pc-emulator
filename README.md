# trying to create own pc
For fun... and because every programmer must to create its cpu emulator, compiler and basic operating system lol.

# CPU raw Instructions
#### IDL
Do nothing. Increment PC

0b0**0000000** -- 0x00

## registers & memory
#### MOV
Main instruction of any cpu. Sets immediate data to register. Possibly set data from any RAM address. Can copy register data to other register.

L - register type
    - 0 = 1 byte register
    - 1 = 2 bytes register
M - set mode
    - 00 = immediate
    - 01 = from ram address
    - 10 = from register
    - 11 = *reserved*
R - register address

0b0**0000001**_LMMRRRRR -- 0x01_XX

## ALU
    INC
    DEC
    ADD
    NOT
    XOR
    OR
    AND
    SHR
    SHL
## Branch
    COMP
    JMP
