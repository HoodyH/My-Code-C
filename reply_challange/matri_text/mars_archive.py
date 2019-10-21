import difflib
import os

dir = 'MarsArchives'
f1 = open('MarsArchives/2600-0.txt', 'r')
f2 = open('MarsArchives/2600-0 (1).txt', 'r')

data_file_1 = f1.read()
data_file_2 = f2.read()

cases = [(data_file_1, data_file_2), ('', '')]

for a, b in cases:
    # print('{} => {}'.format(a, b))
    for i, s in enumerate(difflib.ndiff(a, b)):
        if s[0] == ' ':
            continue
        elif s[0] == '-':
            print(u'Delete "{}" from position {}'.format(s[-1], i))
        elif s[0] == '+':
            print(u'Add "{}" to position {}'.format(s[-1], i))
    print()
"""
for line1 in f1:
    for line2 in f2:
        if line1 == line2:
            print("SAME\n")
        else:
            pass
            # print(line1 + line2)
"""
f1.close()
f2.close()
