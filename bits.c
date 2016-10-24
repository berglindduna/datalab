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
