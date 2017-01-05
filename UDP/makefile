compile: client.c server.c
	gcc -o client client.c
	gcc -o server server.c
run:
	./server & 
	./client localhost 9100 input.txt
clean:
	rm server
	rm client
	rm output.txt
