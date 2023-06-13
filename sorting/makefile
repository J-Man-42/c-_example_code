main:  main.o sorting.o sorting.h colour_text.o ../colour_text/colour_text.h min_max.o ../min_and_max/min_max.h move_cursor.o ../move_cursor/move_cursor.h random.o ../random/random.h
	g++ -Wall main.o sorting.o colour_text.o min_max.o move_cursor.o random.o -o main

main.o:  main.cpp ../lists/linked_list.cpp ../lists/linked_list.h
	g++ -Wall -c main.cpp

sorting.o:  sorting.cpp sorting.h
	g++ -Wall -c sorting.cpp

colour_text.o:  ../colour_text/colour_text.cpp ../colour_text/colour_text.h
	g++ -Wall -c ../colour_text/colour_text.cpp -o colour_text.o

min_max.o:  ../min_and_max/min_max.cpp ../min_and_max/min_max.h
	g++ -Wall -c ../min_and_max/min_max.cpp -o min_max.o

move_cursor.o:  ../move_cursor/move_cursor.cpp ../move_cursor/move_cursor.h
	g++ -Wall -c ../move_cursor/move_cursor.cpp -o move_cursor.o

random.o:  ../random/random.cpp ../random/random.h
	g++ -Wall -c ../random/random.cpp -o random.o

run:  main
	./main

output:  main
	./main > output.txt

clean:
	rm -f *.o main output.txt
