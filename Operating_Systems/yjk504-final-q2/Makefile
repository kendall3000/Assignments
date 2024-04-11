all: server client

client: client.c
	gcc -g client.c -o client -lnsl

server: server.c
	gcc -g server.c -o server -lnsl

clean:
	rm -f client server
