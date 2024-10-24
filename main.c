#define u_char unsigned char

#define OPCODE_NOP	0x00
#define OPCODE_LDI	0x01
#define OPCODE_LDD	0x02
#define OPCODE_ST	0x03
#define OPCODE_ADD	0x04
#define OPCODE_SUB	0x05
#define OPCODE_CMP	0x06
#define OPCODE_JMP	0x07
#define OPCODE_JZ	0x08
#define OPCODE_JN	0x09
#define OPCODE_JC	0x0A
#define OPCODE_JSR	0x0B
#define OPCODE_RET	0x0C
#define OPCODE_IN	0x0D
#define OPCODE_OUT	0x0E
#define OPCODE_RTI	0x0F

u_char Memory[255];
u_char Accumulator, Status, ProgramCounter, StackPointer;
u_char fetch();

void execute(u_char opcode);
void setStatus_clearC();
void setStatus();
u_char getAddr();

int main() {
    Accumulator = 0;
    Status = 0;
    ProgramCounter = 0;
    StackPointer = 0xfb;

    while (ProgramCounter < 255) {
	execute(fetch());
    }
}

u_char fetch() {
    u_char opcode = Memory[ProgramCounter];
    ProgramCounter++;
    return opcode;
}

void execute(u_char opcode) {
    switch (opcode) {
    case OPCODE_NOP:
	break;
    case OPCODE_LDI:
	Accumulator = fetch();
	setStatus_clearC();
	break;
    case OPCODE_LDD:
	Accumulator = Memory[getAddr()];
	setStatus_clearC();
	break;
    case OPCODE_ST:
	Memory[getAddr()] = Accumulator;
    case OPCODE_ADD:
	Accumulator += Memory[getAddr()];
	setStatus();
	break;
    case OPCODE_SUB:
	Accumulator -= Memory[getAddr()];
	setStatus();
	break;
    case OPCODE_CMP:
	Accumulator = Accumulator == Memory[getAddr()]? 1:0;
	setStatus();
	break;
    }
}

void setStatus_clearC() {
    Status = 0;
    if (Accumulator == 0)
	Status |= 1<<4;
    Status |= (Accumulator & 0x08)>>1;
}

void setStatus() {
    setStatus_clearC();
    if ((Accumulator & 0xf0) > 0)
	Status |= 0x02;
}

u_char getAddr() {
    return (fetch()<<4) | fetch();
}
