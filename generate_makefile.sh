#!/bin/bash


# Show the help dialogue.
function showHelp() {
	echo "╔════════════════════════════════════════════════════════════════════╗"
	echo "║ Creates a makefile based on the filenames of local header files.   ║"
	echo "║                                                                    ║"
	echo "║ Usage: ./generate_makefile.sh [option] [value]                     ║"
	echo "║ arguments:                                                         ║"
	echo "║    -h:  Shows the help dialogue                                    ║"
	echo "║    -i:  Specify additional headers to include in the makefile      ║"
	echo "║                                                                    ║"
	echo "║ Opens the help dialogue if no arguments are provided.              ║"
	echo "╚════════════════════════════════════════════════════════════════════╝"
	exit 1
}



# The main operations of the script starts here.
################################################################################

# Organize the input parameters.
while getopts "hi:" arg; do
	case $arg in
		h) help=true;;
		i) include+=("$OPTARG");;
	esac
done


# If help is requested, show the help menu and exit.
if [[ $help ]]; then
	showHelp
fi


# Gather list of all header filenames.
headers=( $(ls *.h 2>/dev/null | cut -d '.' -f1) )
paths=( $(echo ${include[@]%.*}) )
titles=( $(echo "${paths[@]}" | awk -F / '{print $NF}') )


# Start with main
printf "main:  main.o" > makefile
for title in ${headers[@]}; do
	printf " $title.o $title.h" >> makefile
done
for (( i = 0; i < ${#titles[@]}; i++ )); do
	printf " ${titles[i]}.o ${paths[i]}.h" >> makefile
done

# Compile all .o files.
printf "\n\tg++ -Wall main.o" >> makefile
for title in ${headers[@]}; do
	printf " $title.o" >> makefile
done
for title in ${titles[@]}; do
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
for (( i = 0; i < ${#titles[@]}; i++ )); do
	printf "\n${titles[i]}.o:  ${paths[i]}.cpp ${paths[i]}.h\n" >> makefile
	printf "\tg++ -Wall -c ${paths[i]}.cpp -o ${titles[i]}.o\n" >> makefile
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
