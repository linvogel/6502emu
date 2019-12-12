#include <stdio.h>
#include <signal.h>
#include <malloc.h>

#include "memory64k.h"
#include "w65c02s.h"

volatile uint8_t running = 1;

uint8_t memInit[64*1024];

void signalHandler(int sNum)
{
	printf("Handling SIGINT: %d\n", sNum);
	running = 0;
}

int main( void )
{
	puts("Starting Emulator");
	signal(SIGINT, signalHandler);
	
	puts("Setting up processor");
	struct W65C02S tmp;
	tmp.a = 0;
	tmp.x = 0;
	tmp.y = 0;
	tmp.stateRegister = 0;
	tmp.instructionRegister = 0;
	tmp.timingControl = 0;
	tmp.pc = 0;
	tmp.sp = 0;
	tmp.dataBus = 0;
	tmp.addressBus = 0;
	tmp.internalState = 0;
	tmp.handlingInterrupt = 0;
	tmp.handlingNMI = 0;
	tmp.resetting = 0;
	tmp.nDevices = 0;
	tmp.pins = 0;
	tmp.devices = calloc(sizeof(void*), 8192);
	const char* pat = "tmp.a: %d tmp.x: %d tmp.y: %d tmp.stateRegister: %d tmp.instructionRegister: %d tmp.timingControl: %d tmp.pc: %d tmp.sp: %d tmp.dataBus: %d tmp.addressBus: %d tmp.internalState: %d tmp.handlingInterrupt: %d tmp.handlingNMI: %d tmp.resetting: %d tmp.nDevices: %d tmp.devices: %d\n";
	printf(pat, tmp.a,tmp.x,tmp.y,tmp.stateRegister,tmp.instructionRegister,tmp.timingControl,tmp.pc,tmp.sp,tmp.dataBus,tmp.addressBus,tmp.internalState,tmp.handlingInterrupt,tmp.handlingNMI,tmp.resetting,tmp.nDevices,tmp.devices);
	struct W65C02S* processor = &tmp;
	
	puts("Initializing Memory");
	connectMem64k(processor);
	
	puts("Attaching Memory");
	attachDevice(processor, clockMem64k);
	
	puts("Writing initial memory");
	for (int i = 0; i < 1024*64; i++) memInit[i] = 0xEA;
	
	memInit[0x0010] = OP_LDA_IMMEDIATE;
	memInit[0x0011] = 0x42;
	memInit[0x0012] = OP_ORA_ZEROPAGE_INDEXED_INDIRECT;
	memInit[0x0013] = 0xA0;
	memInit[0x0014] = OP_ORA_ZEROPAGE;
	memInit[0x0015] = 0xA2;
	memInit[0x0016] = OP_ASL_ZEROPAGE;
	memInit[0x0017] = 0xA1;
	
	memInit[0x0050] = OP_STA_ABSOLUTE;
	memInit[0x0051] = 0x00;
	memInit[0x0052] = 0x00;
	
	memInit[0x00A0] = 0x00;
	memInit[0x00A1] = 0x10;
	memInit[0x00A2] = 0x01;
	
	
	
	memInit[0x1000] = 0x24;
	
	writeMem64k(processor, memInit);
	
	puts("Starting clock...");
	unsigned int i = 0;
	while (processor->pc < 0x00A0) {
		clock(processor);
		printf("Address: %04X Data: %02X RW: %c   PINS: 0x%016llx\n", processor->addressBus, processor->dataBus, (processor->pins & PIN_RW_B) ? 'r' : 'w', processor->pins);
		//getchar(); printf("\x1b[1A");
	}
	
	printf("Terminating...\n");
	free(processor->devices);
	
	readMem64k(processor, memInit);
	for (int i = 0; i < 4096; i++) {
		printf("%04x: ", i*16);
		for (int j = 0; j < 16; j++) printf("%02x %s", memInit[i*16 + j], j == 7 ? " " : "");
		printf("\n");
	}
	
	return 0;
}