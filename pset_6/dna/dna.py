import csv
import sys
import re
import argparse


STR_COUNTER = dict()


def main():

    db_path, sequence_path = parse()

    with open(db_path) as db_file, open(sequence_path) as sequence_file:
        db_reader = csv.DictReader(db_file)
        strs = set(db_reader.fieldnames) - {'name'}
        str_patterns = {str_: re.compile(rf'({str_})+') for str_ in strs}

        dna_sequence = sequence_file.read()

        for str_, pattern in str_patterns.items():
            longest = 0
            for match in pattern.finditer(dna_sequence):
                span = match.span()
                match_length = (span[1] - span[0]) // len(str_)
                longest = match_length if match_length > longest else longest
            STR_COUNTER[str_] = longest

        for row in db_reader:
            if all(int(row[str_]) == STR_COUNTER[str_] for str_ in strs):
                print(row['name'])
                sys.exit(0)
    print('No match')
    sys.exit(0)


def parse():
    parser = argparse.ArgumentParser(description='DNA program argument parser.')
    parser.add_argument('database', type=str,
                        help='File location of a file that contains STR DNA counts')
    parser.add_argument('sequence', type=str,
                        help='File location of a file containing DNA sequence')

    args = parser.parse_args()
    return args.database, args.sequence


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
