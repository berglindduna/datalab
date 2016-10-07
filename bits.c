 /* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */
You will provide your solution to the Data Lab by
editing the collection of functions in this source file.
INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;
      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }
  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.
  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.
EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }
  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }
FLOATING POINT CODING RULES
For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.
You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.
NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */
#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}

/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  // x^y is only 0 if x and y have the same bits.
  // !(p) = 0 if p = 0
  // !(p) = 1 otherwise
  return !(x ^ y);
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // x + x + 2 = 0;
  //    if x = Tmax OR if x = -1
  // ~x = 0 only if x = -1

  // temp = 0 if x = Tmax or x = -1
  // otherwise: temp = 1
  int temp = x + x + 2;

  // notX = 0 only if x = -1
  int notX = ~x;

  // !notX = 1 if x != -1
  // !(temp | !notX) = 0 only if x = Tmax
  return !(temp | !notX);
}

/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  // ~x & ~y = ~(x|y)
  int temp = ~x & ~y;
  return ~temp;
}

/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // bytes:    1         2         3         4
  //     n: xxxxxxxx  xxxxxxxx  xxxxxxxx  xxxxxxxx

  // mask = 0000 0000...1111 1111
  int mask = 0xff;

  // move the right byte to the first 8 bits in uf
  int xShift = x >> (n << 3);
  return mask & xShift;
}

/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // mask = 1010 1010 1010 ...
  int mask = (0xaa << 8) + 0xaa;
  mask = (mask << 16 ) + mask;

  // x & temp = temp only if all odd bits in x are 1
  return !((x & mask) ^ mask);
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  // only the last n bits of mask are 0, example:
  // if n = 4:
  //    mask = 0000 1111 1111...
  int mask = ~(((1 << 31) >> n) << 1);
  int xShift = x >> n;

  // returns xShift and the last n bits as 0
  return xShift & mask;
}

/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // last bit of toBig is 1 only if x is to large.
  int toBig = (~x + 0x3a);

  // last bit of toSmall is 1 only  if x is to small.
  int toSmall = (x + ~0x2f);
  return !((toBig | toSmall) >> 31);
}

/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  // -1 = 111111111...
  // 0 = 0000000....
  return ~0;
}

/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  // only the first n bits of mask are 1, example:
  //    if n = 4: 0000 0000... 1111
  int mask = (1 << n) + ~0;

  // xShift = -1 if x < 0
  // xShift = 0 otherwise
  int sign = x >> 31;

  // sign & mask = mask if x < 0
  // sign & mask = 0 otherwise
  int temp = sign & mask;
  return (x + temp) >> n;
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  // return 2*x unless:
  //    x and 2*x have opposite signs, then:
  //            return Tmax if x is positive
  //            return Tmin if x is negative

  // sum = 2*x
  int sum = x << 1;

  // mask = -1 if overflow
  // mask = 0 otherwise
  int mask = (x ^ sum) >> 31;

  // ans = -1 if x is positive
  // ans = 0 if x is negative
  int ans = sum >> 31;
  int Tmin = (1 << 31);

  // ans = Tmax if x is positive
  // ans = Tmin if x is negative
  ans = ans ^ Tmin;

  // if overflow return ans
  // otherwise return sum
  return (sum & ~mask)|(ans & mask);
}

/*
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  // overflow if:
  //    x is positive, y is negative and (x-y) is negative
  //    x is negative, y is positive and (x-y) is positive

  // sum = x - y
  int sum = x + (~y + 1);

  // signs = -1 if x and y have opposite signs
  // signs = 0 otherwise
  int signs = (x ^ y) >> 31;

  // sumSigns = -1 if x and sum have opposite signs
  // sumSigns = 0 otherwise
  int sumSigns = (x ^ sum) >> 31;
  return !(signs & sumSigns);
}

/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  // -uf = uf ^ 1000000000...
  unsigned  neguf = uf ^ 0x80000000;

  // if |x| > 0 11111111 0000000....
  // then x is NaN
  unsigned abs = 0x7fffffff & uf;

  if (abs > 0x7f800000)
        return uf;

  return neguf;
}

/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  // |x| = x & 0 11111111...
  unsigned abs = 0x7fffffff & uf;

  // if |x| > 0 11111111 000000...
  // then x is NaN
  if (abs > 0x7f800000)
        return uf;

  return abs;
}

/*
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  // sign, exp and frac are the sign, exponential and fractional parts of uf
  unsigned maskExpOne = 0x00800000;
  unsigned sign = uf & 0x80000000;
  unsigned exp = uf & 0x7f800000;
  unsigned frac = uf & 0x007fffff;
  unsigned fracShiftOne;
  unsigned round = 0;

  // if the exponential part is all ones ...
  // then uf is NaN or infinity
  if (exp == 0x7f800000)
        return uf;

  // if the exponential part is bigger then 1
  // return uf with 1 added to the exponential part
  else if (exp > maskExpOne)
        return sign | (((exp >> 23) - 1) << 23) | frac;

  // special case: if the exponential part is 1
  // 1 is added behind the fractional number in frac
  else if (exp == maskExpOne)
        frac = frac | maskExpOne;

  fracShiftOne = frac >> 1;

  // if the first two bits of uf are 11 then 1 is addedd to the answer
  if ((frac & 3) == 3)
        round = 1;

  return sign | (fracShiftOne + round);
}

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  // x = 0 if x|-x = 0
  // x|x = 1000 0000... otherwise
  int negx = ~x + 1;

  // isNotZero = 0 if x = 0
  // isNotZero = 1 otherwise
  int isNotZero = ((x | negx) >> 31) & 1;
  return isNotZero ^ 1;
}

