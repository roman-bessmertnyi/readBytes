#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

char getBit(int input, int position)
{
   return (input >> position) & 1;
}

void writePin(int pin, int state)
{
	if (state)
	{
		digitalWrite (pin,  HIGH) ;
	}
	else
	{
		digitalWrite (pin,  LOW) ;
	}
}
 
int main()
{
	wiringPiSetup () ;
	pinMode (8, OUTPUT) ;
	pinMode (9, OUTPUT) ;
	pinMode (7, OUTPUT) ;
	pinMode (0, OUTPUT) ;
	
	char ch[2], file_name[25];
	int i;
	FILE *fp;

	printf("Enter name of a file you wish to see\n");
	fflush( stdout );
	gets(file_name);
	
	fp = fopen(file_name, "r"); // read mode

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	printf("The contents of %s file are:\n", file_name);
	
	for (i = 0; i < 2; ++i)
	{
		ch[i] = fgetc(fp);
	}

	i = atoi(ch);
	printf("%i\n", i);
	printf("In byte from\n");
	
	printf("%i", getBit(i, 4));
	printf("%i", getBit(i, 3));
	printf("%i", getBit(i, 2));
	printf("%i\n", getBit(i, 0));
	
	printf("Writing to pins 8, 9, 7, 0\n");
	writePin(8, getBit(i, 0));
	writePin(9, getBit(i, 1));
	writePin(7, getBit(i, 2));
	writePin(0, getBit(i, 3));
	
	return 0;
}