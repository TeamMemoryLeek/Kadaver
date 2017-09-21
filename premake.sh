#!/bin/bash

uname_s=$(uname -s)
os=""

# Linux system
if [ "$uname_s" == "Linux" ]; then
	os="linux"

# Max OS X system
elif [ "$uname_s" == "Darwin" ]; then
	os="osx"

# Assume Windows
else
	os="windows"
fi


# Validate the premake executable
if [ ! -f "bin/premake5" ]; then
	echo "Premake executable not found. Run 'init' to fetch one."
	read -p "Press enter to continue.."
	exit
fi


# Windows
if [ "$os" == "windows" ]; then
	bin/premake5 "--file=src/premake5.lua" "vs2017"

# Linux
elif [ "$os" == "linux" ]; then
	bin/premake5 "--file=src/premake5.lua" "codelite"

# Mac OS X
elif [ "$os" == "osx" ]; then
	bin/premake5 "--file=src/premake5.lua" "xcode4"
fi
