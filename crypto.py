#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 hzshang <hzshang15@gmail.com>
#
# Distributed under terms of the MIT license.
from rsa import rsa
from des import encrypt_des,decrypt_des

class RSA(rsa):
    def __init__(self,bits=0,N=None,e=65537,d=None):
        if N == None:
            super(RSA,self).__init__(bits,str(e))
        elif d == None:
            super(RSA,self).__init__(str(N),str(e))
        else:
            super(RSA,self).__init__(str(N),str(e),str(d))
    
    def encrypt(self,pt):
        return int(super(RSA,self).encrypt(str(pt)))
    
    def decrypt(self,ct):
        return int(super(RSA,self).decrypt(str(ct)))

    @property
    def N(self):
        return int(self.get_N())
    @property
    def e(self):
        return int(self.get_public_key())
    @property
    def d(self):
        return int(self.get_secret_key())

class DES():
    def __init__(self,key,iv):
        self.iv = iv
        self.key = key

    def encrypt(self,pt):
        return encrypt_des(pt,self.key,iv=self.iv)

    def decrypt(self,ct):
        return decrypt_des(ct,self.key,iv=self.iv)

