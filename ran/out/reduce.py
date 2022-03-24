import os
files = os.listdir()
# filter txt from files
txt_files = list(filter(lambda x: x.startswith('out'), files))
sorted_files = sorted(txt_files)

# A Dictionary variable to store Key: String, Value: List of integers
totals = {}

def addLineToTotals(line):
    splittedline = line.split(':')
    key = splittedline[0]
    value = splittedline[1].removeprefix('\t\t').removesuffix('\n')
    if key in totals:
        totals[key].append(value)
    else:
        totals[key] = [value]

def analyzeFile(file):
    with open(file) as f:
        # Skip first line
        f.readline()
        # Work on line 2 to 5
        for i in range(2, 7):
            line = f.readline()
            addLineToTotals(line)
        
        # Read the remaining lines
        for line in f:
            # If line starts with number
            if line[0].isdigit():
                # split line by colon
                splittedline = line.split(':')
                # Get the key
                key = splittedline[0]
                # Get the value
                value = splittedline[1].removeprefix('\t\t').removesuffix('\n')
                # Add key and value to totals
                if key in totals:
                    totals[key].append(value)
                else:
                    totals[key] = [value]
        

# run alalyzeFile for each file
for file in sorted_files:
    analyzeFile(file)

        # Print out values in totals
for key, values in totals.items():
    # print(key, values)
    # Save key, values in text file
    with open('reduced.txt', 'a') as f:
        valuesToWrite = '\t'.join(values)
        f.write(key + '\t' + valuesToWrite + '\n')
        # print(valuesToWrite)



