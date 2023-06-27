# Variables and lists.
######################################################################
HEADERS := \
	queue.h \
	../display_structure/display_structure.h \
	../move_cursor/move_cursor.h \
	../random/random.h
OBJECTS := \
	out/display_structure.o \
	out/move_cursor.o \
	out/random.o
TEMPLATES := \
	queue.cpp \
	queue.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/display_structure.o:  ../display_structure/display_structure.cpp ../display_structure/display_structure.h
	g++ -Wall -c ../display_structure/display_structure.cpp -o out/display_structure.o

out/move_cursor.o:  ../move_cursor/move_cursor.cpp ../move_cursor/move_cursor.h
	g++ -Wall -c ../move_cursor/move_cursor.cpp -o out/move_cursor.o

out/random.o:  ../random/random.cpp ../random/random.h
	g++ -Wall -c ../random/random.cpp -o out/random.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
