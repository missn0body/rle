#include "../lib/rlfunc.h"

bool rle_enc(rle_t *input, const char *filename)
{
	if(input == nullptr || filename == nullptr) return false;

	FILE *fobj = fopen(filename, "r");
	if(fobj == nullptr) return false;

	char line[bufsize] = {0}, append[bufsize] = {0};
	char cur = '\0', next = '\0';
	size_t run = 1, written = 0;

	while(fgets(line, sizeof(line), fobj) != nullptr)
	{
		for(int i = 0; line[i + 1] != '\0'; i++)
		{
			// Get current and next character to compare
			cur = line[i], next = line[i + 1];

			// If we come across any formatting characters, just
			// append them as usual
			if(cur == '\n'  || cur == '\t')  { rleapp(input, &cur, 1);  run = 1; continue; }
			if(next == '\n' || next == '\t') { rleapp(input, &next, 1); run = 1; continue; }

			// Increment the amount of characters we see
			if(cur == next) run++;
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

bool rle_dec(rle_t *input, char *out)
{
	if(input == nullptr || out == nullptr) return false;
	return true;
}
