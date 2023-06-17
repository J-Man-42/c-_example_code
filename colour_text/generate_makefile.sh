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
	echo "║    -t:  Specify titles to include that use template classes        ║"
	echo "╚════════════════════════════════════════════════════════════════════╝"
	exit 1
}



# The main operations of the script starts here.
################################################################################

# Organize the input parameters.
while getopts "hi:t:" arg; do
	case $arg in
		h) help=true;;
		i) includes+=("$OPTARG");;
		t) templates+=("$OPTARG");;
	esac
done


# If help is requested, show the help menu and exit.
if [[ $help ]]; then
	showHelp
fi


# Gather list of all header filenames.
headers=( $(ls *.h 2>/dev/null | cut -d '.' -f1) )
includes=( $(echo "${includes[@]%.*}") )
for path in "${includes[@]}"; do
	titles+=( $(echo "$path" | awk -F / '{print $NF}') )
done
templates=( $(echo "${templates[@]%.*}")  )


# Print the variables and lists section.
printf "# Variables and lists.\n" > makefile
for (( i = 0; i < 70; i++ )); do
	printf "#" >> makefile
done

# HEADERS.
printf "\nHEADERS :=" >> makefile
for path in ${headers[@]}; do
	printf " \\" >> makefile
	printf "\n\t$path.h" >> makefile
done
for path in ${includes[@]}; do
	printf " \\" >> makefile
	printf "\n\t$path.h" >> makefile
done

# SOURCES.
printf "\nSOURCES :=" >> makefile
for path in ${headers[@]}; do
	printf " \\" >> makefile
	printf "\n\t$path.cpp" >> makefile
done
for path in ${includes[@]}; do
	printf " \\" >> makefile
	printf "\n\t$path.cpp" >> makefile
done

# OBJECTS.
printf "\nOBJECTS :=" >> makefile
for title in ${headers[@]}; do
	if [[ "${templates[@]}" && "${templates[@]}" == *"$title"* ]]; then
		continue
	fi
	printf " \\" >> makefile
	printf "\n\tout/$title.o" >> makefile
done
for title in ${titles[@]}; do
	printf " \\" >> makefile
	printf "\n\tout/$title.o" >> makefile
done

# TEMPLATES.
if [[ "${templates[@]}" ]]; then
	printf "\nTEMPLATES :=" >> makefile
fi
for title in ${templates[@]}; do
	printf " \\" >> makefile
	printf "\n\t$title.cpp" >> makefile
	printf " \\" >> makefile
	printf "\n\t$title.h" >> makefile
done

# UPDATES.
printf "\nUPDATES := out/ out/main.o \$(OBJECTS) \$(HEADERS)" >> makefile


# Print the commands section.
printf "\n\n\n\n# Commands.\n" >> makefile
for (( i = 0; i < 70; i++ )); do
	printf "#" >> makefile
done

# Start with main
printf "\nmain:  \$(UPDATES)\n" >> makefile
printf "\tg++ -Wall out/main.o \$(OBJECTS) -o main\n" >> makefile

# Continue with main.o
printf "\nout/main.o:  main.cpp" >> makefile
if [[ "${templates[@]}" ]]; then
	printf " \$(TEMPLATES)" >> makefile
fi
printf "\n\tg++ -Wall -c main.cpp -o out/main.o\n" >> makefile


# Continue with each entry in headers.
for title in ${headers[@]}; do
	if [[ "${templates[@]}" && "${templates[@]}" == *"$title"* ]]; then
		continue
	fi
	printf "\nout/$title.o:  $title.cpp $title.h\n" >> makefile
	printf "\tg++ -Wall -c $title.cpp -o out/$title.o\n" >> makefile
done


# Continue with each additional included title.
for (( i = 0; i < ${#titles[@]}; i++ )); do
	printf "\nout/${titles[i]}.o:  ${includes[i]}.cpp ${includes[i]}.h\n" >> makefile
	printf "\tg++ -Wall -c ${includes[i]}.cpp -o out/${titles[i]}.o\n" >> makefile
done


# Generate the output folder creation command.
printf "\nout/:\n" >> makefile
printf "\tmkdir -p out\n" >> makefile


# Generate the make run command.
printf "\nrun:  main\n" >> makefile
printf "\t./main\n" >> makefile


# Generate the make output command.
printf "\noutput:  main\n" >> makefile
printf "\t./main > output.txt\n" >> makefile


# Generate the make clean command.
printf "\nclean:\n" >> makefile
printf "\trm -rf out main output.txt\n" >> makefile
