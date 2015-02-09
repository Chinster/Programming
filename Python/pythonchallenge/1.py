# Performs a caesar cycle on a string
def caesarcycle(s):
    for c in s:
        if c.isalpha():
            print(chr(ord(c) + 2),end="")
        elif ord(c.lower()) >= 121: # y,z cycled
            print(chr(ord(c) - 24),end="")
        else:
            print(c, end="")

def make_trans(s):
    intab = "abcdefghijklmnopqrstuvwxyz"
    outtab = "cdefghijklmnopqrstuvwxyzab"
    translation = s.translate(str.maketrans(intab, outtab))
    print(translation)

s = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
#caesarcycle(s)
make_trans(s)
