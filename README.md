# trying to create own pc
For fun... and because every programmer must to create its cpu emulator, compiler and basic operating system lol.

# 16x-CPU V1 

## registers
### user's
R0-R15 - single byte registers
WR0-WR15 - double byte registers
### special
PC - Program Counter
SP - Stack Pointer
#### flags
C - Carry (unsigned overflow)
O - Overflow (signed overflow)
E - Equal
B - A > B
Z - Zero
N - Negative
BW - Borrow

## raw Instructions
#### IDL
Do nothing. Increment PC

Command length: 1
0b0**0000000**

#### STP
Stop cpu ticking. Power-off.

Command length: 1
0b0**0001100**

## registers & memory
#### MOV
Main instruction of any cpu. Sets immediate data to register. Possibly set data from any RAM address. Can copy register data to other register.

L - register length
    - 0 = 1 byte register
    - 1 = 2 bytes register 
T - register type
    - 0 = R or WR
    - 1 = special like PC; map:
        - 0000 = PC
        - 0001 = SP
M - set mode
    - 00 = immediate
    - 01 = from memory address
    - 10 = from register; to command added 1 byte *0bRRRRTL00*
    - 11 = move to address
R - target register address

Command length: 3-4
0b0**0000001**_LTMMRRRR \[0x*RR*\] \[0xIIII\] \[0xAAAA\]

## ALU
#### INC
Increment data.
**FLAGS: O,Z,N**

R - register address
T - register type (length)
    - 00 = R register
    - 01 = WR register
    - 10 = special
X - what to increment
    - 0 = register
    - 1 = memory address
A - address

Command length: 2-4
X=0 | 0b0**0000010**_TT0XRRRR
X=1 | 0b0**0000010**_L00X0000 0xAAAA

#### DEC
Decrement data.
**FLAGS: O,Z,N**

R - register address
T - register type (length)
    - 00 = R register
    - 01 = WR register
    - 10 = special
X - what to increment
    - 0 = register
    - 1 = memory address
A - address

Command length: 2-4
X=0 | 0b0**0000011**_TT0XRRRR
X=1 | 0b0**0000011**_L00X0000 0xAAAA
    
#### ADD
Add two integers. Result stores to X.
**FLAGS: C,O,Z,N**

R - register address
T - register type (length)
    - 00 = R register
    - 01 = WR register
    - 10 = special
X - where to add
    - 0 = register
    - 1 = memory address
Y - what to add
    - 00 = immediate
    - 01 = from ram address
    - 10 = from register

Command length: 3-6
X=0 Y=00 | 0b0**0000100**_00LYYTTX 0b0000RRRR 0xII \[0xII\]
X=0 Y=01 | 0b0**0000100**_000YYTTX 0b0000RRRR *0xAAAA*
X=0 Y=10 | 0b0**0000100**_0*TT*YYTTX 0b*RRRR*RRRR
X=1 Y=00 | 0b0**0000100**_00LYY0LX 0xAAAA 0xII \[0xII\]
X=1 Y=01 | 0b0**0000100**_000YY0LX 0xAAAA *0xAAAA*
X=1 Y=10 | 0b0**0000100**_0*TT*YY0LX 0xAAAA 0b*RRRR*0000

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
0b0**0000101**_LX*LYY*000 \[0bRRRR*RRRR*\] \[0xMMMM\]

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
0b0**0000110**_LX*LYY*000 \[0bRRRR*RRRR*\] \[0xMMMM\]

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
0b0**0000111**_LX*LYY*000 \[0bRRRR*RRRR*\] \[0xMMMM\]

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
0b0**0001000**_LX*LYY*000 \[0bRRRR*RRRR*\]

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
0b0**0001001**_LXRRRR00 \[0xMMMM\]

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
0b0**0001010**_LXRRRRC0 \[0x*P*0\] \[0xMMMM\] 

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
0b0**0001011**_LXRRRRC0 \[0x*P*0\] \[0xMMMM\] 

## Branch
#### CMP
#### JMP

## Debugging
#### TRAP 
Break point.
