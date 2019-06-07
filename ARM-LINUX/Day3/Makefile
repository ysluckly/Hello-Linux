.PHONY:all
all:server client

server:server.c
	gcc $^ -o $@
client:client.c
	gcc $^ -o $@

.PHONY:clean
clean:
	rm -rf server client
