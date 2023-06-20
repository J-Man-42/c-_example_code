# Prevent accidental overwrite.
if ls main.cpp 2>/dev/null; then
	printf "Overwrite existing main.cpp?  (Y/[N])\n"
	printf "> "
	read answer
	if [[ $answer == "N"* || $answer == "n"* ]]; then
		exit 1
	fi
fi


# Create the standard main.cpp that prints Hello world.
printf "Creating new main.cpp"

printf "#include <iostream>\n" > main.cpp
printf "using namespace std;\n" >> main.cpp
printf "\n\n" >> main.cpp
printf "int main() {\n" >> main.cpp
printf "\tcout << \"Hello world!\" << endl;\n" >> main.cpp
printf "\treturn 0;\n" >> main.cpp
printf "}\n" >> main.cpp
