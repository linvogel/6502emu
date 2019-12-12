#include "memory64k.h"

uint8_t* mem[256];
struct W65C02S* inst[256] = { 0 };
int nInst = 0;

void clockMem64k(struct W65C02S* instance)
{
	for (int i = 0; i < 256; i++) {
		if (inst[i] == instance) {
			if (instance->pins & PIN_RW_B) {
				instance->dataBus = mem[i][instance->addressBus];
			}
			if (!(instance->pins & PIN_RW_B)) {
				mem[i][instance->addressBus] = instance->dataBus;
			}
			return;
		}
	}
}

void connectMem64k(struct W65C02S* instance)
{
	nInst++;
	int i = 0;
	for (; i < 256 && inst[i] != 0; i++);
	inst[i] = instance;
	mem[i] = (uint8_t*)malloc(sizeof(uint8_t) * 64*1024);
}

void disconnectMem64k(struct W65C02S* instance)
{
	for (int i = 0; i < 256; i++) {
		if (inst[i] == instance) {
			nInst--;
			inst[i] = 0;
			return;
		}
	}
}

void writeMem64k(struct W65C02S* instance, uint8_t* data)
{
	for (int i = 0; i < 256; i++) {
		if (inst[i] == instance) {
			for (int k = 0; k < 64*1024; k++) mem[i][k] = data[k];
			return;
		}
	}
}

void readMem64k(struct W65C02S* instance, uint8_t* data)
{
	for (int i = 0; i < 256; i++) {
		if (inst[i] == instance) {
			for (int k = 0; k < 64*1024; k++) data[k] = mem[i][k];
			return;
		}
	}
}