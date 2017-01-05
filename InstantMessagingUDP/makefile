compile: client.c server.c
	gcc -o client client.c
	gcc -o server server.c
runServer:
	./server
runClient: 
	./client localhost 9100
clean:
	rm server
	rm client
	rm output.txt
