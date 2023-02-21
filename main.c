#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"

int main(void)
{
	char buff[BUFFER_SIZE];
	char fromFileNameInDirect[MAXLEN] = { 0 };
	char toFileNameInDirect[MAXLEN] = { 0 };

	int fFirst, fSecond, fThird;

	printf("%s", "Enter file name to read: ");
	if (scanf("%s", &fromFileNameInDirect));
	printf("%s", "\nEnter file name to write: ");
	if (scanf("%s", &toFileNameInDirect));

	char* filePathFirst = concat("D:/C-C++Projects/Files/", fromFileNameInDirect);
	char* filePathSecond = concat("D:/C-C++Projects/Files/", toFileNameInDirect);
	char* filePathThird = concat("D:/C-C++Projects/Files/", "out2.txt");

	SystemInit(1);

	fFirst = open(filePathFirst, "r");
	fSecond = open(filePathSecond, "w");
	fThird = open(filePathThird, "w");

	read(fFirst, buff, 19);

	for (int i = 0; i < 19; i++)
		printf("%c", buff[i]);

	write(fSecond, buff, 19);

	read(fFirst, buff, 30);
	write(fThird, buff, 30);

	close(fFirst);
	close(fSecond);
	close(fThird);

	SystemClose();

	return 0;
}