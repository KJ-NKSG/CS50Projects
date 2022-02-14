from cs50 import get_int

# Prompt user to input height of half pyramid that is only between 1 and 8 inclusive
while True:
    n = get_int("Height: ")
    if 1 <= n <= 8:
        break
    else:
        False

# Code to print pyramid
for i in range(1, n + 1, 1):
    # j count for spaces at front
    j = n - i
    # print out pyramid
    print(f"{j * ' '}{i * '#'}{2 * ' '}{i * '#'}")