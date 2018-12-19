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
import select

def main():
    if len(sys.argv) != 3:
        print "Example: python %s HOST PORT"%sys.argv[0]
        exit(0)
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((sys.argv[1],int(sys.argv[2])))
    server.listen(1)
    con,addr = server.accept()
    server.close()
    #send N,e
    r=RSA(128)
    send(con,pack_num(r.N))
    send(con,pack_num(r.e))
    # recv des key,iv
    key=pack_num(r.decrypt(unpack_num(recv(con))))
    iv=pack_num(r.decrypt(unpack_num(recv(con))))
    des=DES(key,iv)

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





