#!/bin/bash


# Main functional process.
if [[ $# -eq 0 ]]; then
	echo "No files provided."
else

	# Iterate through all given files and fix them.
	for file in "${@:1}"; do
		echo "> $file"
		sed -i -e 's/\r$//' $file
	done
fi