import cs50
import csv
import sys

# Check for argvalues and return false if the count is not equal to 2


def main():
    if len(sys.argv) != 2:
        print("Usage: python roster.py name_of_house")
        exit(1)

    # assign variable to the house name provided
    house_name = sys.argv[1]

    # Assign a python variable to the SQL database students.db
    db = cs50.SQL("sqlite:///students.db")

    # Command to query student db based on house input
    row = db.execute("SELECT first, middle, last , birth FROM students WHERE house = ? ORDER BY last ASC, First ASC", house_name)
    for item in row:
        if item['middle'] == None:
            print(f"{item['first']} {item['last']}, born {item['birth']}")
        else:
            print(f"{item['first']} {item['middle']} {item['last']}, born {item['birth']}")


main()
