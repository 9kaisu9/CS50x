"""
Need to pip install pandas!
"""
import csv
import sys
import pandas as pd

seq_count = {}
database = {}


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Read database file into a variable (DataFrame)
    db = pd.read_csv(sys.argv[1])

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as txt:
        sequence = txt.read()

    # Find longest match of each STR in DNA sequence
    with open(sys.argv[1], "r") as data:
        reader = csv.reader(data)
        for str in list(reader)[0][1:]:
            seq_count[str] = longest_match(sequence, str)

    # Check database for matching profiles
    for row in range(len(db)):
        dna_found = False
        matches = 0
        for col in db.columns[1:]:
            if db.at[row, col] == seq_count[col]:
                matches += 1
        if matches == len(db.columns[1:]):
            print(db.at[row, "name"])
            dna_found = True
    if dna_found == False:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
