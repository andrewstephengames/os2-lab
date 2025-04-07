import sys
import os
import time

def exercise1():
    print('Exercise 1')
    name = input("Input your name: ")
    print('Hello, ', name)
    return

def exercise2():
    print('Exercise 2')
    a = input("a = ")
    b = input("b = ")
    c = input("c = ")
    d = input("d = ")
    result = int(a) + int(b)*int(c)+int(d)
    print('Result: ', result)
def compute(a, b):
    if int(a) > 10 or int(b) > 10:
        print ('a larger than 10')
    else:
        result = int(a)*int(b)
    return result
    print('Result: ', result)

def exercise3():
    print('Exercise 3 and 4')
    try:
        a = int(input ("a = "))
        b = int(input ("b = "))
    except:
        print('Error: non-numeric input')
        sys.exit(1)
    print(compute(a, b))

def exercise5():
    print('Exercise 5 and 6')
    position = 0
    cow_count = 0
    bull_count = 0
    total_trials = 0
    average_success = 0
    initial_layout = range(1, 4)
    print(initial_layout)
    while input(">") != "exit":
        start = time.time()
        player = input(">")
        end = time.time()
        print('Time for guess: ', end-start)
        total_trials += 1
        for i in initial_layout:
            if player != "exit" and not player.isdigit():
                print('Invalid input')
                sys.exit(1)
            if int(player) == i:
                bull_count += 1
            else:
                cow_count += 1
        print(bull_count, ' bulls')
        print(cow_count, ' cows')
        if bull_count == len(initial_layout) or cow_count == len(initial_layout):
            break
    average_success = float(bull_count)/total_trials
    print('Total trials: ', total_trials)
    print('Average success rate: ', average_success)

def exercise7():
    print('Exercise 7')
    with open ('file1.txt', 'r') as f:
        content = f.read()
        print('Read content: ', content)
        with open('file2.txt', 'w') as f:
            content2 = content.upper()
            print('Written content: ', content2)
            f.write(content2)


if __name__ == "__main__":
    exercise1()
    exercise2()
    exercise3()
    exercise5()
    exercise7()
