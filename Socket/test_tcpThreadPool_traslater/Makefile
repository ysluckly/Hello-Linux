.PHONY:all
all:server client
server:	TcpServer.cc 
	g++ -o $@ $^ -std=c++11 -lpthread
client: TcpClient.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -rf server client
