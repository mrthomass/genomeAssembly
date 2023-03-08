#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input fasta read file, output prefixes and suffixes in a special order

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

	// these will be user input
	unsigned int startMer = 150;

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
	
	// actual min and max are minus one
	minRead = minRead - 1;
	maxRead = maxRead - 1;
	// so we will need to do headmers for values between startMer to maxRead

	for (int i = 0; i < maxRead - startMer + 1; i++)
	{
		printf("%i\n", startMer + i);
	}

	return(0);
}