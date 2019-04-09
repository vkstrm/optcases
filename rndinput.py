#!/usr/bin/env python3

import random
import sys

# pass f for floats or i for ints

if(sys.argv[1] == "f"):
    with open("floatdata.txt", "a") as file:
        for i in range(1024):
            file.write(str(random.uniform(1.0, 150.0)) + "\n")
elif(sys.argv[1] == "i"):
    with open("data.txt", "a") as file:
        for i in range(1024):
            file.write(str(random.randint(1, 150)) + "\n")