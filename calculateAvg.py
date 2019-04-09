#!/usr/bin/env python3


# Check the average for all the results
def main():
    times = []
    with open("result.txt", 'r') as tfile:
        for line in tfile:
            times.append(line.split(' ')[0])
    
    count = len(times) - 10
    sum = 0
    for i in times[10:]:
        sum += int(i)

    avg = sum / count
    print(avg)

if __name__ == "__main__":
    main()
