#
# Makefile
# hzshang, 2018-11-06 02:54
#
CXXFLAGS= -g -fpic -lgmp -lgmpxx `python2-config --includes` -std=c++11 -lboost_python -lboost_system -I/usr/local/include/boost/python -shared

FILE = rsa.cpp util.cpp primelib.cpp
all:
	g++ $(FILE) $(CXXFLAGS) $(PYTHONI) -o ../rsa.so

