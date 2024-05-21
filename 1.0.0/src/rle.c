#include "../lib/rldef.h"
#include "../lib/rlstruct.h"
#include "../lib/rlfunc.h"

int main(int argc, char *argv[])
{
	rle_t *robj = rleinit();
	if(robj == nullptr) { perror(argv[0]); return -1; }

	if(argv[1] != nullptr)
	{
		if(rle_dec(robj, argv[1]) == false)
		{
			perror(argv[0]);
			return -1;
		}
	}
	else rleapp(robj, "Hello, world", 13);
	printf("%s\n%ld\n", rlebuf(robj), rlelen(robj));

	rleclean(robj);
	return 0;
}
