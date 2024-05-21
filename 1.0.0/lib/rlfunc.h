#ifndef rle__rlfunc__h
#define rle__rlfunc__h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
	Run-Length encoding and decoding Functions
	Made by anson in 2024, see LICENSE for related details
*/

#include "rlstruct.h"

bool rle_enc(rle_t *input, const char *filename);
bool rle_dec(rle_t *input, const char *filename);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* rle__rlfunc__h */
