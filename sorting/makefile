# Variables and lists.
######################################################################
SOURCE_1 := ../math/math
SOURCE_2 := ../move_cursor/move_cursor
SOURCE_3 := ../random/random
HEADERS := \
	sorting.h \
	../math/math.h \
	../move_cursor/move_cursor.h \
	../random/random.h
OBJECTS := \
	out/math.o \
	out/move_cursor.o \
	out/random.o
TEMPLATES := \
	sorting.cpp \
	sorting.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/math.o:  $(SOURCE_1).cpp $(SOURCE_1).h
	g++ -Wall -c $(SOURCE_1).cpp -o out/math.o

out/move_cursor.o:  $(SOURCE_2).cpp $(SOURCE_2).h
	g++ -Wall -c $(SOURCE_2).cpp -o out/move_cursor.o

out/random.o:  $(SOURCE_3).cpp $(SOURCE_3).h
	g++ -Wall -c $(SOURCE_3).cpp -o out/random.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
