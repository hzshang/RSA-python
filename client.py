#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 hzshang <hzshang15@gmail.com>
#
# Distributed under terms of the MIT license.

from crypto import RSA,DES
import socket
import sys
from net import send,recv,pack_num,unpack_num
import random
import select

def get_random_str(n):
    return "".join([chr(random.randint(0,0xff)) for _ in range(n)])

def main():
    if len(sys.argv) != 3:
        print "Example: python %s HOST PORT"%sys.argv[0]
        exit(0)

    con = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    con.connect((sys.argv[1],int(sys.argv[2])))
    # recv N,e
    N=unpack_num(recv(con))
    e=unpack_num(recv(con))
    r=RSA(N=N,e=e)
    key=get_random_str(8)
    iv=get_random_str(8)
    des=DES(key,iv)
    # send key,iv
    send(con,pack_num(r.encrypt(unpack_num(key))))
    send(con,pack_num(r.encrypt(unpack_num(iv))))

    socks=[con.fileno(),sys.stdin.fileno()]
    mark = True
    while mark:
        readable,_,error=select.select(socks,[],socks)
        for i in readable:
            if i == con.fileno():
                raw=recv(con)
                if not raw:
                    mark = False
                    break
                data = des.decrypt(raw)
                sys.stdout.write(data)
            elif i == sys.stdin.fileno():
                data = sys.stdin.readline()
                if not data:
                    mark = False
                    break
                send(con,des.encrypt(data))
    con.close()




if __name__ == "__main__":
    main()
