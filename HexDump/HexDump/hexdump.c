//hexdump.c
//Charlie Ang
//CSC 3350 Spring 2016
//April 4, 2016
//Lab 1 HEX File Dump
//This program opens and reads in a file and prints out a hexadecimal representation 
//of the input file contents where each line of the output displays the offset poisiton
//in the file of the first byte on that line, the hex values for the next 16 bytes in the file,
//and the normal ASCII character representation for those 16 bytes.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function prototypes
int lowNibble(char ch);
int highNibble(char ch);
char hexOutput(int nibble);
void printHex(char ch);
void printAddress(int byteOffset);
void printCharCountHex(int count);

int main(int argc, char *argv[])
{
	FILE *filein;
	int i;
	char ch = "";	//char inputs
	char buff[17];	//for reading 16 bytes from each line
	int chCount = 0;	//keeping track of total number of characters 
	int byteOffset = 0;	//for address of first byte on that line

	for (i = 1; i < argc; i++)	//Find first filename on line.....
	{
		if (_stricmp(argv[i], "/?") == 0)	//Help message request switch 
		{
			printf("This program opens and reads in a file and performs a hex dump.");
			return 0;	//exit code 
		}
		else
		{
			if (freopen_s(&filein, argv[i], "rb", stdin) == 0)	//rb for reading in binary mode 
			{
				printf("\nHEX FILE DISPLAY of %s 	Written by Charlie Ang\n", argv[i]);
				printf("		HEX	FILE	DISPLAY\n");
				break;
			}
			printf("Error: Invalid filename %s\n", argv[i]);
		}
	}

	printf("    Addr:  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  ------ASCII-----\n");
	
	while (ch != EOF)	//while the EOF is not reached
	{
		int j;
		int spaces = 0;	//for appending space after EOF
		int k;
		byteOffset = chCount;	//equals to first byte of that line

		//printf("%08X: ", byteOffset);	//print out address offset
		printAddress(byteOffset);	//call printAdrdress function to print out the 8 nibbles
	
		for (j = 0; j < 16; j++)
		{
			ch = getchar();	//get character
			if (ch != EOF)
			{
				chCount++;	//increment character count
				//printf("%02X ", ch);	//output hex
				printHex(ch);	//call printHex function to output character values in hex 

				if (ch < 32 || ch > 127)	//printing characters are in the range of 32 - 127
				{
					ch = ' ';	
				}
				buff[j] = ch;	//insert char into buffer for ASCII printout 
				buff[16] = 0;	//append null byte to end of buffer 17 - 1 or max - 1
			}

			if (ch == EOF)	//output spaces if EOF reached
			{
				spaces = 16 - j;	//determine how many spaces of the 16 are leftover 
				for (k = 1; k <= spaces; k++)
				{
					printf("   ");	//fill up remaining hex location with spaces
				}
				buff[j] = 0;	//append null byte 
				break;	//exit out of for loop
			}
		}
		printf(" %s\n", buff);	//print out ASCII
	}

	printf("Final character count = %d  ", chCount);	//outputs character count
	printCharCountHex(chCount);	//prints character count in hex 

	fclose(filein);	//close file

	return 0;
}

//This function takes in a character and returns the low nibble of the character.
int lowNibble(char ch)
{
	char lowNibble;
	lowNibble = ch & 0x0F;	//0x0F is the mask. Uses bitwise &
	return lowNibble;
}

//This function takes in a character and returns the high nibble of the character.
int highNibble(char ch)
{
	char highNibble;
	highNibble = (ch >> 4) & 0x0F;	//right shift 4 bits to get upper nibble
	return highNibble;
}

//This function takes in an int as a parameter and converts it into hex (0-15) output char.
//It then returns the hex character.
char hexchar = 'A';	//initialize hexChar to something...will update in function
char hexOutput(int nibble)
{
	if (nibble >= 0 && nibble <= 9)	//if nibble is (0-9)
	{
		hexchar = nibble + '0';
	}
	if (nibble >= 10 && nibble <= 15)	//if nibble is (10-15)
	{
		hexchar = (nibble - 10) + 'A';
	}
	return hexchar;
}

//This function takes in a character and prints it in a hex output.
void printHex(char ch)
{
	int lowNib = lowNibble(ch);	//get int for lowNibble
	int highNib = highNibble(ch);	//get int for highNibble
	char highNibChar = hexOutput(highNib);	//convert highNibble int into hex char
	char lowNibChar = hexOutput(lowNib);	//convert lowNibble int into hex char
	printf("%c%c ", highNibChar, lowNibChar);	//print out highNibble char and lowNibble char 
}

//This function takes in an integer for byte offset and prints out the address (byte offset) in hex. 
void printAddress(int byteOffset)
{
	char address[9];	//for 8 nibbles of address plus room for null

	int lowNib = lowNibble(byteOffset);
	char lowNibChar = hexOutput(lowNib);
	address[7] = lowNibChar;	//store hex low nib in array

	for (int i = 0; i < 7; i++)	//7 high nibbles 
	{
		byteOffset = (byteOffset >> 4);	//right shift 4 bits
		int highNib = lowNibble(byteOffset);	//use lowNibble function to retrieve int
		char highNibChar = hexOutput(highNib);
		address[7 - (i + 1)] = highNibChar;
	}
	address[8] = 0;	//append null byte
	printf("%s: ", address);
}
 
//This function takes in an integer for count and prints out the count in hex. 
void printCharCountHex(int count)
{
	char address[9];	//for 8 nibbles of address plus room for null

	int lowNib = lowNibble(count);
	char lowNibChar = hexOutput(lowNib);
	address[7] = lowNibChar;	//store hex low nib in array

	for (int i = 0; i < 7; i++)	//7 high nibbles 
	{
		count = (count >> 4);	//right shift 4 bits
		int highNib = lowNibble(count);	//use lowNibble function to retrieve int
		char highNibChar = hexOutput(highNib);
		address[7 - (i + 1)] = highNibChar;
	}
	address[8] = 0;	//append null byte
	printf("(0x%s)", address);
}