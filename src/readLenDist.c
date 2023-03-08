#include <stdio.h>
#include <stdlib.h>

// input a fasta file with reads

int main(int argc, char *argv[])
{
	if (argc < 2)
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

	FILE *opf;
	opf = fopen("RLD.txt", "w");
	unsigned long s1;
	unsigned long s2;

	while (!feof(inpf))
	{
		fscanf(inpf, ">%*[^\n]\n");
		s1 = ftell(inpf);
		fscanf(inpf, "%*[^>]"); // this is if it is in single line format
		s2 = ftell(inpf);
		fprintf(opf, "%lu\n", s2 - s1 - 1);
	}

	
	fclose(inpf);
	fclose(opf);
	return(0);	
}