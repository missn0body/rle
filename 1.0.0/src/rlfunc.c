#include "../lib/rlfunc.h"

bool rle_enc(rle_t *input, const char *filename)
{
	// (user's) Sanity check
	if(input == nullptr || filename == nullptr) return false;

	FILE *fobj = fopen(filename, "r");
	if(fobj == nullptr) return false;

	char line[bufsize] = {0}, append[bufsize] = {0};
	char cur = '\0', next = '\0';
	size_t run = 1, written = 0;

	while(fgets(line, sizeof(line), fobj) != nullptr)
	{
		for(int i = 0; line[i] != '\0'; i++)
		{
			// Get current and next character to compare
			cur = line[i], next = line[i + 1];

			// If we come across any formatting characters, just
			// append them as usual
			if(cur == '\n' || cur == '\t') { rleapp(input, &cur, 1); run = 1; continue; }

			// Decoding RLE is a bit tricky without escape characters to inflate
			// the size. Instead, we only append single digit runs, so that a run
			// of 'wwwwwwwwwww' wouldn't convert into '12w', but rather '9w3w', which
			// is only an 1 byte increase
			// TODO: maybe regex will work better?
			if(run == 9)
			{
				written = snprintf(append, bufsize, "%ld%c", run, cur);
				rleapp(input, append, written);
				run = 1;
			}
			// Increment the amount of characters we see
			else if(cur == next) run++;
			// Prevent ourselves from inflating the input size, and ensuring that
			// our output is always going to be smaller
			else if(cur != next && run == 1) { rleapp(input, &cur, 1); continue; }
			else if(cur != next && run != 1)
			{
				// The printf family saves the amount of bytes written
				written = snprintf(append, bufsize, "%ld%c", run, cur);
				rleapp(input, append, written);
				run = 1;
			}

		}
	}

	fclose(fobj);
	return true;
}

bool rle_dec(rle_t *input, const char *filename)
{
	// (user's) Sanity check
	if(input == nullptr || filename == nullptr) return false;

	FILE *fobj = fopen(filename, "r");
	if(fobj == nullptr) return false;

	char line[bufsize] = {0};
	char cur = '\0', next = '\0';

	while(fgets(line, sizeof(line), fobj) != nullptr)
	{
		for(int i = 0; line[i] != '\0'; i++)
		{
			// Grab the current and next character
			cur = line[i], next = line[i + 1];

			// If we come across any formatting
			// characters, just append them as usual
			if(cur == '\n' || cur == '\t') { rleapp(input, &cur, 1); continue; }

			if(!isdigit(cur)) rleapp(input, &cur, 1);
			// If the first character is a digit,
			// and the next a character, then loop
			else if(isdigit(cur) && (cur - '0') >= 2 && !isspace(next))
			{
				for(short i = 0; i < (cur - '0'); i++)
					rleapp(input, &next, 1);

				// Each compressed run is a digit and a character.
				// Since we're done with the uncompressing and
				// looking ahead, skip over the next character
				i++;
			}
		}
	}

	fclose(fobj);
	return true;
}
