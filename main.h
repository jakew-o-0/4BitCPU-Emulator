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

void execute(u_char opcode);
void setStatus_clearC();
void setStatus();
u_char getAddr();
u_char popStack();
void pushStack(u_char data);
void ISR();
