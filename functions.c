#pragma once

#include "framework.h"
#include "functions.h"

static TBuffer textBuffer;

char* concat(char* s1, char* s2) {

	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);

	char* result = malloc(len1 + len2 + 1);

	if (!result) {
		fprintf(stderr, "malloc() failed: insufficient memory!\n");
		return NULL;
	}

	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1);

	return result;

}

void SystemInit(unsigned int bufferSize)
{
	textBuffer.filesCount = 0;
	textBuffer.maxFilesCount = MAX_FILE_COUNT;
	textBuffer.files = malloc(sizeof(TFile) * textBuffer.maxFilesCount);
	textBuffer.size = bufferSize;

	for (int i = 0; i < textBuffer.maxFilesCount; i++)
	{
		if ((textBuffer.files[i].buffer = malloc(textBuffer.size)) == NULL) exit(30);

		textBuffer.files[i].offSet = 0;
	}
}

void SystemClose()
{
	textBuffer.size = 0;

	for (int i = 0; i < textBuffer.filesCount; i++)
	{
		if (textBuffer.files[i].f != NULL)
			fclose(textBuffer.files[i].f);
		if (textBuffer.files[i].buffer != NULL)
			free(textBuffer.files[i].buffer);
	}
	if (textBuffer.files != NULL)
		free(textBuffer.files);
}

int open(char* fileName, char* mode)
{

	if (textBuffer.filesCount >= textBuffer.maxFilesCount)
	{
		textBuffer.files = realloc(textBuffer.files, sizeof(TFile) * textBuffer.maxFilesCount * 2);
		textBuffer.maxFilesCount *= 2;

		for (int i = textBuffer.filesCount; i < textBuffer.maxFilesCount; i++)
		{
			if ((textBuffer.files[i].buffer = malloc(textBuffer.size)) == NULL) exit(30);

			textBuffer.files[i].offSet = 0;
		}
	}

	textBuffer.files[textBuffer.filesCount].f = fopen(fileName, mode);
	return textBuffer.filesCount++;
}

void close(int fileIndex)
{
	if (textBuffer.files[fileIndex].f != NULL)
		fclose(textBuffer.files[fileIndex].f);
}

void read(int fileID, void *buff, unsigned int sizeToRead)
{
	int i = 0, n;

	TFile File = textBuffer.files[fileID];
	FILE *F = File.f;

	while (F != EOF && i < sizeToRead)
	{
		n = fread(File.buffer, 1, textBuffer.size < (sizeToRead - i) ? textBuffer.size : (sizeToRead - i), F);
		memcpy((char*)buff+i, File.buffer, n);
		i += n;
	}
}

void write(int fileID, void* buff, unsigned int sizeToWrite)
{
	int i = 0, n;

	TFile File = textBuffer.files[fileID];
	FILE *F = File.f;

	while (i < sizeToWrite && buff != NULL)
	{
		n = textBuffer.size < (sizeToWrite - i) ? textBuffer.size : (sizeToWrite - i);
		memcpy(File.buffer, (char*)buff + i, n);

		i += fwrite(File.buffer, 1, n, F);
	}
}