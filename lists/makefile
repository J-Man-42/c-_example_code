# Variables and lists.
######################################################################
HEADERS := \
	linked_list.h \
	node.h \
	../random/random.h \
	../move_cursor/move_cursor.h
SOURCES := \
	linked_list.cpp \
	node.cpp \
	../random/random.cpp \
	../move_cursor/move_cursor.cpp
OBJECTS := \
	out/random.o \
	out/move_cursor.o
TEMPLATES := \
	linked_list.cpp \
	linked_list.h \
	node.cpp \
	node.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/:
	mkdir -p out

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/random.o:  ../random/random.cpp ../random/random.h
	g++ -Wall -c ../random/random.cpp -o out/random.o

out/move_cursor.o:  ../move_cursor/move_cursor.cpp ../move_cursor/move_cursor.h
	g++ -Wall -c ../move_cursor/move_cursor.cpp -o out/move_cursor.o

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
