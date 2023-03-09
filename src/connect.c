#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("ERROR: NEED LINK FILE\n");
		return(1);
	}
	
	FILE *linkf;
	linkf = fopen(argv[1], "r");
	if (linkf == NULL)
	{
		printf("ERROR: COULD NOT OPEN LINK FILE\n");
		return(2);
	}

	unsigned int FROM;

	fscanf(linkf, "%u%*[^\n]\n", &FROM); 

	unsigned int maximum = FROM;
	unsigned int minimum = FROM;

	unsigned int len = 1;

	while (!feof(linkf))
	{
		fscanf(linkf, "%u%*[^\n]\n", &FROM); 
		if (FROM > maximum)
		{
			maximum = FROM;
		}
		if (FROM < minimum)
		{
			minimum = FROM;
		}
		len++;
	}

	rewind(linkf);

	// make the hash table with this information, if you get to zero you need to quit the loop
	unsigned int *hash = calloc((maximum - minimum + 2), sizeof(unsigned int)); // plus two for difference plus zero
	
	for (int i = 0; i < len; i++)
	{
		
	}
	

	fclose(linkf);
}