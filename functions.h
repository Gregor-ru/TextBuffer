#pragma once

typedef struct SFile
{
	FILE* f;
	char* buffer;
	unsigned int offSet;

} TFile;

typedef struct SBuffer
{
	TFile* files;
	unsigned int size;
	int filesCount, maxFilesCount;

} TBuffer;

char* concat(char* s1, char* s2);
void SystemInit(unsigned int bufferSize);
void SystemClose();
int open(char* fileName, char* mode);
void close(int fileIndex);
void read(int fileID, void* buff, unsigned int sizeToRead);
void write(int fileID, void* buff, unsigned int sizeToWrite);