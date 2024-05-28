#include "../lib/rldef.h"
#include "../lib/rlbits.h"
#include "../lib/rlstruct.h"
#include "../lib/rlfunc.h"

static flag_t status = 0x00;
const char *VERSION = "1.0.0";

void usage(void)
{
	printf("Run-Length Encoder/decoder (%s): an (semi-)adequate zipper\n", VERSION);
	printf("created by anson <thesearethethingswesaw@gmail.com>\n\n");
	printf("usage:\n\trle (-h / --help)\n\trle --version\n");
	printf("\trle [-dv] <input> [<output>]\n\tcommand-to-stdout | rle [-dv] [<output>]\n\n");

	printf("options:\n\t%12s\t%s\n","-d, --decode","signals RLE to decode the input file");
	printf("\t%12s\t%s\n", "-v, --verbose", "displays verbose and diagnostic info");
	printf("\t%12s\t%s\n", "<input>","a file to gather input from");
	printf("\t%12s\t%s\n", "<output>","a file to put output into\n");

	printf("copyright (c) 2024, see LICENSE for related details\n");
	return;
}

void version(void)
{
	printf("Run-Length Encoder/decoder (%s): an (semi-)adequate zipper\n", VERSION);
	return;
}

int main(int argc, char *argv[])
{
	// We have to get some kind of input
	bool frompipe = !isatty(STDIN_FILENO);
	if(!(frompipe || argc > 1))
	{
		fprintf(stderr, "%s: too few arguments, try \"--help\"\n", argv[0]);
		return -1;
	}

	char infile[namesize] = {0}, outfile[namesize] = {0};
	const char *programname = argv[0];

	// Iterate through all arguments sent, character by character
	int c;
	while(--argc > 0 && (*++argv)[0] != '\0')
	{
		if((*argv)[0] != '-')
		{
			if(outfile[0] != '\0')
			{
				fprintf(stderr, "%s: discarded program input -- \"%s\"\n", programname, *argv);
				continue;
			}

			if(infile[0] == '\0' && !frompipe) strncpy(infile, *argv, namesize - 1);
			else if(outfile[0] == '\0')	   strncpy(outfile, *argv, namesize - 1);
		}

		if((*argv)[0] == '-')
		{
			// If there's another dash, then it's a long option.
			// Move the pointer up 2 places and compare the word itself.
			if((*argv)[1] == '-')
			{
				// Using continue statements here so that the user
				// can use both single character and long options
				// simultaniously, and the loop can test both.
				if(strcmp((*argv) + 2, "help")	  == 0) { usage(); 		   return 0; }
				if(strcmp((*argv) + 2, "version") == 0) { version();		   return 0; }
				if(strcmp((*argv) + 2, "verbose") == 0) { setbit(status, VERBOSE); continue; }
				if(strcmp((*argv) + 2, "decode")  == 0) { setbit(status, DECODE);  continue; }
			}
			while((c = *++argv[0]))
			{
				// Single character option testing here.
				switch(c)
				{
					case 'h': usage(); 		   return 0;
					case 'v': setbit(status, VERBOSE); break;
					case 'd': setbit(status, DECODE);  break;
					// This error flag can either be set by a
					// completely unrelated character inputted,
					// or you managed to put -option instead of
					// --option.
					default :
						  fprintf(stderr, "%s: unknown option. try \"--help\"\n", programname);
						  return -1;
				}
			}

			continue;
		}
	}

	// Determine where to output and where to get our input
	FILE *input =  (frompipe && infile[0] == '\0')  ? stdin  : fopen(infile, "r");
	FILE *output = (outfile[0] == '\0') 		? stdout : fopen(outfile, "a");
	if(input == nullptr || output == nullptr) { perror(programname); return -1; }

	if(test(status, VERBOSE)) printf("%s: %s\n", programname, (input == stdin)   ? "recieved input from pipe" : "recieved input from file");
	if(test(status, VERBOSE)) printf("%s: %s\n", programname, (output == stdout) ? "writing to stdout" 	  : "writing to file");

	// Initialize the RLE object
	rle_t *rleobj = rleinit(input, output);
	if(rleobj == nullptr) { perror(programname); return -1; }

	if(test(status, DECODE)) rle_dec(rleobj);
	else rle_enc(rleobj);

	// And output
	rle_put(rleobj);

	if(test(status, VERBOSE)) printf("%s: rleobj->len reports \"%ld\"\n", programname, rleobj->len);

	// It would be a pretty bad idea to accidentally close standard streams
	rleclean(rleobj);
	return 0;
}
