#!/bin/bash
source ./colour_print.sh


# Organize the input parameters.
while getopts 'hsr' arg; do
	case $arg in
		h) hard=true;;
		s) soft=true;;
		r) remote=true;;
	esac
done

# Validate the input arguments.
if [[ $hard && $soft ]]; then
	printColour Red "Error! Cannot perform a hard and soft reset simultaneously!"
	exit 1
fi

# Get list of commits and extract previous hash and message.
readarray -t logs <<< $(git log --pretty=oneline)
hash=${logs[1]:0:40}
message=${logs[1]:41}

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

# Display details of previous commit.
printColour LightGreen "\nPerforming a ${remoteText}LOCAL ${localText}reset to the previous commit..."
echo "message:  $message"
echo "hash:     $hash"
printColour DarkGrey "════════════════════════════════════════════════════════════════════════════"

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
