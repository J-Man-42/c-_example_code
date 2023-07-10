# Variables and lists.
######################################################################
SOURCE_1 := random
HEADERS := \
	random.h
OBJECTS := \
	out/random.o
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp
	g++ -Wall -c main.cpp -o out/main.o

out/random.o:  $(SOURCE_1).cpp $(SOURCE_1).h
	g++ -Wall -c $(SOURCE_1).cpp -o out/random.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
