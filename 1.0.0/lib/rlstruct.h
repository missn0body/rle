#ifndef rle__rlstruct__h
#define rle__rlstruct__h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
	Run-Length Structures and related functions
	Made by anson in 2024, see LICENSE for related details
*/

#include "rldef.h"

typedef struct length
{
	char *buf;	// Buffer for entire length
	size_t len;	// Length of the entire length, lol
	FILE *in, *out; // Input and output file handles
} rle_t;

rle_t		*rleinit	(FILE *input, FILE *output);
void	 	 rleapp		(rle_t *input, const char *what, size_t len);
void 	 	 rleclean 	(rle_t *input);

inline char 	*rlebuf		(const rle_t *input) { return input->buf; }
inline size_t 	 rlelen		(const rle_t *input) { return input->len; }

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* rle__rlstruct__h */
