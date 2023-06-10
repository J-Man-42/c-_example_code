main:  main.o sorting.o sorting.h colour_text.o ../colour_text/colour_text.h min_max.o ../min_and_max/min_max.h
	g++ -Wall main.o sorting.o colour_text.o min_max.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

sorting.o:  sorting.cpp sorting.h
	g++ -Wall -c sorting.cpp

colour_text.o:  ../colour_text/colour_text.cpp ../colour_text/colour_text.h
	g++ -Wall -c ../colour_text/colour_text.cpp -o colour_text.o

min_max.o:  ../min_and_max/min_max.cpp ../min_and_max/min_max.h
	g++ -Wall -c ../min_and_max/min_max.cpp -o min_max.o

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
