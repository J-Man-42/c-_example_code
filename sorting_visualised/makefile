# Variables and lists.
######################################################################
SOURCE_1 := sorting
SOURCE_2 := ../colour_text/colour_text
SOURCE_3 := ../math/math
SOURCE_4 := ../move_cursor/move_cursor
SOURCE_5 := ../random/random
HEADERS := \
	sorting.h \
	../colour_text/colour_text.h \
	../math/math.h \
	../move_cursor/move_cursor.h \
	../random/random.h
OBJECTS := \
	out/sorting.o \
	out/colour_text.o \
	out/math.o \
	out/move_cursor.o \
	out/random.o
TEMPLATES := \
	../linked_list/linked_list.cpp \
	../linked_list/linked_list.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/sorting.o:  $(SOURCE_1).cpp $(SOURCE_1).h
	g++ -Wall -c $(SOURCE_1).cpp -o out/sorting.o

out/colour_text.o:  $(SOURCE_2).cpp $(SOURCE_2).h
	g++ -Wall -c $(SOURCE_2).cpp -o out/colour_text.o

out/math.o:  $(SOURCE_3).cpp $(SOURCE_3).h
	g++ -Wall -c $(SOURCE_3).cpp -o out/math.o

out/move_cursor.o:  $(SOURCE_4).cpp $(SOURCE_4).h
	g++ -Wall -c $(SOURCE_4).cpp -o out/move_cursor.o

out/random.o:  $(SOURCE_5).cpp $(SOURCE_5).h
	g++ -Wall -c $(SOURCE_5).cpp -o out/random.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
