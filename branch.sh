#!/bin/bash
source ./colour_print.sh


# Show the help dialogue.
function showHelp {
	echo "╔════════════════════════════════════════════════════════════════════╗"
	echo "║ Usage: ./branch.sh [option] [value]                                ║"
	echo "║ arguments:                                                         ║"
	echo "║    -h:  Shows the help dialogue                                    ║"
	echo "║    -l:  Links all remote branches with local branches              ║"
	echo "║    -n:  Creates and links a new branch, locally and remotely       ║"
	echo "║    -d:  Deletes the specified branch, locally and remotely         ║"
	echo "║                                                                    ║"
	echo "║ Opens the help dialogue if no arguments are provided.              ║"
	echo "╚════════════════════════════════════════════════════════════════════╝"
	exit 1
}


# Get list of all local and remote branches.
function scanBranches {
	readarray -t branches <<< $(git branch -a)

	# Get all local branches.
	local -n _local=$1
	for (( i = 0; i < ${#branches[@]}; i++ )); do
		if [[ ${branches[i]} == *"HEAD"* ]]; then
			break
		fi
		readarray -d " " -t temp <<< ${branches[i]}
		_local+=(${temp[-1]})
	done

	# Get all remote branches.
	local -n _remote=$2
	for (( i++; i < ${#branches[@]}; i++ )); do
		readarray -d "/" -t temp <<< ${branches[i]}
		_remote+=(${temp[-1]})
	done
}


# Link all local and remote branches.
function linkBranches() {
	local=()
	remote=()
	scanBranches local remote

	# If branches don't exist locally, create them.
	for (( i = 0; i < ${#remote[@]}; i++ )); do
		branch=${remote[i]}
		if ! echo ${local[@]} | grep -qw $branch; then
			git branch $branch
			git branch --set-upstream-to=origin/$branch $branch
		fi
	done

	# If branches don't exist remotely, create them.
	for (( i = 0; i < ${#local[@]}; i++ )); do
		branch=${local[i]}
		if ! echo ${remote[@]} | grep -qw $branch; then
			git push origin $branch
			git branch --set-upstream-to=origin/$branch $branch
		fi
	done
}


# Creates a new branch both locally and remotely.
# Parameter: branch
function createNewBranch() {
	local=()
	remote=()
	scanBranches local remote

	# Ensure lowercase and _ instead of spaces.
	branch=$(echo "${1,,}" | tr " " _)
	exists=true

	# If local branch does not exist, create it.
	if ! echo ${local[@]} | grep -qw $branch; then
		git branch $branch
		exists=false
	fi

	# If remote branch does not exist, create it.
	if ! echo ${remote[@]} | grep -qw $branch; then
		git push origin $branch
		exists=false
	fi

	# Show error if branch already exists. Otherwise, link remote and local branch.
	if [[ $exists == true ]]; then
		printColour Red "Error! Branch '$branch' already exists."
	else
		git branch --set-upstream-to=origin/$branch $branch
	fi
}


# Deletes a branch both locally and remotely.
# Parameter: branch
function deleteBranch() {
	local=()
	remote=()
	scanBranches local remote

	# Ensure lowercase and _ instead of spaces.
	branch=$(echo "${1,,}" | tr " " _)
	missing=true

	# If local branch exists, delete it.
	if echo ${local[@]} | grep -qw $branch; then
		git branch -D $branch
		missing=false
	fi

	# If neither exists, show error message.
	if echo ${remote[@]} | grep -qw $branch; then
		git push origin --delete $branch
		missing=false
	fi

	# If neither exists, show error message.
	if [[ $missing == true ]]; then
		printColour Red "Error! Branch '$branch' does not exist."
	fi
}



# The main operations of the script starts here.
################################################################################

# Organize the input parameters.
while getopts "hln:d:" arg; do
	case $arg in
		h) help=true;;
		l) link=true;;
		n) new="${OPTARG}";;
		d) delete="${OPTARG}";;
	esac
done


# If an argument has not been provided, show the help dialogue.
if ! [[ $link || $new || $delete ]]; then
	help=true
fi

# If help is requested, show the help menu and exit.
if [[ $help ]]; then
	showHelp
fi

# Link branches
if [[ $link ]]; then
	linkBranches
fi

# Create a new branch.
if [[ $new ]]; then
	createNewBranch $new
fi

# Delete the specified branch.
if [[ $delete ]]; then
	deleteBranch $delete
fi
