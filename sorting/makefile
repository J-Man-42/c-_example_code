# Variables and lists.
######################################################################
HEADERS := \
	sorting.h \
	../colour_text/colour_text.h \
	../min_and_max/min_max.h \
	../move_cursor/move_cursor.h \
	../random/random.h
SOURCES := \
	sorting.cpp \
	../colour_text/colour_text.cpp \
	../min_and_max/min_max.cpp \
	../move_cursor/move_cursor.cpp \
	../random/random.cpp
OBJECTS := \
	out/sorting.o \
	out/colour_text.o \
	out/min_max.o \
	out/move_cursor.o \
	out/random.o
TEMPLATES := \
	../lists/linked_list.cpp \
	../lists/linked_list.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/:
	mkdir -p out

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/sorting.o:  sorting.cpp sorting.h
	g++ -Wall -c sorting.cpp -o out/sorting.o

out/colour_text.o:  ../colour_text/colour_text.cpp ../colour_text/colour_text.h
	g++ -Wall -c ../colour_text/colour_text.cpp -o out/colour_text.o

out/min_max.o:  ../min_and_max/min_max.cpp ../min_and_max/min_max.h
	g++ -Wall -c ../min_and_max/min_max.cpp -o out/min_max.o

out/move_cursor.o:  ../move_cursor/move_cursor.cpp ../move_cursor/move_cursor.h
	g++ -Wall -c ../move_cursor/move_cursor.cpp -o out/move_cursor.o

out/random.o:  ../random/random.cpp ../random/random.h
	g++ -Wall -c ../random/random.cpp -o out/random.o

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
