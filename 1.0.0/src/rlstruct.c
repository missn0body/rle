#include "../lib/rlstruct.h"

rle_t *rleinit(FILE *input, FILE *output)
{
	rle_t *newone = malloc(sizeof(struct length));
	if(newone == nullptr) return nullptr;

	// If for whatever reason you want to specify
	// null pointers for the arguments, then let's
	// just assume standard streams
	newone->in  = (input == nullptr)  ? stdin  : input;
	newone->out = (output == nullptr) ? stdout : output;

	// Allocation of the internal buffer isn't too
	// necessary, since rleapp() allocates the buffer
	// if it isn't already
	// Though it generally isn't recommended to access
	// the buf at this point
	return newone;
}

void rleapp(rle_t *input, const char *what, size_t len)
{
	// Make a new chunk of memory to reassign the main buffer
	char *newapp = realloc(input->buf, input->len + len);
	if(newapp == nullptr) return;

	// Copy whatever we want to copy over to the chunk
	// and then reassign the buffer, incrementing size
	memcpy(&newapp[input->len], what, len);
	input->buf = newapp;
	input->len += len;
	return;
}

void rleclean(rle_t *input)
{
	// Like a nesting doll, just to be safe
	free(input->buf);

	if(input->in  != stdin) fclose(input->in);
	if(input->out != stdin) fclose(input->out);

	free(input);
	return;
}
