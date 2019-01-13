.PHONY:all
all:server client
server:	TcpServer.cc 
	g++ -o $@ $^ -std=c++11
client: TcpClient.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -rf server client
