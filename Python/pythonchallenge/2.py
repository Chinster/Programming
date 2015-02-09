# Find rare characters in ocr.txt
target = open("ocr.txt").read()

def count_chars(string):
    wordcount = {}
    for x in string:
        if x in wordcount:
            wordcount[x] = wordcount[x] + 1
        else:
            wordcount[x] = 1
    return wordcount

count = count_chars(target)
print(count)
