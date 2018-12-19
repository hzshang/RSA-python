/*
 * rsa.cpp
 * Copyright (C) 2018 hzshang <hzshang15@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "rsa.h"
#include <cassert>
#include <boost/python.hpp>
#include <boost/python/extract.hpp>

rsa::rsa(int bits,const mpz_class& e){
    this->e=e;
    int half=bits/2;
    mpz_class p=get_prime(half);
    mpz_class q=get_prime(bits-half);
    this->N=p*q;
    mpz_class x=(q-1)*(p-1);
    this->d=invert(e,x);
    // safely release
    p=0;
    q=0;
    x=0;
}

rsa::rsa(int bits,const std::string &tmp_e){
    this->e = mpz_class(tmp_e);
    int half=bits/2;
    mpz_class p=get_prime(half);
    mpz_class q=get_prime(bits-half);
    this->N=p*q;
    mpz_class x=(q-1)*(p-1);
    this->d=invert(e,x);
    // safely release
    p=0;
    q=0;
    x=0;
}

rsa::rsa(const std::string &tmp_N,const std::string& tmp_e){
    this->e = mpz_class(tmp_e);
    this->N = mpz_class(tmp_N);
}

rsa::rsa(const std::string &tmp_N,const std::string& tmp_e,const std::string &tmp_d){
    this->e = mpz_class(tmp_e);
    this->N = mpz_class(tmp_N);
    this->d = mpz_class(tmp_d);
}

rsa::rsa(const mpz_class &N,const mpz_class& e){
    this->e=e;
    this->N=N;
    this->d=0;
}

rsa::rsa(const mpz_class &N,const mpz_class& e,const mpz_class &d){
    this->e=e;
    this->N=N;
    this->d=d;
}

mpz_class rsa::_encrypt(const mpz_class &pt){
    assert(pt < this->N);
    return m_pow(pt,this->e,this->N);
}

mpz_class rsa::_decrypt(const mpz_class &ct){
    assert(ct < this->N);
    assert(d != 0);
    return m_pow(ct,this->d,this->N);
}

rsa::~rsa(){
    // safely release
    this->N=0;
    this->d=0;
    this->e=0;
}

mpz_class rsa::_get_N(){
    return this->N;
}

mpz_class rsa::_get_public_key(){
    return this->e;
}

mpz_class rsa::_get_secret_key(){
    return this->d;
}

std::string rsa::get_N(){
    return this->N.get_str();
}

std::string rsa::get_public_key(){
    return this->e.get_str();
}

std::string rsa::get_secret_key(){
    return this->d.get_str();
}

std::string rsa::encrypt(const std::string &a){
    mpz_class tmp(a);
    mpz_class ret=this->_encrypt(tmp);
    return ret.get_str();
}

std::string rsa::decrypt(const std::string &a){
    mpz_class tmp(a);
    mpz_class ret=this->_decrypt(tmp);
    return ret.get_str();
}

BOOST_PYTHON_MODULE(rsa){
    using namespace boost::python;
    class_<rsa>("rsa",init<int, const std::string& >())
        .def(init<const std::string&,const std::string& >())
        .def(init<const std::string&,const std::string& , const std::string&>())
        .def("encrypt",&rsa::encrypt)
        .def("decrypt",&rsa::decrypt)
        .def("get_N",&rsa::get_N)
        .def("get_public_key",&rsa::get_public_key)
        .def("get_secret_key",&rsa::get_secret_key)
        ;
        
}
