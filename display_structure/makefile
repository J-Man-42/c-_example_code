# Variables and lists.
######################################################################
SOURCE_1 := display_structure
SOURCE_2 := ../colour_text/colour_text
SOURCE_3 := ../random/random
HEADERS := \
	display_structure.h \
	../colour_text/colour_text.h \
	../random/random.h
OBJECTS := \
	out/display_structure.o \
	out/colour_text.o \
	out/random.o
TEMPLATES := \
	../queue/queue.cpp \
	../queue/queue.h
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp $(TEMPLATES)
	g++ -Wall -c main.cpp -o out/main.o

out/display_structure.o:  $(SOURCE_1).cpp $(SOURCE_1).h
	g++ -Wall -c $(SOURCE_1).cpp -o out/display_structure.o

out/colour_text.o:  $(SOURCE_2).cpp $(SOURCE_2).h
	g++ -Wall -c $(SOURCE_2).cpp -o out/colour_text.o

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
