.PHONY:all 
all:server client
server:select_server.cpp 
	g++ -o $@ $^
client:select_server.cpp 
	g++ -o $@ $^

.PHONY:clean
clean 
	rm -rf server client
