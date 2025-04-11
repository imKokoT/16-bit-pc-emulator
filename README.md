# trying to create own pc
For fun... and because every programmer must to create its cpu emulator, compiler and basic operating system lol.

# CPU raw Instructions
#### IDL
Do nothing. Increment PC

0b**0000000**0 -- 0x00

## registers & memory
#### STR
Set data to register. Possibly set static data or from any RAM address.

L - data length
    - 0 = 1 byte
    - 1 = 2 bytes
M - set mode
    - 00 = static
    - 01 = from ram
    - 10 = *reserved*
    - 11 = *reserved*
R - register address

0b**0000001**L_MMRRRRR0

#### STM
Set data from register to RAM

#### MOV
Copies register data to other register

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
