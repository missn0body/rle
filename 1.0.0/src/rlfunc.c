#include "../lib/rlfunc.h"

bool rle_enc(rle_t *input, const char *filename)
{
	if(input == nullptr || filename == nullptr) return false;

	FILE *fobj = fopen(filename, "r");
	if(fobj == nullptr) return false;

	char tmp[bufsize] = {0};
	while(fgets(tmp, sizeof(tmp), fobj) != nullptr)
	{
		size_t tmplen = strlen(tmp);
		rleapp(input, tmp, tmplen);
	}

	fclose(fobj);
	return true;
}

bool rle_dec(rle_t *input, char *out)
{
	if(input == nullptr || out == nullptr) return false;
	return true;
}
