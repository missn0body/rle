#include "../lib/rldef.h"
#include "../lib/rlstruct.h"
#include "../lib/rlfunc.h"

int main(int argc, char *argv[])
{
	rle_t *test = rleinit(defpattern);
	if(test == nullptr) { perror(argv[0]); return -1; }

	char mes[] = "hello, world";
	rleapp(test, mes, strlen(mes));
	printf("\"%s\": %ld\n", test->buf, test->len);

	rleclean(test);
	return 0;
}
