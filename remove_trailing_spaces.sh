# Show the help dialogue.
function showHelp {
	echo "╔══════════════════════════════════════════════════════════╗"
	echo "║ Usage: ./remove_trailing_spaces.sh [option]              ║"
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


# Read file and remove trailing whitespaces.
if [[ $file ]]; then
	echo "Removing trailing spaces for '${file}'..."
	readarray -t lines < $file

	# Create temporary file for output.
	temp="$(echo $file | cut -d '.' -f1).tmp"
	rm -f $temp && touch $temp

	# Write all lines to file.
	for (( i = 0; i < "${#lines[@]}"; i++ )); do
		if [[ "${lines[i]}" == *$'\t' || "${lines[i]}" == *" " ]]; then
			echo "$(sed -e 's/[[:space:]]*$//'<<<"${lines[i]}")" >> $temp
		else
			echo "${lines[i]}" >> $temp
		fi
	done

	# Delete original and rename temp.
	rm $file
	mv $temp $file
fi
