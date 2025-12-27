#!/bin/bash

# Compile script for SocialNet Simulator
# COL106 Long Assignment 2

echo "======================================"
echo "  Compiling SocialNet Simulator..."
echo "======================================"
echo ""

# Check if g++ is available
if ! command -v g++ &> /dev/null
then
    echo "Error: g++ compiler not found!"
    echo "Please install g++ to compile this program."
    exit 1
fi

# Source file name
SOURCE_FILE="main.cpp"

# Output executable name
OUTPUT_FILE="socialnet"

# Check if source file exists
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file '$SOURCE_FILE' not found!"
    echo "Please ensure main.cpp is in the current directory."
    exit 1
fi

# Compile with g++
echo "Compiling $SOURCE_FILE..."
g++ -std=c++17 -O2 -Wall -Wextra -o "$OUTPUT_FILE" "$SOURCE_FILE"

