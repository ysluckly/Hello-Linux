.PHONY:all
all:server client
client:UdpClient.cc
	g++ -g $^ -o $@
server:UdpServer.cc
	g++ -g $^ -o $@
.PHONY:clean
clean:
	rm -rf client server 
