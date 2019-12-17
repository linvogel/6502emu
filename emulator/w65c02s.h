#ifndef HEADER_W65C02S
#define HEADER_W65C02S

#include <stdint.h>

#define RISING 1
#define HIGH 1
#define FALLING 0
#define LOW 0
#define READ 1
#define WRITE 0

#define P_CARRY 0
#define P_NEGATIVE 7
#define P_OVERFLOW 6
#define P_ZERO 1
#define P_USER 5
#define P_DECIMAL 3
#define P_IRQDISABLE 2
#define P_BRK 4

#define PIN_VBP (1ULL << 1)
#define PIN_RDY (1ULL << 2)
#define PIN_PHI1O (1ULL << 3)
#define PIN_IRQ_B (1ULL << 4)
#define PIN_ML_B (1ULL << 5)
#define PIN_NMI_B (1ULL << 6)
#define PIN_SYNC (1ULL << 7)
#define PIN_VDD (1ULL << 8)
#define PIN_A0 (1ULL << 9)
#define PIN_A1 (1ULL << 10)
#define PIN_A2 (1ULL << 11)
#define PIN_A3 (1ULL << 12)
#define PIN_A4 (1ULL << 13)
#define PIN_A5 (1ULL << 14)
#define PIN_A6 (1ULL << 15)
#define PIN_A7 (1ULL << 16)
#define PIN_A8 (1ULL << 17)
#define PIN_A9 (1ULL << 18)
#define PIN_A10 (1ULL << 19)
#define PIN_A11 (1ULL << 20)
#define PIN_VSS (1ULL << 21)
#define PIN_A12 (1ULL << 22)
#define PIN_A13 (1ULL << 23)
#define PIN_A14 (1ULL << 24)
#define PIN_A15 (1ULL << 25)
#define PIN_D7 (1ULL << 26)
#define PIN_D6 (1ULL << 27)
#define PIN_D5 (1ULL << 28)
#define PIN_D4 (1ULL << 29)
#define PIN_D3 (1ULL << 30)
#define PIN_D2 (1ULL << 31)
#define PIN_D1 (1ULL << 32)
#define PIN_D0 (1ULL << 33)
#define PIN_RW_B (1ULL << 34)
#define PIN_BE (1ULL << 36)
#define PIN_PHI2 (1ULL << 37)
#define PIN_SO_B (1ULL << 38)
#define PIN_PHI2O (1ULL << 39)
#define PIN_RES_B (1ULL << 40)

#define OP_BRK_STACK 								0x00
#define OP_ORA_ZEROPAGE_INDEXED_INDIRECT 			0x01
#define OP_TSB_ZEROPAGE 							0x04
#define OP_ORA_ZEROPAGE 							0x05
#define OP_ASL_ZEROPAGE 							0x06
#define OP_RMB0_ZEROPAGE 							0x07
#define OP_PHP_STACK 								0x08
#define OP_ORA_IMMEDIATE 							0x09
#define OP_ASL_ACCUMULATOR 							0x0A
#define OP_TSB_ABSOLUTE 							0x0C
#define OP_ORA_ABSOLUTE 							0x0D
#define OP_ASL_ABSOLUTE 							0x0E
#define OP_BBR0_RELATIVE 							0x0F

#define OP_BPL_RELATIVE 							0x10
#define OP_ORA_ZEROPAGE_INDIRECT_Y_INDEXED 			0x11
#define OP_ORA_ZEROPAGE_INDIRECT 					0x12
#define OP_TRB_ZEROPAGE								0x14
#define OP_ORA_ZEROPAGE_X_INDEXED					0x15
#define OP_ASL_ZEROPAGE_X_INDEXED					0x16
#define OP_RMB1_ZEROPAGE							0x17
#define OP_CLC_IMPLIED								0x18
#define OP_ORA_ABSOLUTE_Y_INDEXED					0x19
#define OP_INC_ACCUMULATOR							0x1A
#define OP_TRB_ABSOLUTE								0x1C
#define OP_ORA_ABSOLUTE_X_INDEXED					0x1D
#define OP_ASL_ABSOLUTE_X_INDEXED					0x1E
#define OP_BBR1_RELATIVE							0x1F

#define OP_JSR_ABSOLUTE								0x20
#define OP_AND_ZEROPAGE_INDEXED_INDIRECT			0x21
#define OP_BIT_ZEROPAGE								0x24
#define OP_AND_ZEROPAGE								0x25
#define OP_ROL_ZEROPAGE								0x26
#define OP_RMB2_ZEROPAGE							0x27
#define OP_PLP_STACK								0x28
#define OP_AND_IMMEDIATE							0x29
#define OP_ROL_ACCUMOLATOR							0x2A
#define OP_BIT_ABSOLUTE								0x2C
#define OP_AND_ABSOLUTE								0x2D
#define OP_ROL_ABSOLUTE								0x2E
#define OP_BBR2_RELATIVE							0x2F

#define OP_BMI_RELATIVE								0x30
#define OP_AND_ZEROPAGE_INDIRECT_Y_INDEXED			0x31
#define OP_AND_ZEROPAGE_INDIRECT					0x32
#define OP_BIT_ZEROPAGE_X_INDEXED					0x34
#define OP_AND_ZEROPAGE_X_INDEXED					0x35
#define OP_ROL_ZEROPAGE_X_INDEXED					0x36
#define OP_RMB3_ZEROPAGE							0x37
#define OP_SEC_IMPLIED								0x38
#define OP_AND_ABSOLUte_Y_INDEXED					0x39
#define OP_DEC_ACCUMULATOR							0x3A
#define OP_BIT_ABSOLUTE_X_INDEXED					0x3C
#define OP_AND_ABSOLUTE_X_INDEXED					0x3D
#define OP_ROL_ABSOLUTE_X_INDEXED					0x3E
#define OP_BBR3_RELATIVE							0x3F

#define OP_RTI_STACK								0x40
#define OP_EOR_ZEROPAGE_INDEXED_INDIRECT			0x41
#define OP_EOR_ZEROPAGE								0x45
#define OP_LSR_ZEROPAGE								0x46
#define OP_RMB4_ZEROPAGE							0x47
#define OP_PHA_STACK								0x48
#define OP_EOR_IMMEDIATE							0x49
#define OP_LSR_ACCUMULATOR							0x4A
#define OP_JMP_ABSOLUTE								0x4C
#define OP_EOR_ABSOLUTE								0x4D
#define OP_LSR_ABSOLUTE								0x4E
#define OP_BBR4_RELATIVE							0x4F

#define OP_BVC_RELATIVE								0x50
#define OP_EOR_ZEROPAGE_INDIRECT_Y_INDEXED			0x51
#define OP_EOR_ZEROPAGE_INDIRECT					0x52
#define OP_EOR_ZEROPAGE_X_INDEXED					0x55
#define OP_LSR_ZEROPAGE_X_INDEXED					0x56
#define OP_RMB5_ZEROPAGE							0x57
#define OP_CLI_IMPLIED								0x58
#define OP_EOR_ABSOLUTE_Y_INDEXED					0x59
#define OP_PHY_STACK								0x5A
#define OP_EOR_ABSOLUTE_X_INDEXED					0x5D
#define OP_LSR_ABSOLUTE_X_INDEXED					0x5E
#define OP_BBR5_RELATIVE							0x5F

#define OP_RTS_STACK								0x60
#define OP_ADC_ZEROPAGE_INDEXED_INDIRECT			0x61
#define OP_STZ_ZEROPAGE								0x64
#define OP_ADC_ZEROPAGE								0x65
#define OP_ROR_ZEROPAGE								0x66
#define OP_RMB6_ZEROPAGE							0x67
#define OP_PLA_STACK								0x68
#define OP_ADC_IMMEDIATE							0x69
#define OP_ROR_ACCUMULATOR							0x6A
#define OP_JMP_ABSOLUTE_INDIRECT					0x6C
#define OP_ADC_ABSOLUTE								0x6D
#define OP_ROR_ABSOLUTE								0x6E
#define OP_BBR6_RELATIVE							0x6F

#define OP_BVS_RELATIVE								0x70
#define OP_ADC_ZEROPAGE_INDIRECT_Y_INDEXED			0x71
#define OP_ADC_ZEROPAGE_INDIRECT					0x72
#define OP_STZ_ZEROPAGE_X_INDEXED					0x74
#define OP_ADC_ZEROPAGE_X_INDEXED					0x75
#define OP_ROR_ZEROPAGE_X_INDEXED					0x76
#define OP_RMB7_ZEROPAGE							0x77
#define OP_SEI_IMPLIED								0x78
#define OP_ADC_ABSOLUTE_Y_INDEXED					0x79
#define OP_PLY_STACK								0x7A
#define OP_JMP_ABSOLUTE_INDEXED_INDIRECT			0x7C
#define OP_ADC_ABSOLUTE_X_INDEXED					0x7D
#define OP_ROR_ABSOLUTE_X_INDEXED					0x7E
#define OP_BBR7_RELATIVE							0x7F

#define OP_BRA_RELATIVE								0x80
#define OP_STA_ZEROPAGE_INDEXED_INDIRECT			0x81
#define OP_STY_ZEROPAGE								0x84
#define OP_STA_ZEROPAGE								0x85
#define OP_STX_ZEROPAGE								0x86
#define OP_SMB0_ZEROPAGE							0x87
#define OP_DEY_IMPLIED								0x88
#define OP_BIT_IMMEDIATE							0x89
#define OP_TXA_IMPLIED								0x8A
#define OP_STY_ABSOLUTE								0x8C
#define OP_STA_ABSOLUTE								0x8D
#define OP_STX_ABSOLUTE								0x8E
#define OP_BBS0_RELATIVE							0x8F

#define OP_BCC_RELATIVE								0x90
#define OP_STA_ZEROPAGE_INDIRECT_Y_INDEXED			0x91
#define OP_STA_ZEROPAGE_INDIRECT					0x92
#define OP_STY_ZEROPAGE_X_INDEXED					0x94
#define OP_STA_ZEROPAGE_X_INDEXED					0x95
#define OP_STX_ZEROPAGE_Y_INDEXED					0x96
#define OP_SMB1_ZEROPAGE							0x97
#define OP_TYA_IMPLIED								0x98
#define OP_STA_ABSOLUTE_Y_INDEXED					0x99
#define OP_TXS_IMPLIED								0x9A
#define OP_STZ_ABSOLUTE								0x9C
#define OP_STA_ABSOLUTE_X_INDEXED					0x9D
#define OP_STZ_ABSOLUTE_X_INDEXED					0x9E
#define OP_BBS1_RELATIVE							0x9F

#define OP_LDY_IMMEDIATE							0xA0
#define OP_LDA_ZEROPAGE_INDEXED_INDIRECT			0xA1
#define OP_LDX_IMMEDIATE							0xA2
#define OP_LDY_ZEROPAGE								0xA4
#define OP_LDA_ZEROPAGE								0xA5
#define OP_LDX_ZEROPAGE								0xA6
#define OP_SMB2_ZEROPAGE							0xA7
#define OP_TAY_IMPLIED								0xA8
#define OP_LDA_IMMEDIATE							0xA9
#define OP_TAX_IMPLIED								0xAA
#define OP_LDY_ABSOLUTE								0xAC
#define OP_LDA_ABSOLUTE								0xAD
#define OP_LDX_ABSOLUTE								0xAE
#define OP_BBS2_RELATIVE							0xAF

#define OP_BCS_RELATIVE								0xB0
#define OP_LDA_ZEROPAGE_INDIRECT_Y_INDEXED			0xB1
#define OP_LDA_ZEROPAGE_INDIRECT					0xB2
#define OP_LDY_ZEROPAGE_X_INDEXED					0xB4
#define OP_LDA_ZEROPAGE_X_INDEXED					0xB5
#define OP_LDX_ZEROPAGE_Y_INDEXED					0xB6
#define OP_SMB3_ZEROPAGE							0xB7
#define OP_CLV_IMPLIED								0xB8
#define OP_LDA_ABSOLUTE_Y_INDEXED					0xB9
#define OP_TSX_IMPLIED								0xBA
#define OP_LDY_ABSOLute_X_INDEXED					0xBC
#define OP_LDA_ABSOLute_X_INDEXED					0xBD
#define OP_LDX_ABSOLute_Y_INDEXED					0xBE
#define OP_BBS3_RELATIVE							0xBF

#define OP_CPY_IMMEDIATE							0xC0
#define OP_CMP_ZEROPAGE_INDEXED_INDIRECT			0xC1
#define OP_CPY_ZEROPAGE								0xC4
#define OP_CMB_ZEROPAGE								0xC5
#define OP_DEC_ZEROPAGE								0xC6
#define OP_SMB4_ZEROPAGE							0xC7
#define OP_INY_IMPLIED								0xC8
#define OP_CMP_IMMEDIATE							0xC9
#define OP_DEX_IMPLIED								0xCA
#define OP_WAI_IMPLIED								0xCB
#define OP_CPY_ABSOLUTE								0xCC
#define OP_CMP_ABSOLUTE								0xCD
#define OP_DEC_ABSOLUTE								0xCE
#define OP_BBS4_RELATIVE							0xCF

#define OP_BNE_RELATIVE								0xD0
#define OP_CMP_ZEROPAGE_INDIRECT_Y_INDEXED			0xD1
#define OP_CMP_ZEROPAGE_INDIRECT					0xD2
#define OP_CMP_ZEROPAGE_X_INDEXED					0xD5
#define OP_DEC_ZEROPAGE_X_INDEXED					0xD6
#define OP_SMB5_ZEROPAGE							0xD7
#define OP_CLD_IMPLIED								0xD8
#define OP_CMP_ABSOLUTE_Y_INDEXED					0xD9
#define OP_PHX_STACK								0xDA
#define OP_STP_IMPLIED								0xDB
#define OP_CMP_ABSOLUTE_X_INDEXED					0xDD
#define OP_DEC_ABSOLUTE_X_INDEXED					0xDE
#define OP_BBS5_RELATIVE							0xDF

#define OP_CPX_IMMEDIATE							0xE0
#define OP_SBC_ZEROPAGE_INDEXED_INDIRECT			0xE1
#define OP_CPX_ZEROPAGE								0xE4
#define OP_SBC_ZEROPAGE								0xE5
#define OP_INC_ZEROPAGE								0xE6
#define OP_SMB6_ZEROPAGE							0xE7
#define OP_INX_IMPLIED								0xE8
#define OP_SBC_IMMEDIATE							0xE9
#define OP_NOP_IMPLIED								0xEA
#define OP_CPX_ABSOLUTE								0xEC
#define OP_SBC_ABSOLUTE								0xED
#define OP_INC_ABSOLUTE								0xEE
#define OP_BBS6_RELATIVE							0xEF

#define OP_BEQ_RELATIVE								0xF0
#define OP_SBC_ZEROPAGE_INDIRECT_Y_INDEXED			0xF1
#define OP_SBC_ZEROPAGE_INDIRECT					0xF2
#define OP_SBC_ZEROPAGE_X_INDEXED					0xF5
#define OP_INC_ZEROPAGE_X_INDEXED					0xF6
#define OP_SMB7_ZEROPAGE							0xF7
#define OP_SED_IMPLIED								0xF8
#define OP_SBC_ABSOLUTE_Y_INDEXED					0xF9
#define OP_PLX_STACK								0xFA
#define OP_SBX_ABSOLUTE_X_INDEXED					0xFD
#define OP_INC_ABSOLUTE_X_INDEXED					0xFE
#define OP_BBS7_RELATIVE							0xFF

struct W65C02S {
	uint8_t a;
	uint8_t x;
	uint8_t y;
	uint8_t stateRegister;
	uint8_t instructionRegister;
	uint8_t timingControl;
	uint16_t pc;
	uint16_t sp;
	
	uint8_t dataBus;
	uint16_t addressBus;
	
	uint8_t internalState;
	uint8_t handlingInterrupt;
	uint8_t handlingNMI;
	uint8_t resetting;
	
	uint64_t pins;
	
	int nDevices;
	void** devices;
};


uint16_t readAddress(struct W65C02S* isntance);

uint8_t readData(struct W65C02S* isntance);
void writeData(struct W65C02S* isntance, uint8_t data);

void busEnable(struct W65C02S* isntance, uint8_t state);
void interruptRequest(struct W65C02S* isntance, uint8_t state);
uint8_t memoryLock(struct W65C02S* isntance);

void nonMaskableInterrupt(struct W65C02S* isntance, uint8_t state);
void clock(struct W65C02S* isntance);

uint8_t phi1(struct W65C02S* isntance);
uint8_t phi2(struct W65C02S* isntance);

uint8_t readWrite(struct W65C02S* isntance);
uint8_t ready(struct W65C02S* isntance, uint8_t state);

void setOverflow(struct W65C02S* isntance, uint8_t state);
uint8_t sync(struct W65C02S* isntance);
void reset(struct W65C02S* isntance, uint8_t state);

uint8_t vectorPull(struct W65C02S* isntance);

int attachDevice(struct W65C02S* instance, void* clockFunction);


#endif