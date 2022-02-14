from cs50 import get_int


def main():
    # Get Credit card number - length of 13 , 15 or 16 only
    while True:
        n = get_int("Number: ")
        if n > 0:
            break
        else:
            False
    # Assign variable

    ccno = str(n)

    # Return invalid Credit card if number is not of length 13,15 or 16
    if len(ccno) not in {13, 15, 16}:
        print("INVALID")
        exit(1)

    # Check the first 1 or 2 digits and calculate checksum
    # if meets credit card reqruirements, return the type of Credit card.

    if int(ccno[:2]) in {34, 37}:
        if checksum(n) == 0:
            print("AMEX")
        else:
            print("INVALID")

    elif int(ccno[:2]) in {51, 52, 53, 54, 55}:
        if checksum(n) == 0:
            print("MASTERCARD")
        else:
            print("INVALID")

    elif int(ccno[0]) == 4:
        if checksum(n) == 0:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def checksum(n):
    # convert to string
    z = str(n)
    # Assign variable to cc length
    y = len(z)

    var1 = 0
    var2 = 0

    for i in range(y - 2, -1, -2):
        var1 += sum(map(int, str(2 * int(z[i]))))

    for i in range(y - 1, -1, -2):
        var2 += int(z[i])

    return (var1 + var2) % 10


main()
