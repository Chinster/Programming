import os
from sys import argv
import urllib.request
import threading

filename = ""
url = ""
content_length = 0

def argvparse():
    argc = len(argv)
    if argc < 2 or argc > 3:
        print("Usage: split-dl URL [SEGMENTS]")
        quit()

# Modify globals with target file info
def gen_info():
    global file_name, url, content_length, segments

    url = argv[1]
    file_name = url.split('/')[-1]
    req = urllib.request.Request(argv[1])
    with urllib.request.urlopen(req) as f:
        meta = f.info()
        content_length = int(meta.get("Content-Length"))

# Reads a range of bytes from the url in argv[1]
def download_chunk(offset, size, label):
    tmpfile = open("/tmp/" + file_name + str(label), "wb");

    req = urllib.request.Request(url)
    req.add_header('Range', 'bytes=' + str(offset) + '-' + str(offset + size))
    with urllib.request.urlopen(req) as f:
        tmpfile.write(f.read())

    tmpfile.close()

# Creates an n array filled with downloader threads, where n is segments
def create_threads(segments):
    odd = content_length % 2 != 0

    array = [None] * segments
    segment = content_length // segments
    for i in range(segments):
        start = segment * i + i

        # Ensure the last byte is grabbed if odd
        if odd and i == segments - 1:
            segment += 1

        array[i] = threading.Thread(target = download_chunk,
                                    args = (start, segment, i))
    return array

def main():
    argvparse()
    gen_info()

    segments = 2
    if len(argv) == 3:
        segments = int(argv[2])
    threads = create_threads(segments)

    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()

    # concat and remove
    for i in range(segments):
        tmp_name = "/tmp/" + file_name + str(i)
        os.system("cat " + tmp_name  + " >> " + file_name)
        os.remove(tmp_name)

main()
