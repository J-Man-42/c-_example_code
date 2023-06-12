main:  main.o move_cursor.o ../move_cursor/move_cursor.h
	g++ -Wall main.o move_cursor.o -o main

main.o:  main.cpp linked_list.cpp linked_list.h node.cpp node.h
	g++ -Wall -c main.cpp

move_cursor.o:  ../move_cursor/move_cursor.cpp ../move_cursor/move_cursor.h
	g++ -Wall -c ../move_cursor/move_cursor.cpp -o move_cursor.o

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
