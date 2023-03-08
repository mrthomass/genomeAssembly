#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// this function should be able to preemptivly snp reads depending on the quality scores, individually

// should have a threashold value that cuts bases if they are of bad quality

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("ERROR: INPUT FASTQ FILE REQUIRED AND OUTPUT FASTA\n");
		return(1);
	}
	
	FILE *inpf;
	inpf = fopen(argv[1], "r");
	if (inpf == NULL)
	{
		printf("ERROR: INPUT FILE NOT FOUND\n");
		return(2);
	}
	
	FILE *outf;
	outf = fopen(argv[2], "w");

	unsigned long s1;
	unsigned long s2;

	char *readBuff;


	unsigned int nh = 1;
	while (!feof(inpf))
	{
		fscanf(inpf, "@%*[^\n]\n"); // should be where the reads start
		s1 = ftell(inpf);
		fscanf(inpf, "%*[^+]");
		s2 = ftell(inpf);
		fscanf(inpf, "%*[^\n]\n%*[^\n]\n");

		readBuff = malloc(sizeof(char) * (s2 - s1)); // dont need to add one since it is to the plus sigh.
		fseek(inpf, s1, SEEK_SET);

		fread(readBuff, sizeof(char), (s2 - s1 - 1), inpf);
		fprintf(outf, ">%u\n%s\n", nh, readBuff);
		
		fscanf(inpf, "%*[^+]%*[^\n]\n%*[^\n]\n");
		nh++;
		free(readBuff);
	}

	fclose(inpf);
	fclose(outf);
	return(0);
}