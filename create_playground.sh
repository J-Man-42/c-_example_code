#!/bin/bash


# Create the playground directory.
mkdir -p playground

# Genreate the main.cpp file.
./generate_main.sh
mv main.cpp playground/main.cpp

# Generate the makefile.
./generate_makefile.sh
mv makefile playground/makefile
