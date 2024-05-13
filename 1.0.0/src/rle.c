#include "../lib/rldef.h"
#include "../lib/rlstruct.h"
#include "../lib/rlfunc.h"

int main(int argc, char *argv[])
{
	rle_t *test = rleinit(defpattern);

	printf("hello world!\n");

	rleclean(test);
	return 0;
}
