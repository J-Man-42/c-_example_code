#!/bin/bash


# See if filename has been provided.
if [[ $# -eq 0 ]]; then
	echo "No filename provided."
else

	# Correctly format file title.
	title=$(echo $1 | cut -d '.' -f1)
	echo "Creating makefile for $title.cpp"

	# Output to makefile.
	printf "$title.o: $title.cpp\n" > makefile
	printf "\tg++ -Wall $title.cpp -o $title.o\n" >> makefile

	printf "\nrun: $title.o\n" >> makefile
	printf "\t./$title.o\n" >> makefile

	printf "\noutput: $title.o\n" >> makefile
	printf "\t./$title.o > output.txt\n" >> makefile

	printf "\nclean:\n" >> makefile
	printf "\trm -f *.o output.txt\n" >> makefile
fi
