# Variables and lists.
######################################################################
HEADERS := \
	display_structure.h \
	../math/math.h \
	../random/random.h
OBJECTS := \
	out/display_structure.o \
	out/math.o \
	out/random.o
UPDATES := out/ out/main.o $(OBJECTS) $(HEADERS)



# Commands.
######################################################################
main:  $(UPDATES)
	g++ -Wall out/main.o $(OBJECTS) -o main

out/main.o:  main.cpp
	g++ -Wall -c main.cpp -o out/main.o

out/display_structure.o:  display_structure.cpp display_structure.h
	g++ -Wall -c display_structure.cpp -o out/display_structure.o

out/math.o:  ../math/math.cpp ../math/math.h
	g++ -Wall -c ../math/math.cpp -o out/math.o

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
