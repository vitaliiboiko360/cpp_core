CXX = g++
CC = $(CXX)

CFLAGS = 	-std=c++17 \
			-I/home/user1/uWebSockets/src \
			-I/home/user1/uWebSockets/helpers \
			-I/home/user1/uSockets/src
LDFLAGS = 	-L/home/user1/uWebSockets \
			-L/home/user1/uSockets 

all : app

app : main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o app main.o /home/user1/uSockets/*.o -lpthread -lz

main.o : main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.cpp

clean:
	rm -f *.o app