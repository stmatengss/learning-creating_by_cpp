default:main

CXXFLAGS  := -O1 -std=c++11
LDFLAGS := ${LDFLAGS} -lrt -lpthread -lmemcached

main: main.cpp
	g++ -o main main.cpp -lpthread -lmemcached -g
main2: main2.c
	gcc -o main2 main2.c -lpthread -lmemcached -g
