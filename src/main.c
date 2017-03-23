#include <stdlib.h>
#include <stdio.h>
#include "max_finder.h"
#include "barrier.h"


int main(int argc, char *argv[])
{
	// argc should be two, argv[0] is the program name, argv[1] is the text file
	// input sanitization
	if(argc > 2 || argc == 1)
	{
		printf("ERROR: too many or too few command line params passed\n");
		return 0;
	}

	FILE * file;
	// printf("program name: %s\n", argv[0]);
	// printf("File name received: %s\n", argv[1]);	
													
	file = fopen(argv[1], "r");
	if (file == 0)										
	{
		printf("ERROR: could not open text file\n");
		return 0;
	}
	// count how many numbers there are in the file

	int c;
	int numCount = 0;
	while((c = getc(file)) != EOF)
	{
		if(c == 32) ++numCount;
	}
	// total number of ints will be number of psaces + 1
	++numCount;
	printf("number of ints counted: %d\n", numCount);

	rewind(file);

	char num;
	int *nums;
	for(int i = 0; i < numCount; ++i)
	{
		if(fscanf(file, "%s", &num) != 1)
		{
			printf("ERROR: integers not properly being palced in to array\n");
			return 0;
		}
		else
		{
			nums[i] = atoi(&num);
		}
	}
	/*
	while (fscanf(file, "%s", c))
	{
		if(feof(file))
		{

		}
		int num = atoi(&c);
		printf("%d\n", c);
		nums[i] = num;
		++i;
	}
	*/
	for(int i = 0; i < numCount; ++i)
	{
		printf("%d\n", nums[i]);
	}

	fclose(file);
	return 0;
}