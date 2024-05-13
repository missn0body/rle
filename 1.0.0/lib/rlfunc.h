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

void rle_enc(rle_t *input);
void rle_dec(rle_t *input);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* rle__rlfunc__h */
