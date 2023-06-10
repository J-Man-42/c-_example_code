main:  main.o colour_text.o colour_text.h
	g++ -Wall main.o colour_text.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

colour_text.o:  colour_text.cpp colour_text.h
	g++ -Wall -c colour_text.cpp

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
