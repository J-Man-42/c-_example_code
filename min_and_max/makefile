# Variables and lists.
######################################################################
HEADERS := \
	min_max.h
SOURCES := \
	min_max.cpp
OBJECTS := \
	out/min_max.o
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp
	g++ -Wall -c main.cpp -o out/main.o

out/min_max.o:  min_max.cpp min_max.h
	g++ -Wall -c min_max.cpp -o out/min_max.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
