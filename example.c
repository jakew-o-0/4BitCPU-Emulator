// CSA4bitCPU.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

typedef unsigned char BYTE;		/* Define 8-bit unsigned number type */
typedef unsigned char NIBBLE;	/* Define 4-bit unsigned number type */


/* Opcodes */

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


/* Flags */

#define Z_FLAG 0x08
#define N_FLAG 0x04
#define C_FLAG 0x02


/* Registers */

NIBBLE Accumulator;		/* 4-bit Registers */
NIBBLE Status;
BYTE   ProgramCounter;	/* 8-bit Registers */
BYTE   StackPointer;


/* Memory */

NIBBLE Memory[256] = 
{ 
	OPCODE_NOP, 
	OPCODE_LDI, 0xA,
	OPCODE_LDD, 0x0, 0x3,
	OPCODE_ST,  0x2, 0x0,
	OPCODE_LDI, 0xB,
	OPCODE_LDD, 0x2, 0x0,
	OPCODE_LDI, 0x0
};


/* Ports */

NIBBLE InputPort[16];
NIBBLE OutputPort[16];


char fetch() {
	NIBBLE instruction_nibble;

	instruction_nibble = Memory[ProgramCounter];
	ProgramCounter++;

	return instruction_nibble;
}


void clear_carry_flag() {
	Status = Status & ~C_FLAG;
}


void set_negative_flag() {
	if ((Accumulator & 0x08) == 0x08)
	{
		Status = Status | N_FLAG;
	}
	else
	{
		Status = Status & ~N_FLAG;
	}
}


void set_zero_flag() {
	if (Accumulator == 0)
	{
		Status = Status | Z_FLAG;
	}
	else
	{
		Status = Status & ~Z_FLAG;
	}
}



void execute(NIBBLE opcode) {
	NIBBLE high_nibble;
	NIBBLE low_nibble;
	BYTE   address;

	/* Decode using a switch statement */

	switch (opcode)
	{
	case OPCODE_NOP:  /* No Operation */
		break;

	case OPCODE_LDI:  /* Load Immediate */
		Accumulator = fetch();
		clear_carry_flag();
		set_negative_flag();
		set_zero_flag();
		break;

	case OPCODE_LDD:  /* Load Direct */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		Accumulator = Memory[address];
		clear_carry_flag();
		set_negative_flag();
		set_zero_flag();
		break;

	case OPCODE_ST:   /* Store */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		Memory[address] = Accumulator;
		break;

	case OPCODE_ADD:
		break;

	case OPCODE_SUB:
		break;

	case OPCODE_CMP:
		break;

	case OPCODE_JMP:
		break;

	case OPCODE_JZ:
		break;

	case OPCODE_JN:
		break;

	case OPCODE_JC:
		break;

	case OPCODE_JSR:
		break;

	case OPCODE_RET:
		break;

	case OPCODE_IN:
		break;

	case OPCODE_OUT:
		break;

	case OPCODE_RTI:
		break;

	default:
		break;
	}
}



int main()
{
	int sanity;
	NIBBLE opcode;

	printf("CSA 4-bit CPU Emulator\n");
	printf("\n");

	/* Initialise Registers */

	Accumulator = 0;
	Status = 0;
	ProgramCounter = 0;
	StackPointer = 0xFB;

	/* Main Fetch/Decode/Execute Loop */

	sanity = 0;

	printf("        A Z N C PC SP\n");

	while (sanity < 100)
	{
		printf("%02X: ", ProgramCounter);	/* Memory location */

		opcode = fetch();

		switch (opcode)
		{
		case OPCODE_NOP: printf("NOP "); break;
		case OPCODE_LDI: printf("LDI "); break;
		case OPCODE_LDD: printf("LDD "); break;
		case OPCODE_ST:  printf("ST  "); break;
		case OPCODE_ADD: printf("ADD "); break;
		case OPCODE_SUB: printf("SUB "); break;
		case OPCODE_CMP: printf("CMP "); break;
		case OPCODE_JMP: printf("JMP "); break;
		case OPCODE_JZ:  printf("JZ  "); break;
		case OPCODE_JN:  printf("JN  "); break;
		case OPCODE_JC:  printf("JC  "); break;
		case OPCODE_JSR: printf("JSR "); break;
		case OPCODE_RET: printf("RET "); break;
		case OPCODE_IN:  printf("IN  "); break;
		case OPCODE_OUT: printf("OUT "); break;
		case OPCODE_RTI: printf("RTI "); break;
		default: break;
		}

		execute(opcode);

		printf("%1X ", Accumulator);		/* Accumulator */
		if ((Status & Z_FLAG) == Z_FLAG) printf("1 "); else printf("0 ");	/* zero flag */
		if ((Status & N_FLAG) == N_FLAG) printf("1 "); else printf("0 ");	/* negative flag */
		if ((Status & C_FLAG) == C_FLAG) printf("1 "); else printf("0 ");	/* carry flag */
		printf("%02X ", ProgramCounter);	/* Program Counter */
		printf("%02X ", StackPointer);		/* Stack Pointer */
		printf("\n");


		sanity++;  // We stop the emulator after 100 cycles, in reality the CPU would run forever
	}
}
