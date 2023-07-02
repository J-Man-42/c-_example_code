# Show the help dialogue.
function showHelp {
	echo "╔══════════════════════════════════════════════════════════╗"
	echo "║ Usage: ./fix_spaces.sh [option]                          ║"
	echo "║ optional arguments:                                      ║"
	echo "║    -h:  Shows the help dialogue                          ║"
	echo "║    -f:  Select the file to update                        ║"
	echo "║                                                          ║"
	echo "║ Opens the help dialogue if no arguments are provided.    ║"
	echo "╚══════════════════════════════════════════════════════════╝"
	exit 1
}



# The main operations of the script starts here.
################################################################################

# Organize the input parameters.
while getopts "hf:" arg; do
	case $arg in
		h) help=true;;
		f) file="${OPTARG}";;
	esac
done

# Help is true if file was not provided.
if ! [[ $file ]]; then
	help=true
fi


# Show help dialogue.
if [[ $help ]]; then
	showHelp
fi


# Read file and correct trailing whitespaces.
if [[ $file ]]; then
	readarray -t lines < $file
	printf "" > $file
	for (( i = 0; i < "${#lines[@]}"; i++ )); do
		echo "$(sed -e 's/[[:space:]]*$//'<<<"${lines[i]}")" >> $file
	done
fi
