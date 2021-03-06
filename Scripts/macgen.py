#!/usr/bin/python
# macgen.py script to generate a MAC address for guest virtual machines
# For other methods see http://red.ht/1mVoPJo
import random
#
def randomMAC():
    mac = [ 0x00, 0x16, 0x3e,
        random.randint(0x00, 0x7f),
        random.randint(0x00, 0xff),
        random.randint(0x00, 0xff) ]
    return ':'.join(map(lambda x: "%02x" % x, mac))
#
print randomMAC()
