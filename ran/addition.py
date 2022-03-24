# List all files in the directory
import os
files = os.listdir()
# filter txt from files
txt_files = list(filter(lambda x: x.endswith('.txt'), files))
sorted_files = sorted(txt_files)

def add_numbers_in_file(fileName, outputFilePrefix):
    # Dictionary to store Key Value pairs
    initial_lines = []
    totals = {}
    # Print all lines from aFile
    with open(fileName) as f:
        # Add first 7 lines to initial_lines
        for i in range(7):
            initial_lines.append(f.readline())
        for line in f:
            # If line starts with number
            if line[0].isdigit():
                # split line by colon
                line = line.split(':')
                # Get the key
                key = line[0]
                # Get the value
                value = line[1]
                # Add key and value to totals
                if key in totals:
                    totals[key] += float(value)
                else:
                    totals[key] = float(value)

    # Modify initial_line line 5 and 6, replace one \t with 2 \t
    initial_lines[4] = initial_lines[4].replace('\t', '\t\t')
    initial_lines[5] = initial_lines[5].replace('\t', '\t\t')
    # Append initial_line, totals to outputFile
    outputFile = outputFilePrefix + file
    with open(outputFile, 'a') as f:
        f.writelines(initial_lines)
        # Add newline
        f.write('\n')
        for key, value in totals.items():
            f.write(key + ':\t\t' + str(value) + '\n')
        # Add 3 newlines
        f.write('\n' * 3)

    initial_lines = [] 
    totals = {} 



# Call add_numbers_in_file for each txt file
for file in sorted(txt_files):
    add_numbers_in_file(file, 'out/out')
