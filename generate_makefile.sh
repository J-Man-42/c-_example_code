#!/bin/bash


# Gather list of all header filenames.
headers=( $(ls *.h | cut -d '.' -f1) )


# Start with main
printf "main:  main.o" > makefile
for title in ${headers[@]}; do
	printf " $title.o $title.h" >> makefile
done

# Compile all .o files.
printf "\n\tg++ -Wall main.o" >> makefile
for title in ${headers[@]}; do
	printf " $title.o" >> makefile
done
echo " -o main" >> makefile


# Continue with main.o
printf "\nmain.o:  main.cpp\n" >> makefile
printf "\tg++ -Wall -c main.cpp\n" >> makefile


# Continue with each entry in headers.
for title in ${headers[@]}; do
	printf "\n$title.o:  $title.cpp $title.h\n" >> makefile
	printf "\tg++ -Wall -c $title.cpp\n" >> makefile
done


# Generate the make run command.
printf "\nrun:  main\n" >> makefile
printf "\t./main\n" >> makefile


# Generate the make output command.
printf "\noutput:  main\n" >> makefile
printf "\t./main > output.txt\n" >> makefile


# Generate the make clean command.
printf "\nclean:\n" >> makefile
printf "\trm -f *.o main output.txt\n" >> makefile
