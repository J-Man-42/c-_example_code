main.o: main.cpp
	g++ -Wall main.cpp -o main.o

run: main.o
	./main.o

output: main.o
	./main.o > output.txt

clean:
	rm -f *.o output.txt
