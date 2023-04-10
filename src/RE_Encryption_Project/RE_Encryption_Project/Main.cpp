#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENC_EXT ".enc"

void xorEncrypt(FILE *src, FILE *dst);

// Function declarations
void xorEncrypt(FILE *src, FILE *dst)
{
	char c;
	while( (c = fgetc(src) ) != EOF )
	{
		// xor with 0
		c ^= 0;
		fwrite(&c, 1, 1, dst);
	}
}

int main(int argc, char* argv[])
{
	char *readFile, *writeFile; // to read/write file
	FILE *readPtr, *writePtr;
	char *buffer;

	// check cmd parameters
	if(argc < 2)
	{
		printf("Usage: .\\encrypt.exe <filename>\n");
		return 0;
	}

	// open file to encrypt
	readFile = argv[1];
	readPtr = fopen(readFile, "rb");
	if(!readPtr)
	{
		fprintf(stderr, "Error: could not open file '%s'\n", readFile);
		return -1;
	}

	writeFile = (char*) malloc( sizeof(char) * (strlen(readFile) + 4) );
	if(!writeFile)
	{
		fprintf(stderr, "Error: could not allocate memory for writeFile string\n");
		fclose(readPtr);
		return -1;
	}

	strcpy(writeFile, readFile);
	strcat(writeFile, ENC_EXT);

	// open file to write encrypted data to
	writePtr = fopen(writeFile, "wb");
	if(!writePtr)
	{
		fprintf(stderr, "Error: could not open file '%s'\n", writeFile);
		fclose(readPtr);
		return -1;
	}

	xorEncrypt(readPtr, writePtr);

	fclose(readPtr);
	fclose(writePtr);
	return 0;
}