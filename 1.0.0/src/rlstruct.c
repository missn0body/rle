#include "../lib/rlstruct.h"

rle_t *rleinit(const char *format)
{
	if(format == nullptr) return nullptr;

	rle_t *newone  = malloc(sizeof(struct length));
	newone->buf    = malloc(bufsize);
	newone->format = malloc(patsize);

	if(newone == nullptr) return nullptr;
	if(newone->buf == nullptr || newone->format == nullptr) return nullptr;

	newone->len = 0;
	strncpy(newone->format, format, patsize - 1);
	newone->format[patsize - 1] = '\0';

	short ret = regcomp(&newone->regobj, newone->format, REG_ICASE | REG_EXTENDED);
	if(ret) return nullptr;
	return newone;
}

void rleclean(rle_t *input)
{
	free(input->buf);
	free(input->format);
	regfree(&input->regobj);
	free(input);
	return;
}
