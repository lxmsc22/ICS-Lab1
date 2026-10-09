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
 
  int funct(arg1, arg2, ...) {
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
  1. Integer constants 0 through 255 (0xff), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. function arguments and local variables (no global variables).
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the sgned range retain their low 32 bits.


EXAMPLES Of ACCEPTABLE CODING STYLE:
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

fLOATING POINT CODING RULES

for the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most sgnificant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  // 1<<31 = 0b10000000_00000000_00000000_00000000。
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(x & y) & (~(~x & ~y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  // sgn 为 32 个 0（非负）或 32 个 1（负数）。
  int sgn = x >> 31;
  return (~x + 1) & sgn;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least sgnificant) to 3 (most sgnificant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  src = src << 3;
  dst = dst << 3;
  // 0xff = 0b11111111；移至 dst 后取反，清空目标字节。
  int mask = ~(0xff << dst);
  return (mask & x) | ((x >> src & 0xff) << dst);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  // 最高位掩码参考P1；mask 的低 (32-n) 位为 1，其余位为 0。
  int mask = ~(1<<31 >> n << 1);
  return mask & (x >> n);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int i = 0x0f;
  // mask = 0b00001111_00001111_00001111_00001111。
  int mask = i<<24 | i<<16 | i<<8 | i;

  int l = (mask & x) << 4;
  int h = mask & (x >> 4);
  return h | l;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least sgnificant 0 bit
 *   Examples: secondLowestZeroBit(0xfffffffA) = 0x4, secondLowestZeroBit(0x7fffffff) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  x = (x + 1) | x;
  return (x + 1) ^ (x & (x + 1));
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    
    return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  // 31 = 0b11111；取低 5 位，保证移位量在 0-31 内。
  n = n & 31;
  // m = 31-n；分两次左移，避免 n=0 时出现一次左移 32 位。
  int m = 32 + ~n;

  int mask = ~(1<<31 >> n << 1);
  int l = mask & (x >> n);
  int h = x << m << 1;
  return h | l;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  // ~0 = 0b11111111_11111111_11111111_11111111，即 -1。
  // mid 只有第 (n-1) 位为 1；bias = mid-1+商的奇偶位。
  int mid = 1 << (n + ~0);
  int bias = mid + ((x >> n) & 1) + ~0;
  
  return ((x + bias) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int mid = (x >> 1) + (y >> 1);
  int dsgn = (x >> 31) ^ (y >> 31);

  int g = (dsgn & (y >> 31)) | (~dsgn & ((y + ~x + 1) >> 31));

  int r = ((x & y) | (g & (x ^ y))) & 1;

  return mid + r;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;

  int da = sx ^ sa;
  int db = sx ^ sb;

  int geA = (da & ~sx) | (~da & ~((x + (~a + 1)) >> 31));
  int geB = (db & ~sx) | (~db & ~((x + (~b + 1)) >> 31));

  int eqA = !(x ^ a);
  int eqB = !(x ^ b);

  return ((geA ^ geB) & 1) | eqA | eqB;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x2 = x + x;
  int x4 = x2 + x2;
  int x5 = x4 + x;

  int o = ((x ^ x2) | (x ^ x4) | (x ^ x5)) >> 31;

  // MAX 是饱和值：非负时为 0b01111111_11111111_11111111_11111111，
  // 负数时为 0b10000000_00000000_00000000_00000000。
  int MAX = (1 << 31) + ~(x >> 31);

  return (o & MAX) | (~o & x5);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;
  int pos1 = ((~x & ~y & s1) >> 31) & 1;
  int neg1 = (x & y & ~s1) >> 31;
  int c1 = pos1 + neg1;

  int s2 = s1 + z;
  int pos2 = ((~s1 & ~z & s2) >> 31) & 1;
  int neg2 = (s1 & z & ~s2) >> 31;
  int c2 = pos2 + neg2;

  return c1 + c2;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sgn of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  //almost by ai
  // 0x80000000 = 0b10000000_00000000_00000000_00000000（符号位）。
  // 0xff = 0b11111111（8 位阶码）；0x007fffff 为低 23 位的 1：
  // 0b00000000_01111111_11111111_11111111。
  unsigned sgn = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xff;
  unsigned f = uf & 0x007fffff;

  if (exp == 0xff) return uf;

  if (exp == 0) {
      unsigned tmp = f * 3;
      // 3 = 0b11；低两位为 11 时，除二的中点舍入需要进位。
      unsigned nf = (tmp >> 1) + ((tmp & 3) == 3);
      return sgn | nf;
  }

  // 0x00800000 = 0b00000000_10000000_00000000_00000000（隐含的 1）。
  unsigned M = 0x00800000 | f;
  unsigned tmp = M * 3;

  // 0x02000000 = 0b00000010_00000000_00000000_00000000，即 2^25。
  if (tmp < 0x02000000) {
      unsigned M_new = (tmp >> 1) + ((tmp & 3) == 3);
      return sgn | (exp << 23) | (M_new & 0x007fffff);
  }

  exp = exp + 1;
  if (exp >= 0xff) {
      // 0x7f800000 = 0b01111111_10000000_00000000_00000000（正无穷）。
      return sgn | 0x7f800000;
  }

  int rem = tmp & 3;
  // 4 = 0b100，标记右移两位后保留部分的最低位。
  int round_up = (rem == 3) || (rem == 2 && (tmp & 4));
  unsigned M_new = (tmp >> 2) + round_up;

  return sgn | (exp << 23) | (M_new & 0x007fffff);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sgn; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  //almost by ai
  // 符号、阶码、尾数掩码的二进制形式参考P15。
  unsigned sgn = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xff;
  unsigned f = uf & 0x007fffff;

  // 150 = 0b10010110 = 127+23；126 = 0b01111110 = 127-1。
  if (exp >= 150) return uf;
  if (exp < 126) return sgn;

  if (exp == 126) {
      if (f == 0) return sgn;
      // 127<<23 = 0b00111111_10000000_00000000_00000000，即 +1.0。
      return sgn | (127 << 23);
  }

  int shift = 150 - exp;
  // mask 的低 shift 位全为 1；half 只有第 (shift-1) 位为 1。
  unsigned mask = (1 << shift) - 1;
  unsigned half = 1 << (shift - 1);
  unsigned fp = uf & mask;
  int lsb = (uf >> shift) & 1;

  int round_up = (fp > half) || ((fp == half) && lsb);
  if (round_up) {
      uf = uf + (1 << shift);
  }

  return uf & ~mask;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  //almost by ai
  if (x == 0) return 0;

  unsigned sgn = x & 0x80000000;
  unsigned ux = x;
  if (x < 0) ux = -ux;

  // 158 = 0b10011110 = 127+31，随最高有效位左移而递减。
  int exp = 158;
  while (!(ux & 0x80000000)) {
      ux = ux << 1;
      exp = exp - 1;
  }

  // 0xff = 0b11111111；0x80 = 0b10000000（半程）；
  // 0x100 = 0b1_00000000（保留部分的最低位）。
  unsigned fp = ux & 0xff;
  int round_up = (fp > 0x80) || ((fp == 0x80) && (ux & 0x100));

  unsigned mantissa = (ux >> 8) + round_up;
  // 1<<24 = 0b00000001_00000000_00000000_00000000（尾数进位）。
  if (mantissa & (1 << 24)) {
      exp = exp + 1;
  }

  return sgn | (exp << 23) | (mantissa & 0x007fffff);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8);
  // 扩展后 m1 = 0b01010101_01010101_01010101_01010101。
  m1 = m1 | (m1 << 16); 

  int m2 = 0x33 | (0x33 << 8);
  // 扩展后 m2 = 0b00110011_00110011_00110011_00110011。
  m2 = m2 | (m2 << 16);

  int m4 = 0x0f | (0x0f << 8);
  // 扩展后 m4 = 0b00001111_00001111_00001111_00001111。
  m4 = m4 | (m4 << 16);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;

  x = x + (x >> 8);
  x = x + (x >> 16);

  // 0x3f = 0b00111111，保留可表示计数 0-32 的低 6 位。
  return x & 0x3f;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7fffffff) = 0xfffffffE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  // m16 = 0b00000000_00000000_11111111_11111111。
  int m16 = (0xff << 8) | 0xff;
  // m8  = 0b00000000_11111111_00000000_11111111。
  int m8 = m16 ^ (m16 << 8);
  // m4  = 0b00001111_00001111_00001111_00001111。
  int m4 = m8 ^ (m8 << 4);
  // m2  = 0b00110011_00110011_00110011_00110011。
  int m2 = m4 ^ (m4 << 2);
  // m1  = 0b01010101_01010101_01010101_01010101。
  int m1 = m2 ^ (m2 << 1);

  x = ((x >> 1) & m1) | ((x & m1) << 1);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 8) & m8) | ((x & m8) << 8);
  x = ((x >> 16) & m16) | (x << 16);
  return x;
}
