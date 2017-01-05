all: client.c server.c
	gcc -o client client.c
	gcc -o server server.c
	./server &
	./client localhost
compile: client.c server.c
	gcc -o client client.c
	gcc -o server server.c
runServer:
	./server
runClient: 
	./client localhost
clean:
	rm server
	rm client
