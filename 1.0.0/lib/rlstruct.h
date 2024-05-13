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
	char *format;	// Format of the buffer as a regex string, like "\d+\w{1}"
	size_t len;	// Length of the entire length, lol
	regex_t regobj;	// Regex object holding the format
} rle_t;

rle_t 	*rleinit 	(const char *format);
void	 rleapp		(rle_t *input, const char *what, size_t len);
void 	 rleclean	(rle_t *input);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* rle__rlstruct__h */
