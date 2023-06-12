main:  main.o
	g++ -Wall main.o -o main

main.o:  main.cpp linked_list.cpp linked_list.h node.cpp node.h
	g++ -Wall -c main.cpp

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
