/*
 * util.h
 * Copyright (C) 2018 hzshang <hzshang15@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef UTIL_H
#define UTIL_H
#include <gmpxx.h>
mpz_class m_gcd( mpz_class op1, mpz_class op2);
mpz_class m_pow(mpz_class x,mpz_class e,mpz_class N);
void extend_gcd(mpz_class x,mpz_class y,mpz_class& s,mpz_class& t,mpz_class& r);
mpz_class invert(mpz_class x, mpz_class N);
mpz_class get_random_r(const mpz_class& begin,const mpz_class& end);
mpz_class get_random(const mpz_class& end);
mpz_class get_random_bits(int bits);

#endif /* !UTIL_H */
