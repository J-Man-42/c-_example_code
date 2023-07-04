# Variables and lists.
######################################################################
HEADERS := \
	stack.h \
	../colour_text/colour_text.h \
	../display_structure/display_structure.h \
	../move_cursor/move_cursor.h \
	../random/random.h
OBJECTS := \
	out/colour_text.o \
	out/display_structure.o \
	out/move_cursor.o \
	out/random.o
TEMPLATES := \
	stack.cpp \
	stack.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/colour_text.o:  ../colour_text/colour_text.cpp ../colour_text/colour_text.h
	g++ -Wall -c ../colour_text/colour_text.cpp -o out/colour_text.o

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
