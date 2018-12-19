/*
 * primelib.cpp
 * Copyright (C) 2018 hzshang <hzshang15@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <gmpxx.h>
#include "primelib.h"
#include "util.h"

bool is_prime(mpz_class n){
    // use miller-rabin method
    if (n%2 == 0){
        return false;
    }
#define TIME 64
    mpz_class m=n-1;
    int k=0;
    while( m%2 != 0){
        m=m/2;
        k++;
    }
    for(int i=0;i<TIME;i++){
        mpz_class a=get_random_r(2,n-2);
        mpz_class b=m_pow(a,m,n);
        if(b == 1 || b == n-1)
            continue;
        mpz_class tmp=b;
        int flag=0;
        for(mpz_class j=0;i<k-1;j++){
            tmp=(b*b)%n;
            if( tmp == 1 )
                return false;
            if( tmp == n-1)
                flag = 1;
                break;
            b=tmp;
        }
        if (flag == 0){
            return false;
        }
    }
    return true;
}

mpz_class get_prime(int bits){
    mpz_class p=get_random_bits(bits);
    while(!is_prime(p))
        p++;
    return p;
}
