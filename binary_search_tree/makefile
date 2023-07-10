# Variables and lists.
######################################################################
SOURCE_1 := ../colour_text/colour_text
SOURCE_2 := ../display_structure/display_structure
SOURCE_3 := ../move_cursor/move_cursor
SOURCE_4 := ../random/random
HEADERS := \
	binary_search_tree.h \
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
	../queue/queue.cpp \
	../queue/queue.h \
	binary_search_tree.cpp \
	binary_search_tree.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/colour_text.o:  $(SOURCE_1).cpp $(SOURCE_1).h
	g++ -Wall -c $(SOURCE_1).cpp -o out/colour_text.o

out/display_structure.o:  $(SOURCE_2).cpp $(SOURCE_2).h
	g++ -Wall -c $(SOURCE_2).cpp -o out/display_structure.o

out/move_cursor.o:  $(SOURCE_3).cpp $(SOURCE_3).h
	g++ -Wall -c $(SOURCE_3).cpp -o out/move_cursor.o

out/random.o:  $(SOURCE_4).cpp $(SOURCE_4).h
	g++ -Wall -c $(SOURCE_4).cpp -o out/random.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
