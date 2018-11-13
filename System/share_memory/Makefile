all:server client

server:server.cpp common.cpp
	g++ $^ -o $@
client:client.cpp common.cpp
	g++  $^ -o $@
.PHONY:clean
clean:
	rm -f server client all
