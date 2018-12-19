/*
 * rsa.cpp
 * Copyright (C) 2018 hzshang <hzshang15@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <gmpxx.h>
#include <string>
#include "util.h"
#include "primelib.h"
#include <boost/python.hpp>
#include <boost/python/extract.hpp>

class rsa{
    public:
        rsa(int bits,const mpz_class& e);
        rsa(int bits,const std::string &e);
        rsa(const mpz_class& N,const mpz_class& );
        rsa(const mpz_class &N,const mpz_class& e,const mpz_class &d);
        rsa(const std::string &N,const std::string& );
        rsa(const std::string &N,const std::string&, const std::string&);
        mpz_class _get_public_key();
        mpz_class _get_secret_key();
        mpz_class _get_N();
        mpz_class _encrypt(const mpz_class& pt);
        mpz_class _decrypt(const mpz_class& ct);

        std::string get_N();
        std::string get_public_key();
        std::string get_secret_key();
        std::string encrypt(const std::string &a);
        std::string decrypt(const std::string &a);
        ~rsa();
    private:
        mpz_class e;
        mpz_class d;
        mpz_class N;
};

