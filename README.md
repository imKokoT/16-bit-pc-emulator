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
#### INC
Increment data.

L - register type
    - 0 = 1 byte register
    - 1 = 2 bytes register
M - what to increment
    - 0 = register
    - 1 = RAM address
A - address

0b0**000XXXX**_LMRRRRR0 -- 0xXX or 0xXX_AA

#### DEC
Decrement data.

L - register type
    - 0 = 1 byte register
    - 1 = 2 bytes register
M - what to increment
    - 0 = register
    - 1 = RAM address
A - address

0b0**000XXXX**_LMRRRRR0 -- 0xXX or 0xXX_AA

    ADD
    SUB
    NOT
    XOR
    OR
    AND
    SHR
    SHL
## Branch
    COMP
    JMP
