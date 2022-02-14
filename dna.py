# import panda for dataframe manipulation for this exercise
import pandas as pd
import sys
import csv
import re


# def main():
# for i in range(20):
# check(i + 1)

def main():
    # Command Line Prompt Check
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    csvfile = sys.argv[1]
    seqfile = sys.argv[2]
    # seqfile = f"sequences/{d}.txt"

    # Read Database in a dataframe
    df = pd.read_csv(csvfile, header=0, index_col=0)

    # Reader will return input as a list but in a 2D list. We only want
    # first row / 1D List data, hence [0][0]is inserted.
    with open(seqfile) as f:
        seq_data = f.read()

    # Search and count STR strings in DNA ssequence
    # Referencing https://stackoverflow.com/questions/61131768/how-to-count-consecutive-substring-in-a-string-in-python-3
    # for the RE expression formula of (?:xx)+.
    # (?: xx ) non capturing version of regula parentheses. Matches whatever regular expression is inside the parenthesis,
    # but the substring matched by the group cannot be retrieved afer performing a match or referenced later in the pattern.
    # hence adding an additional  + which is to replicate preceding expression, allows consecutive finds.

    str_dic = {}
    for col_name in df.columns:
        c = max(re.findall(f"(?:{col_name})+", seq_data), default=0)
        if c == 0:
            count = 0
        else:
            count = c.count(col_name)
        str_dic[col_name] = count

    # Match with df table and return name
    counter = 0
    for i in range(len(df.index)):
        for j in range(len(df.columns)):
            for k in str_dic.keys():
                if k == df.columns[j]:
                    if str_dic[k] == df.iloc[i, j]:
                        counter += 1
        if counter == len(df.columns):
            print(df.index[i])
            return 0
        else:
            counter = 0

    print("No match")

    return 0


main()
