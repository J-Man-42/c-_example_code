# Variables and lists.
######################################################################
SOURCE_1 := colour_text
HEADERS := \
	colour_text.h
OBJECTS := \
	out/colour_text.o
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp
	g++ -Wall -c main.cpp -o out/main.o

out/colour_text.o:  $(SOURCE_1).cpp $(SOURCE_1).h
	g++ -Wall -c $(SOURCE_1).cpp -o out/colour_text.o

out/:
	mkdir -p out

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -rf out main output.txt
