# Prevent accidental overwrite.
if ls main.cpp 2>/dev/null; then
	printf "Overwrite existing main.cpp?  (Y/[N])\n"
	printf "> "
	read answer
	if [[ $answer == "N"* || $answer == "n"* ]]; then
		exit 1
	fi
fi


# Indicate to the user that main.cpp is being generated.
printf "Generating main.cpp file...\n"

# Create the standard main.cpp that prints Hello world.
printf "#include <iostream>\n" > main.cpp
printf "using namespace std;\n" >> main.cpp
printf "\n\n" >> main.cpp
printf "int main() {\n" >> main.cpp
printf "\tcout << \"Hello world!\" << endl;\n" >> main.cpp
printf "\treturn 0;\n" >> main.cpp
printf "}\n" >> main.cpp
