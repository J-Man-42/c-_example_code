#!/bin/bash
source ./colour_print.sh


# Organize the input parameters.
while getopts 'hsrn:' arg; do
	case $arg in
		h) hard=true;;
		s) soft=true;;
		r) remote=true;;
		n) number="${OPTARG}";;
	esac
done

# Validate the input arguments.
if [[ $hard && $soft ]]; then
	printColour Red "Error! Cannot perform a hard and soft reset simultaneously!\n"
	exit 1
fi

# Ensure number is at least 1.
digit='^[0-9]+$'
if ! [[ $number && $number =~ $digit && $number -ge 1 ]]; then
	number=1
fi

# Get list of commits
readarray -t logs <<< $(git log --pretty=oneline)

# Ensure number is within range.
maxValue=$(("${#logs[@]}" - 1))
if (( number > maxValue)); then
	number=$maxValue
fi

# Extract previous hash and message.
hash=${logs[$number]:0:40}
message=${logs[$number]:41}

# Format the local commit text to display below.
if [[ $hard ]]; then
	localText="hard-"
elif [[ $soft ]]; then
	localText="soft-"
fi

# Format the remote commit text to display below.
if [[ $remote ]]; then
	remoteText="REMOTE reset and a "
fi

# Format the message for previous commit.
if (( number == 1)); then
	previous="to the previous commit"
else
	previous="$number commits back"
fi

# Display details of previous commit.
printColour LightGreen "\nPerforming a ${remoteText}LOCAL ${localText}reset ${previous}...\n"
echo "message:  $message"
echo "hash:     $hash"
printColour DarkGrey "════════════════════════════════════════════════════════════════════════════\n"

# Reset local branch to previous commit.
if [[ $hard ]]; then
	git reset --hard $hash
elif [[ $soft ]]; then
	git reset --soft $hash
else
	git reset $hash
fi

# If desired, reset remote branch to previous commit.
if [[ $remote ]]; then
	git push -f
fi
