# coding: utf-8
# flake8: noqa

# huffman algorhytm in python
# coded by Denes Gutai

print
print("##############################")
print("#                            #")
print("#     huffman algoritmus     #")
print("#                            #")
print("##############################")

# Input string to be encoded
print
string = raw_input("Írja be a kódolandó szöveget: ")
print
print("Kódolandó szöveg:")
print(string)
print


# STEP 1:
# Define each character's frequency of the string given

characters_frequency = {}

for x in string:
    if x in characters_frequency:
        characters_frequency[x] += 1
    else:
        characters_frequency[x] = 1


# STEP 2:
# Merge characters frequency to one end-node

# Define the node class
class Node:
    def __init__(self, freq, char=None):
        self.char = char
        self.left = None
        self.right = None
        self.freq = freq

    def __repr__(self):
        return repr((self.char, self.freq))

    def set_branches(self, node_1, node_2):
        self.left = node_1
        self.right = node_2
        self.freq = node_1.freq + node_2.freq

    def print_self(self):
        print(str(self.char) + " " + str(self.freq))

    def print_tree(self):
        if self.left is not None:
            self.left.print_tree()
        print(str(self.freq) + " " + str(self.char))
        if self.right is not None:
            self.right.print_tree()


# Create nodes based on the dictionary
nodes = []
for x in characters_frequency:
    nodes.append(Node(characters_frequency[x], x))

sorted_nodes = sorted(nodes, key=lambda node: node.freq)


# Loop while only one node is left
while len(sorted_nodes) >= 2:
    # sort nodes so the smallest frequency ones come first
    sorted_nodes = sorted(sorted_nodes, key=lambda node: node.freq)

    # merge the first two nodes two one and pop them out of the list
    node_1 = sorted_nodes.pop(0)
    node_2 = sorted_nodes.pop(0)

    # create the merged node and set it's branches to the popped nodes
    merged_node = Node(0)
    merged_node.set_branches(node_1, node_2)

    # add the merged node to the sorted_nodes list
    sorted_nodes.append(merged_node)


# STEP 3:
# Define codes looping through the tree

# Create blank dictionary for our codes
bit_dictionary = {}

# If a node contains a character add it and it's code to the dictionary
# Dig recursively the left and the right branch if they are not None


def shovel(node, received_char='', code=''):
    new_code = str(code) + str(received_char)
    if (node.char is not None):
        bit_dictionary[node.char] = new_code
    if (node.left is not None):
        shovel(node.left, '0', new_code)
    if(node.right is not None):
        shovel(node.right, '1', new_code)


# Start digging the character codes from the end-node
shovel(sorted_nodes[0])

# Print out the code table
print("Kódtábla:")
for x in characters_frequency:
    print("karakter: " + str(x) + "  gyakoriság: " +
          str(characters_frequency[x]) + "  bit kód: " + str(bit_dictionary[x]))
print

# STEP 4:
# Sum how many bits are necessary to code the string

bits = 0

for x in bit_dictionary:
    bit_length = len(bit_dictionary[x])
    bit_frequency = characters_frequency[x]
    bits += bit_length*bit_frequency

print(str(bits) + " biten kódolható a megadott szöveg")
print

# STEP 5:
# Code the string

code = ""
for x in string:
    code += bit_dictionary[x]

print("A szöveg kódja:")
print(str(code))
print

# STEP 6
# Decode coded string

code_snippet = ""
decoded_string = ""

# Return the character if the passed bits match a code in the dictionary
def search_character(bits):
    for x in bit_dictionary:
        if str(bit_dictionary[x]) == str(code_snippet):
            return str(x)
    return None


# Go through the code and add it's bit to the code_snippet:
# Set found_character variable the result of the search_character() function
# If found_character is not None clear code_snippet and add the character to the decoded string
for x in code:
    code_snippet += x
    found_character = search_character(code_snippet)
    if found_character is not None:
        decoded_string += found_character
        code_snippet = ""

print("Kódbol visszafejtett szöveg:")
print decoded_string
print
