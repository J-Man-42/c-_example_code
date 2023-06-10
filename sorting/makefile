main:  main.o sorting.o sorting.h min_max.o ../min_and_max/min_max.h
	g++ -Wall main.o sorting.o min_max.o -o main

main.o:  main.cpp
	g++ -Wall -c main.cpp

sorting.o:  sorting.cpp sorting.h
	g++ -Wall -c sorting.cpp

min_max.o:  ../min_and_max/min_max.cpp ../min_and_max/min_max.h
	g++ -Wall -c ../min_and_max/min_max.cpp -o min_max.o

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
