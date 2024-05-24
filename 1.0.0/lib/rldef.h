#ifndef rle__rldef__h
#define rle__rldef__h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
	Definitions used by the various RLE header files
	Made by anson in 2024, see LICENSE for related details
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// Sizes of various char buffers
static constexpr short bufsize  = 256;
static constexpr short namesize = 80;

// Modes of operation for this program
#define DECODE		(1 << 2)
#define VERBOSE		(1 << 3)
#define FROMPIPE	(1 << 4)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* rle__rldef__h */
