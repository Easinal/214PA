CC = g++
CFLAGS = -O3 -I../c++ -mcx16 -march=native -DCILK -fcilkplus -std=c++17

all:	treap

treap:	treap.cpp
	$(CC) $(CFLAGS) -DNDEBUG treap.cpp -o treap
	
	
clean:
	rm -f treap
