#ifndef rle__rlbits__h
#define rle__rlbits__h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
	Bit setting and
	Made by anson in 2024, see LICENSE for related details
*/

#include "rldef.h"

// We're not using "char", just in case there's some
// dystopian future where they changed the definition
// of "char". Might be just bias, but I put more trust
// in stdint.h's typedefs.
typedef uint8_t flag_t;

// Shorthands for setting bits in a flag typedef
#define setbit(x, y)	((x) |= (y))
#define unsetbit(x, y)	((x) &= (~(y)))

// Shorthand for testing a bit in a flag typedef
// e.g. if(test(status, ANSI)) { /*do ANSI stuff*/ }
#define test(x, y)	(((x) & (y)) != 0)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* rle__rlbits__h */
