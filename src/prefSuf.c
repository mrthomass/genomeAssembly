#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input fasta read file, output prefixes and suffixes in a special order
char *makeString(int index, char *init, int lenInit);

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		printf("ERROR: COMMAND LINE INPUTS REQUIRED\n");
		printf("./prefSuf readFile.fasta rdl.txt #startVal\n");
		return(1);
	}
	
	FILE *inpf;
	inpf = fopen(argv[1], "r");
	if (inpf == NULL)
	{	
		printf("ERROR: COULD NOT OPEN FILE\n");
		return(2);
	}

	FILE *inpft;
	inpft = fopen(argv[1], "r");
	if (inpft == NULL)
	{
		fclose(inpf);
		return(3); // THIS WOULD BE SOME MEMORY ISSUE
	}
	

	FILE *rdl;
	rdl = fopen(argv[2], "r");
	if (rdl == NULL)
	{
		printf("ERROR: COULD NOT FIND RDL\n");
		return(4);
	}

	// also we need a way to check these are integers
	unsigned int startMer;
	sscanf(argv[3], "%i", &startMer);
	

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

	char *holdPREF;
	char *holdSUFF;
	char *holdPRES;
	char *holdNOT;
	

	FILE *prefix;
	FILE *suffix;
	FILE *notIN;

	for (int i = 0; i < maxRead - startMer; i++)
	{ // for kmer length in the given area

		printf("WORKING ON: KMER = %i\n", i + startMer);

		prefix = fopen(makeString(i, "PREF", 4), "w"); // possible memory breach here ***
		suffix = fopen(makeString(i, "SUFF", 4), "w"); // suffix will start being exactly like the prefix, coming from other file though
		notIN = fopen(makeString(i, "NOT", 3), "w");

		holdPREF = malloc(sizeof(char) * (startMer + i + 1)); // one for the newline

		holdSUFF = malloc(sizeof(char) * (startMer + i + 1));

		while (!feof(inpf))
		{ // practically, for read in given area

			fscanf(inpf, ">%*[^\n]\n");
			fscanf(inpft, ">%*[^\n]\n");
			fscanf(rdl, "%i\n", &holdRlen);

			holdPRES = malloc(sizeof(char) * (holdRlen - startMer - i)); // this is different for each read since they all have different lengths
			// might want to make a certain output for these guys, and we also might want to create file that hold

			if (holdRlen > startMer + i)
			{
				
				// the idea is to read the first non needed part into the holdPRES (presuffix) so the suffix can be perfect
				fread(holdPRES, sizeof(char), (holdRlen - startMer - i), inpft);

				fread(holdPREF, sizeof(char), startMer + i, inpf);
				fread(holdSUFF, sizeof(char), startMer + i, inpft);

				fprintf(prefix, "%s\n", holdPREF);
				fprintf(suffix, "%s\n", holdSUFF);

			}
			else
			{
				holdNOT = malloc(sizeof(char) * (holdRlen + 1));
				fread(holdNOT, sizeof(char), holdRlen, inpf);
				fprintf(notIN, ">\n%s\n", holdNOT);
				free(holdNOT);
			}
			
		
			fscanf(inpf, "%*[^>]");
			fscanf(inpft, "%*[^>]");


			free(holdPRES);
		}




		free(holdPREF);
		free(holdSUFF);

		rewind(inpf);
		rewind(inpft);
		rewind(rdl);
		fclose(prefix);
		fclose(suffix);
		fclose(notIN);
	}


	printf("SUCCESSFULLY COMPLETED STORAGE\n");
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
				output[i] = 48 + index; //starts at 48 because 47 is / (problematic)
			}
			else
			{
				output[i] = suff[i - lenInit - 1];
			}
		}
	}
	return(output);
}