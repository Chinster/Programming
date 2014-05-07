def prob2():
	myString = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj"
	newString = ""
	for char in myString:
		if(char == " "):
			newString += " "
		else:
			newString += chr(ord(char)+2)
	print newString
prob2()
