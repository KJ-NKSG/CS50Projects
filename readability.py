from cs50 import get_string


def main():
    # Get text
    text = get_string("Text: ")

    # Count letters in the text
    L = countletters(text)

    # Count words
    W = countwords(text)

    # Count Sentences
    S = countsent(text)

    # Calculate the coleman-liau index
    index = round(0.0588 * (L / W * 100) - 0.296 * (S / W * 100) - 15.8)

    # Print Grade
    if index < 1:
        print("Before Grade 1\n")

    elif index > 16:
        print("Grade 16+\n")

    else:
        print(f"Grade {index}\n")

    return 0


def countletters(text):

    count = 0
    for i in text:
        if (i.isalpha()) == True:
            count += 1

    return count


def countwords(text):

    count = 0
    # As example states words are seperated by spaces
    # use the split() fnction with dafault whitespace as seperator setting
    split_text = text.split()

    # count the words in the split text
    count = len(split_text)

    return count

# counting sentences 
def countsent(text):

    n = len(text)
    count = 0
    for i in range(n):
        if text[i] == '.' or text[i] == '?' or text[i] == '!':
            count += 1

    return count


main()