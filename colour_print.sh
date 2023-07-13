#!/bin/bash


# Prints the given text in the given colour.
# Parameters: colour, text
function printColour() {

: "
Black        0;30     Dark Gray     1;30
Red          0;31     Light Red     1;31
Green        0;32     Light Green   1;32
Brown/Orange 0;33     Yellow        1;33
Blue         0;34     Light Blue    1;34
Purple       0;35     Light Purple  1;35
Cyan         0;36     Light Cyan    1;36
Light Gray   0;37     White         1;37
"
	case $1 in
	"Black")
		printf "\033[0;30m$2\033[0m"
		;;
	"Red")
		printf "\033[0;31m$2\033[0m"
		;;
	"Green")
		printf "\033[0;32m$2\033[0m"
		;;
	"Orange")
		printf "\033[0;33m$2\033[0m"
		;;
	"Blue")
		printf "\033[0;34m$2\033[0m"
		;;
	"Purple")
		printf "\033[0;35m$2\033[0m"
		;;
	"Cyan")
		printf "\033[0;36m$2\033[0m"
		;;
	"Grey")
		printf "\033[0;37m$2\033[0m"
		;;
	"DarkGrey")
		printf "\033[1;30m$2\033[0m"
		;;
	"LightRed")
		printf "\033[1;31m$2\033[0m"
		;;
	"LightGreen")
		printf "\033[1;32m$2\033[0m"
		;;
	"Yellow")
		printf "\033[1;33m$2\033[0m"
		;;
	"LightBlue")
		printf "\033[1;34m$2\033[0m"
		;;
	"LightPurple")
		printf "\033[1;35m$2\033[0m"
		;;
	"LightCyan")
		printf "\033[1;36m$2\033[0m"
		;;
	"White")
		printf "\033[1;37m$2\033[0m"
		;;
	*)
		printf $2
		;;
	esac
}