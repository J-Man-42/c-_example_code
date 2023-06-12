main:  main.o linked_list.cpp linked_list.h
	g++ -Wall main.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
