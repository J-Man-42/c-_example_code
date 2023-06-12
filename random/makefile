main:  main.o random.o random.h
	g++ -Wall main.o random.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

random.o:  random.cpp random.h
	g++ -Wall -c random.cpp

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
