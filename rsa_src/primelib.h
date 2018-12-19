/*
 * primelib.h
 * Copyright (C) 2018 hzshang <hzshang15@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PRIMELIB_H
#define PRIMELIB_H
#include <gmpxx.h>

mpz_class get_prime(int bits);
bool is_prime(mpz_class n);

#endif /* !PRIMELIB_H */
