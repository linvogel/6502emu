#ifndef HEADER_MEMORY64K
#define HEADER_MEMORY64K

#include "w65c02s.h"

void clockMem64k(struct W65C02S* instance);
void connectMem64k(struct W65C02S* instance);
void disconnectMem64k(struct W65C02S* instance);
void writeMem64k(struct W65C02S* instance, uint8_t* data);
void readMem64k(struct W65C02S* instance, uint8_t* data);

#endif