# trying to create own pc
For fun... and because every programmer must to create its cpu emulator, compiler and basic operating system lol.

# CPU raw Instructions
#### IDL
Do nothing. Increment PC

Command length: 1
0b0**0000000**

## registers & memory
#### MOV
Main instruction of any cpu. Sets immediate data to register. Possibly set data from any RAM address. Can copy register data to other register.

L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
M - set mode
    - 00 = immediate
    - 01 = from memory address
    - 10 = from register
    - 11 = *reserved*
R - register address

Command length: 2-4
0b0**0000001**_LMMRRRR0 \[0x*MMMM*\] \[0xIIII\]

## ALU
#### INC
Increment data.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - what to increment
    - 0 = register
    - 1 = memory address
A - address

Command length: 2-4
0b0**000XXXX**_LXRRRR00 \[0xMMMM\]

#### DEC
Decrement data.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - what to increment
    - 0 = register
    - 1 = memory address

Command length: 2-4
0b0**000XXXX**_LXRRRR00 \[0xMMMM\]
    
#### ADD
Add two integers.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - where to add
    - 0 = register
    - 1 = memory
Y - what to add
    - 00 = immediate
    - 01 = from ram address
    - 10 = from register

Command length: 3-6
0b0**000XXXX**_LX*LYY*000 \[0bRRRR*RRRR*\] \[0xMMMM\]

#### SUB
Subtract two integers.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - where to subtract
    - 0 = register
    - 1 = memory
Y - what to subtract
    - 00 = immediate
    - 01 = from ram address
    - 10 = from register

Command length: 3-6
0b0**000XXXX**_LX*LYY*000 \[0bRRRR*RRRR*\] \[0xMMMM\]

#### XOR
XOR two numbers.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - where to xor
    - 0 = register
    - 1 = memory
Y - what to use for xor
    - 00 = immediate
    - 01 = from ram address
    - 10 = from register

Command length: 3-6
0b0**000XXXX**_LX*LYY*000 \[0bRRRR*RRRR*\] \[0xMMMM\]

#### OR
OR two numbers.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - where to or
    - 0 = register
    - 1 = memory
Y - what to use for or
    - 00 = immediate
    - 01 = from ram address
    - 10 = from register

Command length: 3-6
0b0**000XXXX**_LX*LYY*000 \[0bRRRR*RRRR*\] \[0xMMMM\]

#### AND
AND two numbers.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - where to xor
    - 0 = register
    - 1 = memory
Y - what to use for xor
    - 00 = immediate
    - 01 = from ram address
    - 10 = from register

Command length: 3-6
0b0**000XXXX**_LX*LYY*000 \[0bRRRR*RRRR*\]

#### NOT
NOT memory.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - what to NOT
    - 0 = register
    - 1 = memory

Command length: 2-4
0b0**000XXXX**_LXRRRR00 \[0xMMMM\]

#### SHR
SHift Right data. possible to shift circular to multiple positions.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - what to NOT
    - 0 = register
    - 1 = memory
C - circular mode
P - multi position

Command length: 2-5
0b0**000XXXX**_LXRRRRC0 \[0x*P*0\] \[0xMMMM\] 

#### SHL
SHift Left data. possible to shift circular to multiple positions.

R - register address
L - register type (length)
    - 0 = 1 byte register
    - 1 = 2 bytes register
X - what to NOT
    - 0 = register
    - 1 = memory
C - circular mode
P - multi position

Command length: 2-5
0b0**000XXXX**_LXRRRRC0 \[0x*P*0\] \[0xMMMM\] 

## Branch
#### CMP
#### JMP
