# coding: utf-8
# flake8: noqa

# Bitvektor tömörítés
# coded by Denes Gutai

print
print("------------------------------------------")
print("||          Bitvektor tömörítés         ||")
print("------------------------------------------")
print


# A kódolandó bitvektor
bitvektor = "10000000000000000000000000000000000000000000010000000101"


print("A kódolandó bitvektor:")
print(bitvektor)
print

if ('1' not in bitvektor):
    print "A bitvektor üres"
    exit()


encoded = ""
snippet = ""

for x in bitvektor:
    if snippet == "" and x == '1':
        encoded += '00'
    elif x == '0':
        snippet += x
    elif x == '1':

        binary_part = str(bin(len(snippet))[2:])
        encoded_start = "".join("1" * (len(binary_part)-1))
        encoded_start += "0"

        encoded += encoded_start
        encoded += binary_part
        snippet = ""

print("A tömörített bitsorozat:")
print(encoded)
print


# Visszafejtés

snippet = ""
decoded = ""

encoded_list = list(encoded)

while(len(encoded_list) != 0):
    actual = encoded_list.pop(0)
    if(snippet == "0"):
        if(actual == "0"):
            decoded += "1"
            snippet = ""
        if(actual == "1"):
            decoded += "01"
            snippet = ""
    elif(len(snippet) > 0):
        snippet += actual
        if(actual == "0"):
            binary_part = ""
            for x in range(0, len(snippet)):
                binary_part += encoded_list.pop(0)
            number_of_zeros = int(binary_part, 2)
            decoded += "".join('0' * number_of_zeros)
            decoded += "1"
            snippet = ""
    else:
        snippet += actual

print decoded
