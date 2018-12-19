#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 hzshang <hzshang15@gmail.com>
#
# Distributed under terms of the MIT license.

import socket
from struct import pack,unpack

def p8(n):
    return pack("<B",n)

def p16(n):
    return pack("<H",n)

def p32(n):
    return pack("<I",n)

def p64(n):
    return pack("<Q",n)

def u8(s):
    return unpack("<B",s)[0]

def u16(s):
    return unpack("<H",s)[0]

def u32(s):
    return unpack("<I",s)[0]

def u64(s):
    return unpack("<Q",s)[0]

def pack_num(x):
    data='%x'%x
    data=data.rjust((len(data)+1)>>1<<1,'0').decode("hex")
    return data

def unpack_num(x):
    return int(x.encode("hex"),16)

def send(sock,data):
    payload = p64(len(data))+data
    sock.send(payload)

def recv(sock):
    data=sock.recv(8)
    if len(data) != 8:
        return None
    length = u64(data)
    done = 0
    payload=[]
    while done < length:
        tmp=sock.recv(length-done)
        if tmp == '':
            return None
        payload.append(tmp)
        done+=len(tmp)
    ret= "".join(payload)
    return ret



