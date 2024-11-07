#include "main.h"

u_char Memory[255];
u_char Accumulator, Status, ProgramCounter, StackPointer, isrSig;
u_char fetch();

int main() {
    Accumulator = 0;
    Status = 0;
    ProgramCounter = 0;
    StackPointer = 0xfb;
    isrSig = 0;

    while (ProgramCounter < 255) {
	if (isrSig)
	    ISR();
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
	u_char tmp = Accumulator;
	Accumulator -= Memory[getAddr()];
	setStatus();
	Accumulator = tmp;
	break;
    case OPCODE_JMP:
	ProgramCounter = getAddr();
	break;
    case OPCODE_JZ:
	if (Status & 0x08)
	    ProgramCounter = getAddr();
	break;
    case OPCODE_JN:
	if (Status & 0x04)
	    ProgramCounter = getAddr();
	break;
    case OPCODE_JC:
	if (Status & 0x02)
	    ProgramCounter = getAddr();
	break;
    case OPCODE_JSR:
	pushStack(ProgramCounter);
	ProgramCounter = getAddr();
	break;
    case OPCODE_RET:
	ProgramCounter = popStack();
	break;
    case OPCODE_IN:
	break;
    case OPCODE_OUT:
	break;
    case OPCODE_RTI:
	Accumulator = popStack();
	Status = popStack();
	ProgramCounter = (popStack()<<4) | popStack();
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

void pushStack(u_char data) {
    Memory[StackPointer] = data;
    StackPointer++;
}

u_char popStack() {
    StackPointer--;
    return Memory[StackPointer];
}

void ISR() {
    pushStack(ProgramCounter & 0x0f);
    pushStack((ProgramCounter & 0xf0) >> 4);
    pushStack(Status);
    pushStack(Accumulator);
    ProgramCounter = 0xfc;
}
