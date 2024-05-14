#include "../lib/rlstruct.h"

rle_t *rleinit(const char *format)
{
	if(format == nullptr) return nullptr;

	// Allocation of the main structure is tested
	// on its own, since we can't access the elements
	// if it wasn't allocated
	rle_t *newone  = malloc(sizeof(struct length));
	if(newone == nullptr) return nullptr;

	newone->format = malloc(patsize);
	if(newone->format == nullptr) return nullptr;

	// Reserving one byte for the null terminator
	newone->len = 0;
	strncpy(newone->format, format, patsize - 1);
	newone->format[patsize - 1] = '\0';

	// Capture the return value of regcomp to test
	short ret = regcomp(&newone->regobj, newone->format, REG_ICASE | REG_EXTENDED);
	if(ret) return nullptr;
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
	free(input->format);
	regfree(&input->regobj);
	free(input);
	return;
}
