all: entropyCalculator.c randomFileGenerator.c
	gcc -o entropy entropyCalculator.c -lm
	gcc -o random randomFileGenerator.c 
	./random 100 input100.txt
	./random 1000 input1000.txt
	./random 10000 input10000.txt
	./random 100000 input100000.txt
	./random 1000000 input1000000.txt
	./entropy helloWorld.txt
	./entropy star.jpg
	./entropy star.jpg.zip
	./entropy romeoxjuliet.pdf
	./entropy romeoxjuliet.pdf.zip
	./entropy input100.txt
	./entropy input1000.txt
	./entropy input10000.txt
	./entropy input100000.txt
	./entropy input1000000.txt
	


clean:
	rm entropy
	rm random
	rm input100.txt
	rm input1000.txt
	rm input10000.txt
	rm input100000.txt
	rm input1000000.txt
