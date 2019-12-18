#include "w65c02s.h"

#include <stdio.h>
#include <malloc.h>

#define STATE_FETCH_OPCODE 0
#define STATE_EXECUTE 1





void fetchOpcode(struct W65C02S* instance);
void execute(struct W65C02S* instance);

void brk_stack(struct W65C02S* instance);
void ora_zeropage_indexed_indirect(struct W65C02S* instance);
void tsb_zeropage(struct W65C02S* instance);
void ora_zeropage(struct W65C02S* instance);
void asl_zeropage(struct W65C02S* instance);
void rmb0_zeropage(struct W65C02S* instance);
void php_stack(struct W65C02S* instance);
void ora_immediate(struct W65C02S* instance);
void asl_accumulator(struct W65C02S* instance);
void tsb_absolute(struct W65C02S* instance);
void ora_absolute(struct W65C02S* instance);
void asl_absolute(struct W65C02S* instance);
void bbr0_relative(struct W65C02S* instance);
void bpl_relative(struct W65C02S* instance);
void ora_zeropage_indirect_y_indexed(struct W65C02S* instance);
void ora_zeropage_indirect(struct W65C02S* instance);
void trb_zeropage(struct W65C02S* instance);
void ora_zeropage_x_indexed(struct W65C02S* instance);
void asl_zeropage_x_indexed(struct W65C02S* instance);
void rmb1_zeropage(struct W65C02S* instance);
void clc_implied(struct W65C02S* instance);
void ora_absolute_y_indexed(struct W65C02S* instance);
void inc_accumulator(struct W65C02S* instance);
void trb_absolute(struct W65C02S* instance);
void ora_absolute_x_indexed(struct W65C02S* instance);
void asl_absolute_x_indexed(struct W65C02S* instance);
void bbr1_relative(struct W65C02S* instance);
void jsr_absolute(struct W65C02S* instance);
void and_zeropage_indexed_indirect(struct W65C02S* instance);
void bit_zeropage(struct W65C02S* instance);
void and_zeropage(struct W65C02S* instance);
void rol_zeropage(struct W65C02S* instance);
void rmb2_zeropage(struct W65C02S* instance);
void plp_stack(struct W65C02S* instance);
void and_immediate(struct W65C02S* instance);
void rol_accumolator(struct W65C02S* instance);
void bit_absolute(struct W65C02S* instance);
void and_absolute(struct W65C02S* instance);
void rol_absolute(struct W65C02S* instance);
void bbr2_relative(struct W65C02S* instance);
void bmi_relative(struct W65C02S* instance);
void and_zeropage_indirect_y_indexed(struct W65C02S* instance);
void and_zeropage_indirect(struct W65C02S* instance);
void bit_zeropage_x_indexed(struct W65C02S* instance);
void and_zeropage_x_indexed(struct W65C02S* instance);
void rol_zeropage_x_indexed(struct W65C02S* instance);
void rmb3_zeropage(struct W65C02S* instance);
void sec_implied(struct W65C02S* instance);
void and_absolute_y_indexed(struct W65C02S* instance);
void dec_accumulator(struct W65C02S* instance);
void bit_absolute_x_indexed(struct W65C02S* instance);
void and_absolute_x_indexed(struct W65C02S* instance);
void rol_absolute_x_indexed(struct W65C02S* instance);
void bbr3_relative(struct W65C02S* instance);
void rti_stack(struct W65C02S* instance);
void eor_zeropage_indexed_indirect(struct W65C02S* instance);
void eor_zeropage(struct W65C02S* instance);
void lsr_zeropage(struct W65C02S* instance);
void rmb4_zeropage(struct W65C02S* instance);
void pha_stack(struct W65C02S* instance);
void eor_immediate(struct W65C02S* instance);
void lsr_accumulator(struct W65C02S* instance);
void jmp_absolute(struct W65C02S* instance);
void eor_absolute(struct W65C02S* instance);
void lsr_absolute(struct W65C02S* instance);
void bbr4_relative(struct W65C02S* instance);
void bvc_relative(struct W65C02S* instance);
void eor_zeropage_indirect_y_indexed(struct W65C02S* instance);
void eor_zeropage_indirect(struct W65C02S* instance);
void eor_zeropage_x_indexed(struct W65C02S* instance);
void lsr_zeropage_x_indexed(struct W65C02S* instance);
void rmb5_zeropage(struct W65C02S* instance);
void cli_implied(struct W65C02S* instance);
void eor_absolute_y_indexed(struct W65C02S* instance);
void phy_stack(struct W65C02S* instance);
void eor_absolute_x_indexed(struct W65C02S* instance);
void lsr_absolute_x_indexed(struct W65C02S* instance);
void bbr5_relative(struct W65C02S* instance);
void rts_stack(struct W65C02S* instance);
void adc_zeropage_indexed_indirect(struct W65C02S* instance);
void stz_zeropage(struct W65C02S* instance);
void adc_zeropage(struct W65C02S* instance);
void ror_zeropage(struct W65C02S* instance);
void rmb6_zeropage(struct W65C02S* instance);
void pla_stack(struct W65C02S* instance);
void adc_immediate(struct W65C02S* instance);
void ror_accumulatot(struct W65C02S* instance);
void jmp_absolute_indirect(struct W65C02S* instance);
void adc_absolute(struct W65C02S* instance);
void ror_absolute(struct W65C02S* instance);
void bbr6_relative(struct W65C02S* instance);
void bvs_relative(struct W65C02S* instance);
void adc_zeropage_indirect_y_indexed(struct W65C02S* instance);
void adc_zeropage_indirect(struct W65C02S* instance);
void stz_zeropage_x_indexed(struct W65C02S* instance);
void adc_zeropage_x_indexed(struct W65C02S* instance);
void ror_zeropage_x_indexed(struct W65C02S* instance);
void rmb7_zeropage(struct W65C02S* instance);
void sei_implied(struct W65C02S* instance);
void adc_absolute_y_indexed(struct W65C02S* instance);
void ply_stack(struct W65C02S* instance);
void jmp_absolute_indexed_indirect(struct W65C02S* instance);
void adc_absolute_x_indexed(struct W65C02S* instance);
void ror_absolute_x_indexed(struct W65C02S* instance);
void bbr7_relative(struct W65C02S* instance);
void bra_relative(struct W65C02S* instance);
void sta_zeropage_indexed_indirect(struct W65C02S* instance);
void sty_zeropage(struct W65C02S* instance);
void sta_zeropage(struct W65C02S* instance);
void stx_zeropage(struct W65C02S* instance);
void smb0_zeropage(struct W65C02S* instance);
void dey_implied(struct W65C02S* instance);
void bit_immediate(struct W65C02S* instance);
void txa_implied(struct W65C02S* instance);
void sty_absolute(struct W65C02S* instance);
void sta_absolute(struct W65C02S* instance);
void stx_absolute(struct W65C02S* instance);
void bbs0_relative(struct W65C02S* instance);
void bcc_relative(struct W65C02S* instance);
void sta_zeropage_indirect_y_indexed(struct W65C02S* instance);
void sta_zeropage_indirect(struct W65C02S* instance);
void sty_zeropage_x_indexed(struct W65C02S* instance);
void sta_zeropage_x_indexed(struct W65C02S* instance);
void stx_zeropage_y_indexed(struct W65C02S* instance);
void smb1_zeropage(struct W65C02S* instance);
void tya_implied(struct W65C02S* instance);
void sta_absolute_y_indexed(struct W65C02S* instance);
void txs_implied(struct W65C02S* instance);
void stz_absolute(struct W65C02S* instance);
void sta_absolute_x_indexed(struct W65C02S* instance);
void stz_absolute_x_indexed(struct W65C02S* instance);
void bbs1_relative(struct W65C02S* instance);
void ldy_immediate(struct W65C02S* instance);
void lda_zeropage_indexed_indirect(struct W65C02S* instance);
void ldx_immediate(struct W65C02S* instance);
void ldy_zeropage(struct W65C02S* instance);
void lda_zeropage(struct W65C02S* instance);
void ldx_zeropage(struct W65C02S* instance);
void smb2_zeropage(struct W65C02S* instance);
void tay_implied(struct W65C02S* instance);
void lda_immediate(struct W65C02S* instance);
void tax_implied(struct W65C02S* instance);
void ldy_absolute(struct W65C02S* instance);
void lda_absolute(struct W65C02S* instance);
void ldx_absolute(struct W65C02S* instance);
void bbs2_relative(struct W65C02S* instance);
void bcs_relative(struct W65C02S* instance);
void lda_zeropage_indirect_y_indexed(struct W65C02S* instance);
void lda_zeropage_indirect(struct W65C02S* instance);
void ldy_zeropage_x_indexed(struct W65C02S* instance);
void lda_zeropage_x_indexed(struct W65C02S* instance);
void ldx_zeropage_y_indexed(struct W65C02S* instance);
void smb3_zeropage(struct W65C02S* instance);
void clv_implied(struct W65C02S* instance);
void lda_absolute_y_indexed(struct W65C02S* instance);
void tsx_implied(struct W65C02S* instance);
void ldy_absolute_x_indexed(struct W65C02S* instance);
void lda_absolute_x_indexed(struct W65C02S* instance);
void ldx_absolute_y_indexed(struct W65C02S* instance);
void bbs3_relative(struct W65C02S* instance);
void cpy_immediate(struct W65C02S* instance);
void cmp_zeropage_indexed_indirect(struct W65C02S* instance);
void cpy_zeropage(struct W65C02S* instance);
void cmb_zeropage(struct W65C02S* instance);
void dec_zeropage(struct W65C02S* instance);
void smb4_zeropage(struct W65C02S* instance);
void iny_implied(struct W65C02S* instance);
void cmp_immediate(struct W65C02S* instance);
void dex_implied(struct W65C02S* instance);
void wai_implied(struct W65C02S* instance);
void cpy_absolute(struct W65C02S* instance);
void cmp_absolute(struct W65C02S* instance);
void dec_absolute(struct W65C02S* instance);
void bbs4_relative(struct W65C02S* instance);
void bne_relative(struct W65C02S* instance);
void cmp_zeropage_indirect_y_indexed(struct W65C02S* instance);
void cmp_zeropage_indirect(struct W65C02S* instance);
void cmp_zeropage_x_indexed(struct W65C02S* instance);
void dec_zeropage_x_indexed(struct W65C02S* instance);
void smb5_zeropage(struct W65C02S* instance);
void cld_implied(struct W65C02S* instance);
void cmp_absolute_y_indexed(struct W65C02S* instance);
void phx_stack(struct W65C02S* instance);
void stp_implied(struct W65C02S* instance);
void cmp_absolute_x_indexed(struct W65C02S* instance);
void dec_absolute_x_indexed(struct W65C02S* instance);
void bbs5_relative(struct W65C02S* instance);
void cpx_immediate(struct W65C02S* instance);
void sbc_zeropage_indexed_indirect(struct W65C02S* instance);
void cpx_zeropage(struct W65C02S* instance);
void sbc_zeropage(struct W65C02S* instance);
void inc_zeropage(struct W65C02S* instance);
void smb6_zeropage(struct W65C02S* instance);
void inx_implied(struct W65C02S* instance);
void sbc_immediate(struct W65C02S* instance);
void nop_implied(struct W65C02S* instance);
void cpx_absolute(struct W65C02S* instance);
void sbc_absolute(struct W65C02S* instance);
void inc_absolute(struct W65C02S* instance);
void bbs6_relative(struct W65C02S* instance);
void beq_relative(struct W65C02S* instance);
void sbc_zeropage_indirect_y_indexed(struct W65C02S* instance);
void sbc_zeropage_indirect(struct W65C02S* instance);
void sbc_zeropage_x_indexed(struct W65C02S* instance);
void inc_zeropage_x_indexed(struct W65C02S* instance);
void smb7_zeropage(struct W65C02S* instance);
void sed_implied(struct W65C02S* instance);
void sbc_absolute_y_indexed(struct W65C02S* instance);
void plx_stack(struct W65C02S* instance);
void sbx_absolute_x_indexed(struct W65C02S* instance);
void inc_absolute_x_indexed(struct W65C02S* instance);
void bbs7_relative(struct W65C02S* instance);


void clock(struct W65C02S* instance)
{
	//printf("Internal state: %d: Timing Control: %d: ", instance->internalState, instance->timingControl);
	if (instance->internalState == STATE_FETCH_OPCODE) {
		fetchOpcode(instance);
		return;
	}
	if (instance->internalState == STATE_EXECUTE) {
		execute(instance);
		return;
	}
}

uint16_t readAddress(struct W65C02S* instance)
{
	return instance->addressBus;
}

uint8_t readData(struct W65C02S* instance)
{
	return instance->dataBus;
}

void writeData(struct W65C02S* instance, uint8_t data)
{
	instance->dataBus = data;
}

void busEnable(struct W65C02S* instance, uint8_t state)
{
	instance->pins = state ? instance->pins | PIN_BE : instance->pins & ~PIN_BE;
}

void interruptRequest(struct W65C02S* instance, uint8_t state)
{
	if (!state) {
		instance->pins &= ~PIN_IRQ_B;
		instance->handlingInterrupt = 1;
	} else {
		instance->pins |= PIN_IRQ_B;
	}
}

uint8_t memoryLock(struct W65C02S* instance)
{
	return (instance->pins & PIN_ML_B) ? 1 : 0;
}

void nonMaskableInterrupt(struct W65C02S* instance, uint8_t state)
{
	if (state) {
		instance->pins &= ~PIN_NMI_B;
		instance->handlingNMI = 1;
	} else {
		instance->pins |= PIN_NMI_B;
	}
}

uint8_t phi1(struct W65C02S* instance)
{
	return (instance->pins & PIN_PHI1O) ? 1 : 0;
}

uint8_t phi2(struct W65C02S* instance)
{
	return (instance->pins & PIN_PHI2O) ? 1 : 0;
}

uint8_t readWrite(struct W65C02S* instance)
{
	return (instance->pins & PIN_RW_B) ? 1 : 0;
}

uint8_t ready(struct W65C02S* instance, uint8_t state)
{
	//TODO: Implement
}

void setOverflow(struct W65C02S* instance, uint8_t state)
{
	if (state) {
		instance->pins &= ~PIN_SO_B;
		instance->stateRegister |= P_OVERFLOW;
	} else {
		instance->pins |= PIN_SO_B;
	}
}

uint8_t sync(struct W65C02S* instance)
{
	return (instance->pins & PIN_SYNC) != 0;
}

void reset(struct W65C02S* instance, uint8_t state)
{
	instance->resetting = 1;
	instance->pins &= ~PIN_RES_B;
}

uint8_t vectorPull(struct W65C02S* instance)
{
	return instance->handlingInterrupt || instance->handlingNMI || instance->resetting;
}

int attachDevice(struct W65C02S* instance, void* clockFunction)
{instance->devices[instance->nDevices] = clockFunction;
	return instance->nDevices++;
}


/**
 * #######################################################################################################################################################
 * #######################################################################################################################################################
 * ##                                                                                                                                                   ##
 * ##             All lines beyond are internal functions only                                                                                          ##
 * ##                                                                                                                                                   ##
 * #######################################################################################################################################################
 * #######################################################################################################################################################
 */


void clockDevices(struct W65C02S* instance)
{
	for (int i = 0, d = 0; i < 8192; i++) {
		if (d == instance->nDevices) return;
		if (instance->devices[i] != 0) {
			d++;
			void (*ptr)(struct W65C02S*) = instance->devices[i];
			ptr(instance);
		}
	}
}

void fetchOpcode(struct W65C02S* instance)
{
	instance->addressBus = instance->pc++;
	instance->pins |= PIN_RW_B;
	clockDevices(instance);
	instance->instructionRegister = instance->dataBus;
	instance->internalState = STATE_EXECUTE;
	instance->timingControl = 0;
}

void execute(struct W65C02S* instance)
{
	switch (instance->instructionRegister) {
		case 0x00: brk_stack(instance); break;
		case 0x01: ora_zeropage_indexed_indirect(instance); break;
		case 0x04: tsb_zeropage(instance); break;
		case 0x05: ora_zeropage(instance); break;
		case 0x06: asl_zeropage(instance); break;
		case 0x07: rmb0_zeropage(instance); break;
		case 0x08: php_stack(instance); break;
		case 0x09: ora_immediate(instance); break;
		case 0x0A: asl_accumulator(instance); break;
		case 0x0C: tsb_absolute(instance); break;
		case 0x0D: ora_absolute(instance); break;
		case 0x0E: asl_absolute(instance); break;
		case 0x0F: bbr0_relative(instance); break;
		case 0x10: bpl_relative(instance); break;
		case 0x11: ora_zeropage_indirect_y_indexed(instance); break;
		case 0x12: ora_zeropage_indirect(instance); break;
		case 0x14: trb_zeropage(instance); break;
		case 0x15: ora_zeropage_x_indexed(instance); break;
		case 0x16: asl_zeropage_x_indexed(instance); break;
		case 0x17: rmb1_zeropage(instance); break;
		case 0x18: clc_implied(instance); break;
		case 0x19: ora_absolute_y_indexed(instance); break;
		case 0x1A: inc_accumulator(instance); break;
		case 0x1C: trb_absolute(instance); break;
		case 0x1D: ora_absolute_x_indexed(instance); break;
		case 0x1E: asl_absolute_x_indexed(instance); break;
		case 0x1F: bbr1_relative(instance); break;
		case 0x20: jsr_absolute(instance); break;
		case 0x21: and_zeropage_indexed_indirect(instance); break;
		case 0x24: bit_zeropage(instance); break;
		case 0x25: and_zeropage(instance); break;
		case 0x26: rol_zeropage(instance); break;
		case 0x27: rmb2_zeropage(instance); break;
		case 0x28: plp_stack(instance); break;
		case 0x29: and_immediate(instance); break;
		case 0x2A: rol_accumolator(instance); break;
		case 0x2C: bit_absolute(instance); break;
		case 0x2D: and_absolute(instance); break;
		case 0x2E: rol_absolute(instance); break;
		case 0x2F: bbr2_relative(instance); break;
		case 0x30: bmi_relative(instance); break;
		case 0x31: and_zeropage_indirect_y_indexed(instance); break;
		case 0x32: and_zeropage_indirect(instance); break;
		case 0x34: bit_zeropage_x_indexed(instance); break;
		case 0x35: and_zeropage_x_indexed(instance); break;
		case 0x36: rol_zeropage_x_indexed(instance); break;
		case 0x37: rmb3_zeropage(instance); break;
		case 0x38: sec_implied(instance); break;
		case 0x39: and_absolute_y_indexed(instance); break;
		case 0x3A: dec_accumulator(instance); break;
		case 0x3C: bit_absolute_x_indexed(instance); break;
		case 0x3D: and_absolute_x_indexed(instance); break;
		case 0x3E: rol_absolute_x_indexed(instance); break;
		case 0x3F: bbr3_relative(instance); break;
		case 0x40: rti_stack(instance); break;
		case 0x41: eor_zeropage_indexed_indirect(instance); break;
		case 0x45: eor_zeropage(instance); break;
		case 0x46: lsr_zeropage(instance); break;
		case 0x47: rmb4_zeropage(instance); break;
		case 0x48: pha_stack(instance); break;
		case 0x49: eor_immediate(instance); break;
		case 0x4A: lsr_accumulator(instance); break;
		case 0x4C: jmp_absolute(instance); break;
		case 0x4D: eor_absolute(instance); break;
		case 0x4E: lsr_absolute(instance); break;
		case 0x4F: bbr4_relative(instance); break;
		case 0x50: bvc_relative(instance); break;
		case 0x51: eor_zeropage_indirect_y_indexed(instance); break;
		case 0x52: eor_zeropage_indirect(instance); break;
		case 0x55: eor_zeropage_x_indexed(instance); break;
		case 0x56: lsr_zeropage_x_indexed(instance); break;
		case 0x57: rmb5_zeropage(instance); break;
		case 0x58: cli_implied(instance); break;
		case 0x59: eor_absolute_y_indexed(instance); break;
		case 0x5A: phy_stack(instance); break;
		case 0x5D: eor_absolute_x_indexed(instance); break;
		case 0x5E: lsr_absolute_x_indexed(instance); break;
		case 0x5F: bbr5_relative(instance); break;
		case 0x60: rts_stack(instance); break;
		case 0x61: adc_zeropage_indexed_indirect(instance); break;
		case 0x64: stz_zeropage(instance); break;
		case 0x65: adc_zeropage(instance); break;
		case 0x66: ror_zeropage(instance); break;
		case 0x67: rmb6_zeropage(instance); break;
		case 0x68: pla_stack(instance); break;
		case 0x69: adc_immediate(instance); break;
		case 0x6A: ror_accumulatot(instance); break;
		case 0x6C: jmp_absolute_indirect(instance); break;
		case 0x6D: adc_absolute(instance); break;
		case 0x6E: ror_absolute(instance); break;
		case 0x6F: bbr6_relative(instance); break;
		case 0x70: bvs_relative(instance); break;
		case 0x71: adc_zeropage_indirect_y_indexed(instance); break;
		case 0x72: adc_zeropage_indirect(instance); break;
		case 0x74: stz_zeropage_x_indexed(instance); break;
		case 0x75: adc_zeropage_x_indexed(instance); break;
		case 0x76: ror_zeropage_x_indexed(instance); break;
		case 0x77: rmb7_zeropage(instance); break;
		case 0x78: sei_implied(instance); break;
		case 0x79: adc_absolute_y_indexed(instance); break;
		case 0x7A: ply_stack(instance); break;
		case 0x7C: jmp_absolute_indexed_indirect(instance); break;
		case 0x7D: adc_absolute_x_indexed(instance); break;
		case 0x7E: ror_absolute_x_indexed(instance); break;
		case 0x7F: bbr7_relative(instance); break;
		case 0x80: bra_relative(instance); break;
		case 0x81: sta_zeropage_indexed_indirect(instance); break;
		case 0x84: sty_zeropage(instance); break;
		case 0x85: sta_zeropage(instance); break;
		case 0x86: stx_zeropage(instance); break;
		case 0x87: smb0_zeropage(instance); break;
		case 0x88: dey_implied(instance); break;
		case 0x89: bit_immediate(instance); break;
		case 0x8A: txa_implied(instance); break;
		case 0x8C: sty_absolute(instance); break;
		case 0x8D: sta_absolute(instance); break;
		case 0x8E: stx_absolute(instance); break;
		case 0x8F: bbs0_relative(instance); break;
		case 0x90: bcc_relative(instance); break;
		case 0x91: sta_zeropage_indirect_y_indexed(instance); break;
		case 0x92: sta_zeropage_indirect(instance); break;
		case 0x94: sty_zeropage_x_indexed(instance); break;
		case 0x95: sta_zeropage_x_indexed(instance); break;
		case 0x96: stx_zeropage_y_indexed(instance); break;
		case 0x97: smb1_zeropage(instance); break;
		case 0x98: tya_implied(instance); break;
		case 0x99: sta_absolute_y_indexed(instance); break;
		case 0x9A: txs_implied(instance); break;
		case 0x9C: stz_absolute(instance); break;
		case 0x9D: sta_absolute_x_indexed(instance); break;
		case 0x9E: stz_absolute_x_indexed(instance); break;
		case 0x9F: bbs1_relative(instance); break;
		case 0xA0: ldy_immediate(instance); break;
		case 0xA1: lda_zeropage_indexed_indirect(instance); break;
		case 0xA2: ldx_immediate(instance); break;
		case 0xA4: ldy_zeropage(instance); break;
		case 0xA5: lda_zeropage(instance); break;
		case 0xA6: ldx_zeropage(instance); break;
		case 0xA7: smb2_zeropage(instance); break;
		case 0xA8: tay_implied(instance); break;
		case 0xA9: lda_immediate(instance); break;
		case 0xAA: tax_implied(instance); break;
		case 0xAC: ldy_absolute(instance); break;
		case 0xAD: lda_absolute(instance); break;
		case 0xAE: ldx_absolute(instance); break;
		case 0xAF: bbs2_relative(instance); break;
		case 0xB0: bcs_relative(instance); break;
		case 0xB1: lda_zeropage_indirect_y_indexed(instance); break;
		case 0xB2: lda_zeropage_indirect(instance); break;
		case 0xB4: ldy_zeropage_x_indexed(instance); break;
		case 0xB5: lda_zeropage_x_indexed(instance); break;
		case 0xB6: ldx_zeropage_y_indexed(instance); break;
		case 0xB7: smb3_zeropage(instance); break;
		case 0xB8: clv_implied(instance); break;
		case 0xB9: lda_absolute_y_indexed(instance); break;
		case 0xBA: tsx_implied(instance); break;
		case 0xBC: ldy_absolute_x_indexed(instance); break;
		case 0xBD: lda_absolute_x_indexed(instance); break;
		case 0xBE: ldx_absolute_y_indexed(instance); break;
		case 0xBF: bbs3_relative(instance); break;
		case 0xC0: cpy_immediate(instance); break;
		case 0xC1: cmp_zeropage_indexed_indirect(instance); break;
		case 0xC4: cpy_zeropage(instance); break;
		case 0xC5: cmb_zeropage(instance); break;
		case 0xC6: dec_zeropage(instance); break;
		case 0xC7: smb4_zeropage(instance); break;
		case 0xC8: iny_implied(instance); break;
		case 0xC9: cmp_immediate(instance); break;
		case 0xCA: dex_implied(instance); break;
		case 0xCB: wai_implied(instance); break;
		case 0xCC: cpy_absolute(instance); break;
		case 0xCD: cmp_absolute(instance); break;
		case 0xCE: dec_absolute(instance); break;
		case 0xCF: bbs4_relative(instance); break;
		case 0xD0: bne_relative(instance); break;
		case 0xD1: cmp_zeropage_indirect_y_indexed(instance); break;
		case 0xD2: cmp_zeropage_indirect(instance); break;
		case 0xD5: cmp_zeropage_x_indexed(instance); break;
		case 0xD6: dec_zeropage_x_indexed(instance); break;
		case 0xD7: smb5_zeropage(instance); break;
		case 0xD8: cld_implied(instance); break;
		case 0xD9: cmp_absolute_y_indexed(instance); break;
		case 0xDA: phx_stack(instance); break;
		case 0xDB: stp_implied(instance); break;
		case 0xDD: cmp_absolute_x_indexed(instance); break;
		case 0xDE: dec_absolute_x_indexed(instance); break;
		case 0xDF: bbs5_relative(instance); break;
		case 0xE0: cpx_immediate(instance); break;
		case 0xE1: sbc_zeropage_indexed_indirect(instance); break;
		case 0xE4: cpx_zeropage(instance); break;
		case 0xE5: sbc_zeropage(instance); break;
		case 0xE6: inc_zeropage(instance); break;
		case 0xE7: smb6_zeropage(instance); break;
		case 0xE8: inx_implied(instance); break;
		case 0xE9: sbc_immediate(instance); break;
		case 0xEA: nop_implied(instance); break;
		case 0xEC: cpx_absolute(instance); break;
		case 0xED: sbc_absolute(instance); break;
		case 0xEE: inc_absolute(instance); break;
		case 0xEF: bbs6_relative(instance); break;
		case 0xF0: beq_relative(instance); break;
		case 0xF1: sbc_zeropage_indirect_y_indexed(instance); break;
		case 0xF2: sbc_zeropage_indirect(instance); break;
		case 0xF5: sbc_zeropage_x_indexed(instance); break;
		case 0xF6: inc_zeropage_x_indexed(instance); break;
		case 0xF7: smb7_zeropage(instance); break;
		case 0xF8: sed_implied(instance); break;
		case 0xF9: sbc_absolute_y_indexed(instance); break;
		case 0xFA: plx_stack(instance); break;
		case 0xFD: sbx_absolute_x_indexed(instance); break;
		case 0xFE: inc_absolute_x_indexed(instance); break;
		case 0xFF: bbs7_relative(instance); break;
		
		default: nop_implied(instance); break;
	}
	instance->timingControl++;
	clockDevices(instance);
}

void   brk_stack(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ora_zeropage_indexed_indirect(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus + instance->x;
		instance->addressBus = tmp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		tmp = 0x0000 | instance->dataBus;
		instance->addressBus++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		tmp = (instance->dataBus << 8) | tmp;
		instance->addressBus = tmp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		tmp = instance->dataBus;
	}
	if (instance->timingControl == 5) {
		instance->a |= tmp;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   tsb_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		instance->stateRegister = (instance->a & instance->dataBus) ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->dataBus |= instance->a;
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   ora_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = 0x0000 | instance->dataBus;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   asl_zeropage(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->stateRegister = (instance->dataBus & 0x80) ? (instance->stateRegister | P_CARRY) : (instance->stateRegister & ~P_CARRY);
	}
	if (instance->timingControl == 3) {
		instance->dataBus <<= 1;
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   rmb0_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 0);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   php_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins &= ~PIN_RW_B;
		instance->addressBus = instance->sp--;
		instance->dataBus = instance->stateRegister;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   ora_immediate(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
	
}

void   asl_accumulator(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_CARRY : instance->stateRegister & ~P_CARRY;
		instance->a <<= 1;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->stateRegister = (instance->a) ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   tsb_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 2) {
		instance->addressBus = ((uint16_t)instance->dataBus << 8) | tmp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		instance->stateRegister = (instance->a & instance->dataBus) ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->dataBus |= instance->a;
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   ora_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		tmp = (instance->dataBus << 8) | tmp;
		instance->addressBus = tmp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   asl_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		tmp = (instance->dataBus << 8) | tmp;
		instance->addressBus = tmp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		instance->dataBus <<= 1;
		instance->addressBus = tmp;
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bbr0_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 0))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bpl_relative(struct W65C02S* instance)
{
	static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (! (instance->stateRegister & P_NEGATIVE)) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   ora_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	static uint16_t tmp, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		tmp = instance->dataBus;
		instance->addressBus++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		tmp = (((uint16_t)instance->dataBus) << 8) | (tmp & 0xff);
		page = instance->addressBus = tmp + instance->y;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		if (page == (0xff00 & instance->addressBus)) instance->internalState = STATE_FETCH_OPCODE;
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   ora_zeropage_indirect(struct W65C02S* instance)
{
	static uint16_t tmp, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		tmp = instance->dataBus;
		instance->addressBus++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		tmp = (((uint16_t)instance->dataBus) << 8) | (tmp & 0xff);
		page = 0xff00 & instance->pc;
		instance->addressBus = tmp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   trb_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ora_zeropage_x_indexed(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus + instance->x;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   asl_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rmb1_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 1);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   clc_implied(struct W65C02S* instance)
{
	instance->stateRegister &= ~P_CARRY;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   ora_absolute_y_indexed(struct W65C02S* instance)
{
	static uint16_t tmp, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->addressBus = ((((uint16_t)instance->dataBus) << 8) | (tmp & 0xff)) + instance->y;
		page = instance->pc & 0xff00;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		if (page == (instance->addressBus & 0xff00)) instance->internalState = STATE_FETCH_OPCODE;
	}
	if (instance->timingControl == 4) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   inc_accumulator(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->a++;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   trb_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ora_absolute_x_indexed(struct W65C02S* instance)
{
	static uint16_t tmp, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->addressBus = ((((uint16_t)instance->dataBus) << 8) | (tmp & 0xff)) + instance->x;
		page = instance->pc & 0xff00;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		instance->a |= instance->dataBus;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		if (page == (instance->addressBus & 0xff00)) instance->internalState = STATE_FETCH_OPCODE;
	}
	if (instance->timingControl == 4) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   asl_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbr1_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 1))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   jsr_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		uint16_t t = instance->dataBus;
		tmp = (t << 8) | tmp;
		instance->addressBus = instance->sp--;
		instance->dataBus = (instance->pc >> 8) & 0xff;
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		instance->addressBus = instance->sp--;
		instance->dataBus = instance->pc & 0xff;
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pc = tmp;
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   and_zeropage_indexed_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bit_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   and_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rol_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rmb2_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 2);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   plp_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = ++instance->sp;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->stateRegister = instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   and_immediate(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->a &= instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   rol_accumolator(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bit_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   and_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rol_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbr2_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 2))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bmi_relative(struct W65C02S* instance)
{
		static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (instance->stateRegister & P_NEGATIVE) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   and_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   and_zeropage_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bit_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   and_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rol_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rmb3_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 3);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sec_implied(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->stateRegister |= P_CARRY;
		instance->internalState  = STATE_FETCH_OPCODE;
	}
}

void   and_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   dec_accumulator(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->a--;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bit_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   and_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rol_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbr3_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 3))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   rti_stack(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = ++instance->sp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->stateRegister = instance->dataBus;
		instance->addressBus = ++instance->sp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		tmp = instance->dataBus;
		instance->addressBus = ++instance->sp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		uint16_t t = instance->dataBus;
		tmp = (t << 8) | tmp;
		instance->pc = tmp;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   eor_zeropage_indexed_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   eor_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lsr_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rmb4_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 4);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   pha_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins &= ~PIN_RW_B;
		instance->addressBus = instance->sp--;
		instance->dataBus = instance->a;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   eor_immediate(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->a ^= instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   lsr_accumulator(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->stateRegister = (instance->a & 0x01) ? instance->stateRegister | P_CARRY : instance->stateRegister & ~P_CARRY;
		instance->a >>= 1;
		instance->stateRegister &= ~P_NEGATIVE;
		instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   jmp_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		uint16_t t = instance->dataBus;
		instance->pc = (t << 8) | tmp;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   eor_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lsr_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbr4_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 4))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bvc_relative(struct W65C02S* instance)
{
	static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (! (instance->stateRegister & P_OVERFLOW)) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   eor_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   eor_zeropage_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   eor_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lsr_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rmb5_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 5);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   cli_implied(struct W65C02S* instance)
{
	instance->stateRegister &= ~P_IRQDISABLE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   eor_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   phy_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins &= ~PIN_RW_B;
		instance->addressBus = instance->sp--;
		instance->dataBus = instance->y;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   eor_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lsr_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbr5_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 5))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   rts_stack(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = ++instance->sp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = ++instance->sp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		uint16_t t = instance->dataBus;
		tmp = (t << 8) | tmp;
		instance->pc = tmp;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   adc_zeropage_indexed_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   stz_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   adc_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ror_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rmb6_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 6);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   pla_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = ++instance->sp;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->a = instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   adc_immediate(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		uint16_t c = (instance->a & instance->dataBus) << 1;
		c = c | (((instance->a ^ instance->dataBus) & c) << 1);
		if (c & 0x0100) instance->stateRegister |= P_CARRY;
		instance->a += instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   ror_accumulatot(struct W65C02S* instance)
{
	uint8_t tmp = instance->stateRegister & P_CARRY;
	instance->stateRegister = (instance->a & 0x01) ? instance->stateRegister | P_CARRY : instance->stateRegister & ~P_CARRY;
	instance->a >>= 1;
	if (tmp) {
		instance->a |= 0x80;
		instance->stateRegister |= P_NEGATIVE;
	} else {
		instance->stateRegister &= ~P_NEGATIVE;
	}
	if (!instance->a) instance->stateRegister |= P_ZERO;
	else instance->stateRegister &= ~P_ZERO;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   jmp_absolute_indirect(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		uint16_t t = instance->dataBus;
		tmp = (t << 8) | tmp;
		instance->addressBus = tmp;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		tmp = instance->dataBus;
		instance->addressBus++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		uint16_t t = instance->dataBus;
		instance->pc = (t << 8) | tmp;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   adc_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ror_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbr6_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 6))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bvs_relative(struct W65C02S* instance)
{
	static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (instance->stateRegister & P_OVERFLOW) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   adc_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   adc_zeropage_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   stz_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   adc_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ror_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   rmb7_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus &= ~(1 << 7);
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sei_implied(struct W65C02S* instance)
{
	instance->stateRegister |= P_IRQDISABLE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   adc_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ply_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = ++instance->sp;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->y = instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   jmp_absolute_indexed_indirect(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		uint16_t t = instance->dataBus;
		tmp = (t << 8) | tmp;
		instance->addressBus = tmp + instance->x;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		tmp = instance->dataBus;
		instance->addressBus++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		uint16_t t = instance->dataBus;
		instance->pc = (t << 8) | tmp;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   adc_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ror_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbr7_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (! (value & (1 << 7))) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bra_relative(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->pc += (int8_t)instance->dataBus;
	}
	if (instance->timingControl == 2) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sta_zeropage_indexed_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sty_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sta_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   stx_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb0_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 0;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   dey_implied(struct W65C02S* instance)
{
	instance->y--;
	instance->stateRegister = instance->y ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->y & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   bit_immediate(struct W65C02S* instance)
{
	//TODO: Implement
}

void   txa_implied(struct W65C02S* instance)
{
	instance->a = instance->x;
	instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   sty_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 2) {
		tmp = (instance->dataBus << 8) | tmp;
		instance->pins &= ~PIN_RW_B;
		instance->addressBus = tmp;
		instance->dataBus = instance->y;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sta_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 2) {
		tmp = (instance->dataBus << 8) | tmp;
		instance->pins &= ~PIN_RW_B;
		instance->addressBus = tmp;
		instance->dataBus = instance->a;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   stx_absolute(struct W65C02S* instance)
{
	static uint16_t tmp;
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 1) {
		tmp = instance->dataBus;
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
	}
	if (instance->timingControl == 2) {
		tmp = (instance->dataBus << 8) | tmp;
		instance->pins &= ~PIN_RW_B;
		instance->addressBus = tmp;
		instance->dataBus = instance->x;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bbs0_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 0)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bcc_relative(struct W65C02S* instance)
{
	static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (! (instance->stateRegister & P_CARRY)) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sta_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sta_zeropage_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sty_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sta_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   stx_zeropage_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb1_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 1;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   tya_implied(struct W65C02S* instance)
{
	instance->a = instance->y;
	instance->stateRegister = instance->a ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->a & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   sta_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   txs_implied(struct W65C02S* instance)
{
	instance->sp = instance->x;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   stz_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sta_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   stz_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbs1_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 1)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   ldy_immediate(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lda_zeropage_indexed_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ldx_immediate(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ldy_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lda_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ldx_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb2_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 2;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   tay_implied(struct W65C02S* instance)
{
	instance->y = instance->a;
	instance->stateRegister = instance->y ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->y & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   lda_immediate(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = instance->pc++;
		clockDevices(instance);
		instance->a = instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   tax_implied(struct W65C02S* instance)
{
	instance->x = instance->a;
	instance->stateRegister = instance->x ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->x & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   ldy_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lda_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ldx_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbs2_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 2)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bcs_relative(struct W65C02S* instance)
{
	static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (instance->stateRegister & P_CARRY) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   lda_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lda_zeropage_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ldy_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lda_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ldx_zeropage_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb3_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 3;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   clv_implied(struct W65C02S* instance)
{
	instance->stateRegister &= ~P_OVERFLOW;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   lda_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   tsx_implied(struct W65C02S* instance)
{
	instance->x = instance->sp;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   ldy_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   lda_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   ldx_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbs3_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 3)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   cpy_immediate(struct W65C02S* instance)
{
	//TODO: Implement
}

void   cmp_zeropage_indexed_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   cpy_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   cmb_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   dec_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb4_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 4;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   iny_implied(struct W65C02S* instance)
{
	instance->y++;
	instance->stateRegister = instance->y ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->y & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   cmp_immediate(struct W65C02S* instance)
{
	//TODO: Implement
}

void   dex_implied(struct W65C02S* instance)
{
	instance->x--;
	instance->stateRegister = instance->x ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->x & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   wai_implied(struct W65C02S* instance)
{
	// TODO Make More Accurate
	if (!(instance->pins & PIN_IRQ_B)) instance->internalState = STATE_FETCH_OPCODE;
}

void   cpy_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   cmp_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   dec_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbs4_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 4)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   bne_relative(struct W65C02S* instance)
{
	static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (instance->stateRegister & P_ZERO) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   cmp_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   cmp_zeropage_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   cmp_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   dec_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb5_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 5;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   cld_implied(struct W65C02S* instance)
{
	instance->stateRegister &= ~P_DECIMAL;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   cmp_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   phx_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins &= ~PIN_RW_B;
		instance->addressBus = instance->sp--;
		instance->dataBus = instance->x;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   stp_implied(struct W65C02S* instance)
{
	// Stopping the processor by not resetting it to the fetch opcode state, so it will not fetch another opcode
}

void   cmp_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   dec_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbs5_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 5)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   cpx_immediate(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sbc_zeropage_indexed_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   cpx_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sbc_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   inc_zeropage(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb6_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 6;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   inx_implied(struct W65C02S* instance)
{
	instance->x++;
	instance->stateRegister = instance->x ? instance->stateRegister & ~P_ZERO : instance->stateRegister | P_ZERO;
	instance->stateRegister = (instance->x & 0x80) ? instance->stateRegister | P_NEGATIVE : instance->stateRegister & ~P_NEGATIVE;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   sbc_immediate(struct W65C02S* instance)
{
	//TODO: Implement
}

void   nop_implied(struct W65C02S* instance)
{
	instance->internalState = STATE_FETCH_OPCODE;
}

void   cpx_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sbc_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   inc_absolute(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbs6_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 6)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   beq_relative(struct W65C02S* instance)
{
	static uint8_t page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		if (! (instance->stateRegister & P_ZERO)) {
			page = (instance->pc >> 8) & 0xff;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 2) {
		if (page == ((instance->pc >> 8) & 0xff)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 3) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sbc_zeropage_indirect_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sbc_zeropage_indirect(struct W65C02S* instance)
{
	//TODO: Implement
}

void   sbc_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   inc_zeropage_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   smb7_zeropage(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		instance->dataBus |= 1 << 7;
	}
	if (instance->timingControl == 3) {
		instance->pins &= ~PIN_RW_B;
	}
	if (instance->timingControl == 4) {
		instance->pins |= PIN_RW_B;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sed_implied(struct W65C02S* instance)
{
	instance->stateRegister |= P_DECIMAL;
	instance->internalState = STATE_FETCH_OPCODE;
}

void   sbc_absolute_y_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   plx_stack(struct W65C02S* instance)
{
	if (instance->timingControl == 0) {
		instance->pins |= PIN_RW_B;
		instance->addressBus = ++instance->sp;
	}
	if (instance->timingControl == 1) {
		instance->pins |= PIN_RW_B;
		instance->x = instance->dataBus;
		instance->internalState = STATE_FETCH_OPCODE;
	}
}

void   sbx_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   inc_absolute_x_indexed(struct W65C02S* instance)
{
	//TODO: Implement
}

void   bbs7_relative(struct W65C02S* instance)
{
	static uint8_t value, page;
	if (instance->timingControl == 0) {
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 1) {
		instance->addressBus = instance->dataBus & 0xff;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 2) {
		value = instance->dataBus;
		instance->addressBus = instance->pc++;
		instance->pins |= PIN_RW_B;
	}
	if (instance->timingControl == 3) {
		if (value & (1 << 7)) {
			page = instance->pc >> 8;
			instance->pc += (int8_t)instance->dataBus;
		} else {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 4) {
		if (page == (uint8_t)(instance->pc >> 8)) {
			instance->internalState = STATE_FETCH_OPCODE;
		}
	}
	if (instance->timingControl == 5) {
		instance->internalState = STATE_FETCH_OPCODE;
	}
}
