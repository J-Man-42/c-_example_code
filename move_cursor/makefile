# Variables and lists.
######################################################################
HEADERS := \
	move_cursor.h
SOURCES := \
	move_cursor.cpp
OBJECTS := \
	out/move_cursor.o
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp
	g++ -Wall -c main.cpp -o out/main.o

out/move_cursor.o:  move_cursor.cpp move_cursor.h
	g++ -Wall -c move_cursor.cpp -o out/move_cursor.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
