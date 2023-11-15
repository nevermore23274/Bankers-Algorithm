#!/bin/bash

# Clear the screen
clear
# Compile the program
echo "Compiling the program..."
g++ hw4.cpp -o hw4
echo -e "Compiling completed.\n"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    # Run the program with different input files
    for i in {0..3}
    do
        echo "Running with input$i.txt..."
        ./hw4 input$i.txt
        echo -e "\n"
    done
else
    echo "Compilation failed."
fi

# Drop back to the shell
exec /bin/bash
