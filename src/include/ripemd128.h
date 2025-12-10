/*
 * Copyright (c) 2025-Present
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause License.
 * See the LICENSE file for details.
 */

/********************************************************************\
 *
 *      FILE:     rmd128.c
 *
 *      CONTENTS: A sample C-implementation of the RIPEMD-128
 *                hash-function. This function is a plug-in substitute
 *                for RIPEMD. A 160-bit hash result is obtained using
 *                RIPEMD-160.
 *      TARGET:   any computer with an ANSI C compiler
 *
 *      AUTHOR:   Antoon Bosselaers, ESAT-COSIC
 *      DATE:     1 March 1996
 *      VERSION:  1.0
 *
 *      Copyright (c) Katholieke Universiteit Leuven
 *      1996, All Rights Reserved
 *
\********************************************************************/

#pragma once
#ifndef RMDsize
#define RMDsize 128
#endif

#ifdef uint8_t
#undef uint8_t
#endif
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/

/* typedef 8, 16 and 32 bit types, resp.  */
/* adapt these, if necessary,
   for your operating system and compiler */
typedef unsigned char byte;   /* unsigned 8-bit type */
typedef unsigned short word;  /* unsigned 16-bit type */
typedef unsigned int dword32; /* unsigned 32-bit type */

/********************************************************************/

/* macro definitions */

/* collect four bytes into one word: */
#define BYTES_TO_DWORD(strptr)                                               \
  (((dword32) * ((strptr) + 3) << 24) | ((dword32) * ((strptr) + 2) << 16) | \
   ((dword32) * ((strptr) + 1) << 8) | ((dword32) * (strptr)))

/* ROL(x, n) cyclically rotates x over n bits to the left */
/* x must be of an unsigned 32 bits type and 0 <= n < 32. */
#define ROL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define xororor(x, y, z) (x ^ y ^ z)
#define xorandxor(x, y, z) (z ^ (x & (y ^ z)))
#define xorornot(x, y, z) (z ^ (x | ~y))
#define xorandxor2(x, y, z) (y ^ (z & (x ^ y)))
#define xorornot2(x, y, z) (x ^ (y | ~z))

#define magicK0 0
#define magicK1 0x5a827999UL
#define magicK2 0x6ed9eba1UL
#define magicK3 0x8f1bbcdcUL
#define magicK4 0xa953fd4eUL
#define magicK5 0x50a28be6UL
#define magicK6 0x5c4dd124UL
#define magicK7 0x6d703ef3UL
#define magicK8 0x7a6d76e9UL
#define magicK9 0

/* the eight basic operations FF() through III() */
#define FFfunc(a, b, c, d, x, s)            \
  {                                     \
    (a) += xororor((b), (c), (d)) + (x) + magicK0; \
    (a) = ROL((a), (s));                \
  }
#define GGfunc(a, b, c, d, x, s)            \
  {                                     \
    (a) += xorandxor((b), (c), (d)) + (x) + magicK1; \
    (a) = ROL((a), (s));                \
  }
#define HHfunc(a, b, c, d, x, s)            \
  {                                     \
    (a) += xorornot((b), (c), (d)) + (x) + magicK2; \
    (a) = ROL((a), (s));                \
  }
#define IIfunc(a, b, c, d, x, s)            \
  {                                     \
    (a) += xorandxor2((b), (c), (d)) + (x) + magicK3; \
    (a) = ROL((a), (s));                \
  }
#define FFFfunc(a, b, c, d, x, s)           \
  {                                     \
    (a) += xororor((b), (c), (d)) + (x) + magicK9; \
    (a) = ROL((a), (s));                \
  }
#define GGGfunc(a, b, c, d, x, s)           \
  {                                     \
    (a) += xorandxor((b), (c), (d)) + (x) + magicK7; \
    (a) = ROL((a), (s));                \
  }
#define HHHfunc(a, b, c, d, x, s)           \
  {                                     \
    (a) += xorornot((b), (c), (d)) + (x) + magicK6; \
    (a) = ROL((a), (s));                \
  }
#define IIIfunc(a, b, c, d, x, s)           \
  {                                     \
    (a) += xorandxor2((b), (c), (d)) + (x) + magicK5; \
    (a) = ROL((a), (s));                \
  }

/********************************************************************/

/* function prototypes */

/*
 *  initializes MDbuffer to "magic constants"
 */
void ripemd128Init(dword32 *digest);

/*
 *  the compression function.
 *  transforms MDbuf using message bytes X[0] through X[15]
 */
void ripemd128compress(dword32 *digest, dword32 *X);

/*
 * ISO7816 message padding
 * return the length after padding, the data will be modified
 */
int ripemd128PaddingISO7816(uint8_t **data, int data_len);

/**
 * simple ripemd128 for string method
 * @param message
 * @param length
 */

byte *ripemd128bytes(uint8_t *message, int length);

/*********************** end of file rmd128.h ***********************/

#ifdef __cplusplus
}
#endif
