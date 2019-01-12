.PHONY:all
all:server client
server:	TcpServer.cc
	g++ -o $@ $^
client: TcpClient.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -rf server client
