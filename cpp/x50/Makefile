CXX = g++
CC = $(CXX)

CFLAGS = 	-std=c++11 \
			-I/home/user1/uWebSockets/src \
			-I/home/user1/uSockets/src
LDFLAGS = 	-L/home/user1/uWebSockets \
			-L/home/user1/uSockets 

all : app

app : main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o app main.o http_srv.o /home/user1/uSockets/*.o -lpthread

main.o : main.cpp http_srv.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.cpp http_srv.cpp

clean:
	rm -f *.o app