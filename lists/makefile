main:  main.o linked_list.o linked_list.h
	g++ -Wall main.o linked_list.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

linked_list.o:  linked_list.cpp linked_list.h
	g++ -Wall -c linked_list.cpp

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
