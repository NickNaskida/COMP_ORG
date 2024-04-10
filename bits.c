/* 
 * CS:APP Data Lab 
 * 
 * Nikoloz Naskidashvili
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


/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}

// 6 - 0110   ~6 - 1001
// 5 - 0101   ~5 - 1010
// & - 0100   |  - 1011  ~\ - valid answer

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678, 1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int mask = 0x000000FF;

  int tmp1 = x >> (n << 3);  // n << 3 == 2^3 == 8 (multiply by eight)

  return tmp1 & mask;
}

// Shift left multiplaction by 2^n powers | Shift right division by 2^n powers

// 1 byte - 8 bits
// 0x 12 34 56 78    0001 0010 0011 0100  0101 0110  0111 1000
//     3  2  1  0
//    00 00 00 FF    0000 0000 0000 0000  0000 0000  1111 1111


/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int mask = ((1 << 31) >> n) << 1;
  return (x >> n) & ~mask;
}

//      1000 0111 0110 0101 0100 0011 0010 0001 
// >> 4
// 1111 1000 0111 0110 0101 0100 0011 0010
// Shifting hex by 1 == shift by 4
// 1 / 4 ratio !!!!! 
// right shift may add sign bit at the start and mess up my code :// 

// (1 << 31) >> n)
// e.g. n=4 => (1 << 31) >> r => 1111 0000 0000 .... 0000

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int result = 0;
  int mask = 0x55 | 0x55 << 8;
  mask = mask | (mask << 16); // mask = 0101
  result = x & mask;
  x = x >> 1;
  result = result + (x & mask);

  mask = 0x33 | 0x33 << 8;
  mask = mask | (mask << 16); // mask = 0x33333333
  result = ((result >> 2) & mask) + (result & mask);

  mask = 0x0F | 0x0F << 8;
  mask = mask | (mask << 16); // mask = 0x0f0f0f0f
  result = ((result >> 4) & mask) + (result & mask);

  mask = 0xFF | 0xFF << 16;
  result = ((result >> 8) & mask) + (result & mask);

  mask = 0xFF | 0xFF << 8;
  result = ((result >> 16) & mask) + (result & mask);

  return result;
}

// ^^^ https://www.youtube.com/watch?v=0rdRRURz6IQ - Too hard :D

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int sign = x >> 31;              // 0 or 1
  int comp2sign = (~x + 1) >> 31;  // 1 or 0

  
  return (sign | comp2sign) + 1;
}


/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x1 << 31; // 0000 ... 0001 << 31 --> 1000 ... 0000
}


/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int m = n + ~0x0;  // Same as n-1
  
  int sign = ( x >> 31 ) & 0x1;  // get sign

  // second, convert the sign into a "mask" (all bits either 0 or 1)
  int mask = ~(sign + ~0); 

  // then xor with x, all leading bits will go away 
  x = x ^ mask;

  // now shift right n - 1 times
  x = x >> m;

  // the result will be zero unless we can't fitbits
  return !x;
}

// First (32 - n) + 1 bits will should identical. Then it fits


/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int isNeg = x >> 31;
  int sign = (isNeg & 0x1); // Extract sign
  int validX = (sign << n) + isNeg; // So here, if the sign is negative we shift 1 (sign) by k to left and
                                    // we add isNeg which is -1 (1111) obtained from right shifting negative integer
                                    // otherwise we just do all the operations on 0 which doesn't change anything
                                    // and we get x + 0 = x
  return (x + validX) >> n;
}

//  x/y  =  (x + y − 1)/y 
// (x<0 ? x+(1<<k)-1 : x) >> k

// Isolate (1 << k) - 1  because this part changes x. I don't need to change it if x > 0. 
// Somehow need to make it 0


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

// expressions -x and ~x + 1 give identical results.


/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int mask = 0x1;
  return !((x >> 31) & mask) & !!x;  // !! same as != 0
}

// 0000 .... 0001
// 1111 .... 

// !x -> zero -> 1 | non zero -> 0 
// !!x -> convert back  => 1 -> zero, zero -> 1


/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int diff = y + (~x + 1);  // (~x + 1) is same as -x as I already showed in negate func above

  int signBit = !((diff >> 31) & 0x1); // 0 or 1 (1 - neg, 0 - pos) and apply not to flip
  return signBit;
}

// y - x >= 0


/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int count = 0;
  count = (!!(x >> 16)) << 4;
  count = count + ((!!(x >> (8 + count))) << 3);
  count = count + ((!!(x >> (4 + count))) << 2);
  count = count + ((!!(x >> (2 + count))) << 1);
  count = count + ((!!(x >> (1 + count))) << 0);

  return count;
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
  unsigned expo = (uf >> 23) & 0xFF;  // shit the mantissa and get expo
  unsigned fracc = uf << 9; // shift away sign and expo bits (1 & 8)
  if(expo == 0xFF && fracc != 0x00) {
    return uf;
  }
  return uf ^ (1<<31); // negate 1000 0000 .... 0000
}


/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned ans;
  int tmpx = x;
  int f = 0;
  int delta = 0;
  int tail = 0;
  int E = 0;

  // handle edge cases
  if (x == 0)
    return x;

  if (x == 0x80000000)
    return 0xcf000000;

  ans = x & 0x80000000; // fixed first place, symbol bit

  if (ans)
    tmpx = -x; // If x is a negative number, then tempx takes the opposite number of x (positive)
  
  // In order to construct a small number segment, we first give up 1, and then add 0 on the tail until 23 digits.
  while ((tmpx >> E))  // Calculate how many digits of tmpx are there in total?
    E++;
    
  E = E - 1;

  // Take 12345 as an example, the binary expression now is 11000000111001, E=13,
  tmpx = tmpx << (31 - E); // Then tmpx moves 18 bits to the left, now tmpx has a total of 31 bits
  
  //tmpx = 11000000111001 000000000000000000
  tail = (tmpx >> 8) & 0x007FFFFF; // Move tmpx to the right by 8 bits, give the order code a space, and now tail is
  
  //10000001110010000000000
  f = tmpx & 0xff;
  
  // round to an even number
  delta = (f > 128) || ((f == 128) && (tail & 1));
  tail += delta;

  E = E + 127; // Calculate the order code, E=e+ offset
    
    // If the frac segment is greater than 23 bits, then add a 1 to the exp segment, which means entering one bit and leaving the highest bit at the same time.
  if (tail >> 23)
  {
    tail = tail & 0x007FFFF;
    E += 1;
  }
  ans = ans | E << 23 | tail; // Merge these three paragraphs to get the final answer
  
  return ans;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // Extract sign (1 bit) exp (8 bit) mantissa (23 bit)
  int signMask = uf & 0x80000000;
  int expMask = uf & 0x7f800000;
  int matMask = uf & 0x007fffff;

  int exp_infty = 0xff000000;
  int tempuf = uf << 1;
  int ans = uf;

  if((tempuf & exp_infty) == exp_infty) // Get rid of NaN -_-
    return uf;

	// If the exp section is not 0, then add 1 to the exp paragraph.
  if(expMask !=0)
    ans = signMask + matMask + expMask + 0x00800000;

  // If the exp paragraph is 0, it means that it is denormalized. We only need to move the Mmask one digit to the left.
  // Move left same as 
  else if(matMask != 0)
    ans = signMask + expMask + (matMask << 1);

  return ans;
}
