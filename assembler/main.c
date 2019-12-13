#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STATE_INPUT_FILENAME 0
#define STATE_OUTPUT_FILENAME 1

uint8_t streq(const char* a, const char* b);

uint8_t parseLine();
void parseInstruction();
void append(uint8_t byte);

char* inputFileName = (char*)0;
char* outputFileName = "a.bin";

uint8_t* buffer;
int boff = 0;
int linenumber = 1;

FILE* in;
FILE* out;

int main(int argc, char** argv)
{
	int state = STATE_INPUT_FILENAME;
	for (int i = 1; i < argc; i++) {
		switch (state) {
			case STATE_OUTPUT_FILENAME:
				outputFileName = argv[i];
				state = STATE_INPUT_FILENAME;
				break;
			case STATE_INPUT_FILENAME:
				if (argv[i][0] != '-') inputFileName = argv[i];
				else {
					if (streq(argv[i], "-o")) state = STATE_OUTPUT_FILENAME;
				}
				break;
		}
	}
	if (state) {
		fprintf(stderr, "FATAL: Missing arguments at end of line!\n");
		exit(1);
	}
	if (inputFileName == 0) {
		fprintf(stderr, "FATAL: No inputfile specified!\n");
		exit(1);
	}
	
	in = fopen(inputFileName, "r");
	out = fopen(outputFileName, "wb");
	buffer = (uint8_t*)calloc(sizeof(uint8_t), 32*1024);
	
	while (parseLine()) linenumber++;;
	
cleanExit:
	free(buffer);
}

uint8_t streq(const char* a, const char* b)
{
	int ia = 0;
	int ib = 0;
	while (a[ia] && b[ib]) {
		if (a[ia] != b[ib]) return 0;
		ia++;
		ib++;
	}
	if (a[ia] || b[ib]) return 0;
	return 1;
}

uint8_t parseLine()
{
	uint8_t comment = 0;
	int mlen = 256;
	char* line = (char*)calloc(sizeof(char), mlen+1);
	int len = 0;
	char t = 0;
	uint8_t started = 0;
	while (t != '\n' && t != EOF) {
		t = fgetc(in);
		if (t != ' ' && t != '\t') {
			started = 1;
		}
		if (t == '#') comment = 1;
		if (!comment && started) {
			if (len == mlen) line = (char*)realloc(line, sizeof(char) * (mlen + 256 + 1));
			line[len++] = t;
		}
	}
	
	if (line[0] == '.') {
		char* label = &line[1];
		printf("Read label: %s", label);
	} else {
		char cmd[5] = { 0, 0, 0, 0, 0 };
		cmd[0] = line[0];
		cmd[1] = line[1];
		cmd[2] = line[2];
		if (cmd[3] != ' ' && cmd[3] != '\t') cmd[3] = line[3];
		printf("Command read: %s\n", cmd);
		
	}
	
	
	if (t == '\n') return 1;
	return 0;
}