#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input fasta read file, output prefixes and suffixes in a special order
char *makeString(int index, char *init, int lenInit);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("ERROR: COMMAND LINE INPUTS REQUIRED\n");
		return(1);
	}
	
	FILE *inpf;
	inpf = fopen(argv[1], "r");
	if (inpf == NULL)
	{	
		printf("ERROR: COULD NOT OPEN FILE\n");
		return(2);
	}	

	FILE *rdl;
	rdl = fopen(argv[2], "r");
	if (rdl == NULL)
	{
		printf("ERROR: COULD NOT FIND RDL\n");
		return(3);
	}

	// these will be user input
	unsigned int startMer = 50;

	// find the longest read (these are supposed to be accurate reads
	unsigned long s1;
	unsigned long s2;
	unsigned long maxRead;
	unsigned long minRead;
	
	fscanf(inpf, ">%*[^\n]\n");
	s1 = ftell(inpf);
	fscanf(inpf, "%*[^>]"); // this is if it is in single line format
	s2 = ftell(inpf);
	maxRead = s2 - s1;
	minRead = s2 - s1;
	
	while (!feof(inpf))
	{
		fscanf(inpf, ">%*[^\n]\n");
		s1 = ftell(inpf);
		fscanf(inpf, "%*[^>]"); // this is if it is in single line format
		s2 = ftell(inpf);

		if (s2 - s1 > maxRead)
		{
			maxRead = s2 - s1;	
		}
		if (s2 - s1 < minRead)
		{
			minRead = s2 - s1;
		}
	}
	rewind(inpf);
	minRead = minRead - 1;
	maxRead = maxRead - 1;

	// this is where you run the two files parallelly
	int holdRlen;
	char holdBuff;
	

	FILE *prefix;

	// this part gets all the prefixes
	for (int i = 0; i < maxRead - startMer; i++)
	{

		prefix = fopen(makeString(i, "PREF", 4), "w"); // this file holds all the prefixes

		while (!feof(inpf))
		{
			fscanf(inpf, ">%*[^\n]\n");
			fscanf(rdl, "%i\n", &holdRlen);

			if (holdRlen > startMer + i)
			{
				for (int k = 0; k < startMer + i; k++)
				{
					fscanf(inpf, "%c", &holdBuff);
					fprintf(prefix, "%c", holdBuff);
				}
				fprintf(prefix, "\n");
			}
			fscanf(inpf, "%*[^>]");
		}
		
		rewind(inpf);
		rewind(rdl);
		fclose(prefix);
	}


	return(0);
}


char *makeString(int index, char *init, int lenInit)
{
	char *output = malloc(sizeof(char) * (lenInit + 6));
	char *suff = ".txt";
	for (int i = 0; i < lenInit + 6; i++)
	{
		if (i < lenInit)
		{
			output[i] = init[i];
		}
		else
		{
			if (i == lenInit)
			{
				output[i] = 33 + index;
			}
			else
			{
				output[i] = suff[i - lenInit - 1];
			}
		}
	}
	return(output);
}