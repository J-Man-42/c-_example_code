main:  main.o min_max.o min_max.h
	g++ -Wall main.o min_max.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

min_max.o:  min_max.cpp min_max.h
	g++ -Wall -c min_max.cpp

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
