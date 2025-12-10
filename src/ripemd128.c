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

/*  header files */
#include <stdio.h>
#include <stdlib.h>
#ifdef uint8_t
#undef uint8_t
#endif
#include <stdint.h>
#include <string.h>
#include "include/ripemd128.h"


#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/

void ripemd128Init(dword32 *digest)
{
  digest[0] = 0x67452301UL;
  digest[1] = 0xefcdab89UL;
  digest[2] = 0x98badcfeUL;
  digest[3] = 0x10325476UL;

  return;
}


/********************************************************************/

void ripemd128compress(dword32 *digest, dword32 *X)
{
  dword32 aa,aaa,bb,bbb,cc,ccc,dd,ddd;
  aa = aaa = digest[0];
  bb = bbb = digest[1];
  cc = ccc = digest[2];
  dd = ddd = digest[3];

  /* round 1 */
  FFfunc(aa, bb, cc, dd, X[ 0], 11);
  FFfunc(dd, aa, bb, cc, X[ 1], 14);
  FFfunc(cc, dd, aa, bb, X[ 2], 15);
  FFfunc(bb, cc, dd, aa, X[ 3], 12);
  FFfunc(aa, bb, cc, dd, X[ 4],  5);
  FFfunc(dd, aa, bb, cc, X[ 5],  8);
  FFfunc(cc, dd, aa, bb, X[ 6],  7);
  FFfunc(bb, cc, dd, aa, X[ 7],  9);
  FFfunc(aa, bb, cc, dd, X[ 8], 11);
  FFfunc(dd, aa, bb, cc, X[ 9], 13);
  FFfunc(cc, dd, aa, bb, X[10], 14);
  FFfunc(bb, cc, dd, aa, X[11], 15);
  FFfunc(aa, bb, cc, dd, X[12],  6);
  FFfunc(dd, aa, bb, cc, X[13],  7);
  FFfunc(cc, dd, aa, bb, X[14],  9);
  FFfunc(bb, cc, dd, aa, X[15],  8);

  /* round 2 */
  GGfunc(aa, bb, cc, dd, X[ 7],  7);
  GGfunc(dd, aa, bb, cc, X[ 4],  6);
  GGfunc(cc, dd, aa, bb, X[13],  8);
  GGfunc(bb, cc, dd, aa, X[ 1], 13);
  GGfunc(aa, bb, cc, dd, X[10], 11);
  GGfunc(dd, aa, bb, cc, X[ 6],  9);
  GGfunc(cc, dd, aa, bb, X[15],  7);
  GGfunc(bb, cc, dd, aa, X[ 3], 15);
  GGfunc(aa, bb, cc, dd, X[12],  7);
  GGfunc(dd, aa, bb, cc, X[ 0], 12);
  GGfunc(cc, dd, aa, bb, X[ 9], 15);
  GGfunc(bb, cc, dd, aa, X[ 5],  9);
  GGfunc(aa, bb, cc, dd, X[ 2], 11);
  GGfunc(dd, aa, bb, cc, X[14],  7);
  GGfunc(cc, dd, aa, bb, X[11], 13);
  GGfunc(bb, cc, dd, aa, X[ 8], 12);

  /* round 3 */
  HHfunc(aa, bb, cc, dd, X[ 3], 11);
  HHfunc(dd, aa, bb, cc, X[10], 13);
  HHfunc(cc, dd, aa, bb, X[14],  6);
  HHfunc(bb, cc, dd, aa, X[ 4],  7);
  HHfunc(aa, bb, cc, dd, X[ 9], 14);
  HHfunc(dd, aa, bb, cc, X[15],  9);
  HHfunc(cc, dd, aa, bb, X[ 8], 13);
  HHfunc(bb, cc, dd, aa, X[ 1], 15);
  HHfunc(aa, bb, cc, dd, X[ 2], 14);
  HHfunc(dd, aa, bb, cc, X[ 7],  8);
  HHfunc(cc, dd, aa, bb, X[ 0], 13);
  HHfunc(bb, cc, dd, aa, X[ 6],  6);
  HHfunc(aa, bb, cc, dd, X[13],  5);
  HHfunc(dd, aa, bb, cc, X[11], 12);
  HHfunc(cc, dd, aa, bb, X[ 5],  7);
  HHfunc(bb, cc, dd, aa, X[12],  5);

  /* round 4 */
  IIfunc(aa, bb, cc, dd, X[ 1], 11);
  IIfunc(dd, aa, bb, cc, X[ 9], 12);
  IIfunc(cc, dd, aa, bb, X[11], 14);
  IIfunc(bb, cc, dd, aa, X[10], 15);
  IIfunc(aa, bb, cc, dd, X[ 0], 14);
  IIfunc(dd, aa, bb, cc, X[ 8], 15);
  IIfunc(cc, dd, aa, bb, X[12],  9);
  IIfunc(bb, cc, dd, aa, X[ 4],  8);
  IIfunc(aa, bb, cc, dd, X[13],  9);
  IIfunc(dd, aa, bb, cc, X[ 3], 14);
  IIfunc(cc, dd, aa, bb, X[ 7],  5);
  IIfunc(bb, cc, dd, aa, X[15],  6);
  IIfunc(aa, bb, cc, dd, X[14],  8);
  IIfunc(dd, aa, bb, cc, X[ 5],  6);
  IIfunc(cc, dd, aa, bb, X[ 6],  5);
  IIfunc(bb, cc, dd, aa, X[ 2], 12);

  /* parallel round 1 */
  IIIfunc(aaa, bbb, ccc, ddd, X[ 5],  8);
  IIIfunc(ddd, aaa, bbb, ccc, X[14],  9);
  IIIfunc(ccc, ddd, aaa, bbb, X[ 7],  9);
  IIIfunc(bbb, ccc, ddd, aaa, X[ 0], 11);
  IIIfunc(aaa, bbb, ccc, ddd, X[ 9], 13);
  IIIfunc(ddd, aaa, bbb, ccc, X[ 2], 15);
  IIIfunc(ccc, ddd, aaa, bbb, X[11], 15);
  IIIfunc(bbb, ccc, ddd, aaa, X[ 4],  5);
  IIIfunc(aaa, bbb, ccc, ddd, X[13],  7);
  IIIfunc(ddd, aaa, bbb, ccc, X[ 6],  7);
  IIIfunc(ccc, ddd, aaa, bbb, X[15],  8);
  IIIfunc(bbb, ccc, ddd, aaa, X[ 8], 11);
  IIIfunc(aaa, bbb, ccc, ddd, X[ 1], 14);
  IIIfunc(ddd, aaa, bbb, ccc, X[10], 14);
  IIIfunc(ccc, ddd, aaa, bbb, X[ 3], 12);
  IIIfunc(bbb, ccc, ddd, aaa, X[12],  6);

  /* parallel round 2 */
  HHHfunc(aaa, bbb, ccc, ddd, X[ 6],  9);
  HHHfunc(ddd, aaa, bbb, ccc, X[11], 13);
  HHHfunc(ccc, ddd, aaa, bbb, X[ 3], 15);
  HHHfunc(bbb, ccc, ddd, aaa, X[ 7],  7);
  HHHfunc(aaa, bbb, ccc, ddd, X[ 0], 12);
  HHHfunc(ddd, aaa, bbb, ccc, X[13],  8);
  HHHfunc(ccc, ddd, aaa, bbb, X[ 5],  9);
  HHHfunc(bbb, ccc, ddd, aaa, X[10], 11);
  HHHfunc(aaa, bbb, ccc, ddd, X[14],  7);
  HHHfunc(ddd, aaa, bbb, ccc, X[15],  7);
  HHHfunc(ccc, ddd, aaa, bbb, X[ 8], 12);
  HHHfunc(bbb, ccc, ddd, aaa, X[12],  7);
  HHHfunc(aaa, bbb, ccc, ddd, X[ 4],  6);
  HHHfunc(ddd, aaa, bbb, ccc, X[ 9], 15);
  HHHfunc(ccc, ddd, aaa, bbb, X[ 1], 13);
  HHHfunc(bbb, ccc, ddd, aaa, X[ 2], 11);

  /* parallel round 3 */
  GGGfunc(aaa, bbb, ccc, ddd, X[15],  9);
  GGGfunc(ddd, aaa, bbb, ccc, X[ 5],  7);
  GGGfunc(ccc, ddd, aaa, bbb, X[ 1], 15);
  GGGfunc(bbb, ccc, ddd, aaa, X[ 3], 11);
  GGGfunc(aaa, bbb, ccc, ddd, X[ 7],  8);
  GGGfunc(ddd, aaa, bbb, ccc, X[14],  6);
  GGGfunc(ccc, ddd, aaa, bbb, X[ 6],  6);
  GGGfunc(bbb, ccc, ddd, aaa, X[ 9], 14);
  GGGfunc(aaa, bbb, ccc, ddd, X[11], 12);
  GGGfunc(ddd, aaa, bbb, ccc, X[ 8], 13);
  GGGfunc(ccc, ddd, aaa, bbb, X[12],  5);
  GGGfunc(bbb, ccc, ddd, aaa, X[ 2], 14);
  GGGfunc(aaa, bbb, ccc, ddd, X[10], 13);
  GGGfunc(ddd, aaa, bbb, ccc, X[ 0], 13);
  GGGfunc(ccc, ddd, aaa, bbb, X[ 4],  7);
  GGGfunc(bbb, ccc, ddd, aaa, X[13],  5);

  /* parallel round 4 */
  FFFfunc(aaa, bbb, ccc, ddd, X[ 8], 15);
  FFFfunc(ddd, aaa, bbb, ccc, X[ 6],  5);
  FFFfunc(ccc, ddd, aaa, bbb, X[ 4],  8);
  FFFfunc(bbb, ccc, ddd, aaa, X[ 1], 11);
  FFFfunc(aaa, bbb, ccc, ddd, X[ 3], 14);
  FFFfunc(ddd, aaa, bbb, ccc, X[11], 14);
  FFFfunc(ccc, ddd, aaa, bbb, X[15],  6);
  FFFfunc(bbb, ccc, ddd, aaa, X[ 0], 14);
  FFFfunc(aaa, bbb, ccc, ddd, X[ 5],  6);
  FFFfunc(ddd, aaa, bbb, ccc, X[12],  9);
  FFFfunc(ccc, ddd, aaa, bbb, X[ 2], 12);
  FFFfunc(bbb, ccc, ddd, aaa, X[13],  9);
  FFFfunc(aaa, bbb, ccc, ddd, X[ 9], 12);
  FFFfunc(ddd, aaa, bbb, ccc, X[ 7],  5);
  FFFfunc(ccc, ddd, aaa, bbb, X[10], 15);
  FFFfunc(bbb, ccc, ddd, aaa, X[14],  8);

  /* combine results */
  ddd += cc + digest[1];               /* final result for MDbuf[0] */
  digest[1] = digest[2] + dd + aaa;
  digest[2] = digest[3] + aa + bbb;
  digest[3] = digest[0] + bb + ccc;
  digest[0] = ddd;
}


/********************************************************************/

int ripemd128PaddingISO7816(uint8_t **data, int data_len) {
  // padding ISO7816
  // message += 0x80 += 0x00 * length
  int padding_length = ((data_len % 64) < 56 ? 56 : 120) - data_len % 64;
  //printf("paddinglength: %d\n", padding_length);

  uint8_t* padding = (uint8_t *) calloc((size_t) (padding_length), sizeof(uint8_t));
  padding[0] = 0x80; // 0x80

//	printf("padding:");
//	for(int i =0;i<padding_length;i++)
//	   printf("%d ", padding[i]);
//	printf("\n");

  // 1 byte for 0x80
  uint8_t * new_data = (uint8_t *) calloc((size_t) (padding_length + data_len), sizeof(uint8_t));
  // concat data and padding
  memcpy(new_data, *data, data_len);
  memcpy(new_data + data_len * sizeof(uint8_t), padding, padding_length);

  // add length bits
  // bytes_len concat
  uint32_t bytes_len = (uint32_t) data_len; //u32 -> 4 bytes
  bytes_len = bytes_len << 3;
  // malloc x_data memory
  // x_data = data || padding_data(0x80,0x00...0x00<length>) || length_bits
  uint8_t * length_bits = (uint8_t *)calloc(2* sizeof(uint32_t), sizeof(uint8_t)); // 8bytes data
  // length_bits: [length:\x00\x00\x00\x00]
  length_bits[0] = (uint8_t) bytes_len;
  length_bits[1] = (uint8_t) (bytes_len >> 8);
  length_bits[2] = (uint8_t) (bytes_len >> 16);
  length_bits[3] = (uint8_t) (bytes_len >> 24);

  int xdata_length = padding_length +  data_len + 2 * sizeof(uint32_t) /* 2 * 4 * 8*/;
  uint8_t* x_data = (uint8_t *) calloc((size_t) xdata_length, sizeof(uint8_t));
  memcpy(x_data, new_data, data_len + padding_length);
  // concat length bits
  memcpy(x_data + (data_len + padding_length) * sizeof(uint8_t), length_bits , 2 * sizeof(uint32_t));
//	char* tmpdata = *data;
//	if (*tmpdata) free(*tmpdata);
  if (new_data) free(new_data);
  free(padding);
  free(length_bits);

//	printf("xdata:");
//	for(int i =0;i<xdata_length;i++)
//	   printf("%02x", x_data[i]);
//	printf("\n");

  // little endian to big endian
//	uint32_t testd = x_data[3];
//	testd = testd << 8 | x_data[2];
//
//  testd = testd << 8 | x_data[1];
//  testd = testd << 8 | x_data[0];
//  printf("testd:%u\n" ,testd);

  (*data) = x_data;

  return data_len + padding_length + 2 * sizeof(uint32_t);
}


/*
 * returns ripemd128(message, length)
 * message should be a string terminated by '\0'
 */
byte *ripemd128(const byte *message, int len)
{
   dword32       digest[RMDsize/32];   /* contains (A, B, C, D(, E))   */
   static byte   hashcode[RMDsize/8];  /* for final hash-value         */
   dword32       X[16];                /* current 16-word chunk        */
   word          i;                    /* counter                      */
   dword32       length;               /* length in bytes of message   */
   dword32       nbytes;               /* # of bytes not yet processed */

   /* initialize */
   ripemd128Init(digest);

   length = (dword32) len;

   /* process message in 16-word chunks */
   for (nbytes=length; nbytes > 63; nbytes-=64) {
      for (i=0; i<16; i++) {
         X[i] = BYTES_TO_DWORD(message);
//         printf("%ld ", X[i]);
         message += 4;
      }
//      printf("\nX[i] ");
//      for(int j = 0; j < 16; j++) {
//         printf("%ld ", X[j]);
//      }
//
//      printf("\n");
//      printf("\nMDBUFFER[i] ");
//      for(int j = 0; j < 4; j++) {
//         printf("%lx ", digest[j]);
//      }
//      printf("\n");

      ripemd128compress(digest, X);

// printf("\nMDBuffer: ");
//      for(int j = 0; j < 4; j++) {
//         printf("%lx ", digest[j]);
//      }

   }  /* length mod 64 bytes left */


   /* finish: */
//   MDfinish(MDbuf, message, length, 0);

//   printf("\nMDBuffer: ");
//      for(int j = 0; j < 4; j++) {
//         printf("%lx ", digest[j]);
//      }
//      printf("\n");

   for (i=0; i<RMDsize/8; i+=4) {
      hashcode[i]   = (byte) (digest[i >> 2] & 0x000000ff);         /* implicit cast to byte  */
      hashcode[i+1] = (byte) ((digest[i >> 2] >> 8 ) & 0x000000ff);  /*  extracts the 8 least  */
      hashcode[i+2] = (byte) ((digest[i >> 2] >> 16) & 0x000000ff);  /*  significant bits.     */
      hashcode[i+3] = (byte) ((digest[i >> 2] >> 24) & 0x000000ff);
   }
//   for (i=0; i<RMDsize/8; i+=4) {
//     printf("%02x(%d)",hashcode[i]  ,hashcode[i]);         /* implicit cast to byte  */
//     printf("%02x(%d)",hashcode[i+1],hashcode[i+1]);  /*  extracts the 8 least  */
//     printf("%02x(%d)",hashcode[i+2],hashcode[i+2]);  /*  significant bits.     */
//     printf("%02x(%d)",hashcode[i+3],hashcode[i+3]);
//   }

   return (byte *)hashcode;
}

/********************************************************************/

/********************************************************************/

byte* ripemd128bytes(uint8_t *message, int length)
{
//   int i;
//   printf("\n* message: %s\n  hashcode: ", message);

   int rlen = ripemd128PaddingISO7816(&message, length);
//   printf("\n* padding  length: %d\n  : ", rlen);
//   printf("\n* message  length: %d\n  : ", (int) strlen(message));

   byte* hashcode = ripemd128(message, rlen);

   for (int i=0; i< RMDsize/8 /*ripemd size / 8 = 128 / 8*/; i++) {
     hashcode[i] = (byte)(hashcode[i] & 255);
//     printf("%d ", hashcode[i]);
   }
//   printf("\n");
//   for (i=0; i< RMDsize/8; i++) {
//      printf("%02x ", hashcode[i] );
//   }
   return hashcode;
}



/************************ end of file rmd128.c **********************/

#ifdef __cplusplus
}
#endif
