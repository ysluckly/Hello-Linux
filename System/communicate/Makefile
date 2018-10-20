.PHONY:all
all:server client

client:client.c
	gcc -c $^ -o $@
server:server.c
	gcc -c $^ -o $@
.PHONY:clean
clean:
	rm -rf client server mypipe
