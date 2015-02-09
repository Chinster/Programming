# Find a lowercase character surrounded by 3 uppercase characters on both sides
import re

target = open("equality.txt").read()

m = re.findall('[a-z][A-Z]{3}[a-z][A-Z]{3}[a-z]', target)
for each in m:
    print(each[4])
