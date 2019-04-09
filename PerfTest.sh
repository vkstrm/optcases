#!/usr/bin/env bash

# Run the passed file 110 times
# Call the python script to figure out the average
if [[ -e "result.txt" ]]; then
    rm result.txt
fi

for i in {1..110}; do
    #./$1 112 1024 >> result.txt # When input is needed
    ./$1 >> result.txt
done

python3 calculateAvg.py

mv result.txt $2.txt
mv $2.txt Mätningar/$2.txt
