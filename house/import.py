import cs50
import csv
import sys

# Check for argvalues and return false if the count is not equal to 2


def main():
    if len(sys.argv) != 2:
        print("Usage: python import.py characters.csv")
        exit(1)

    # Assign a python variable to the SQL database students.db
    db = cs50.SQL("sqlite:///students.db")

    # Open CSV File and import the data
    # CSV file is ordered in Name / House / Birth
    with open(sys.argv[1], "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            n = row['name'].split()
            h = row['house']
            b = row['birth']
            nu = None
            if len(n) == 2:
                db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?, ?, ?, ?, ?)",
                           n[0], nu, n[1], h, b)
            elif len(n) == 3:
                db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?, ?, ?, ?, ?)",
                           n[0], n[1], n[2], h, b)


main()
