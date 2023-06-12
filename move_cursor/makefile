main:  main.o move_cursor.o move_cursor.h
	g++ -Wall main.o move_cursor.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

move_cursor.o:  move_cursor.cpp move_cursor.h
	g++ -Wall -c move_cursor.cpp

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
