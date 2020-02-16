"""Első gyakorlat.

- Caesar kódolás
- Vigenére kódolás
"""


# 1.
# Caesar kódolás
# Szöveg betűihez az x-edik következő betűt adja.


class Caesar():
    """Class to encode and decode Caesar code."""

    def __init__(self, shift=1):
        """Initialize class with a shift param."""
        self.shift = shift

    def encode(self, text):
        """Encode text using Caesar method."""
        return ''.join([chr(ord(c)+self.shift) for c in text])

    def decode(self, text):
        """Decode encoded text using Caesar method."""
        return ''.join([chr(ord(c)-self.shift) for c in text])


# Define Caesar encoding class with the shift
caesar = Caesar(5)

# Encode string
encoded = caesar.encode('Encode me!')
print(f'Caesar encoded text: {encoded}')

# Decode string
decoded = caesar.decode(encoded)
print(f'Caesar decoded text: {decoded}')

# 2.
# Vigenére kódolás
# Kisebb szórészletet húzunk egy egész szövegre
# és a betűk "összege" lesz a titkosított szöveg


class Vigenere():
    """Class to encode and decode Vigenere code."""

    def __init__(self, keyword):
        """Initialize class with a shift param."""
        self.keyword = keyword

    def encode(self, text):
        """Encode text using Caesar method."""
        encoded_chars = []
        for index, c in enumerate(text):
            char_to_shift_with = self.keyword[index % len(self.keyword)]
            encoded_chars.append(ord(c)+ord(char_to_shift_with))
        return ''.join([chr(c) for c in encoded_chars])

    def decode(self, text):
        """Decode encoded text using Caesar method."""
        decoded_chars = []
        for index, c in enumerate(text):
            char_to_shift_with = self.keyword[index % len(self.keyword)]
            decoded_chars.append(ord(c)-ord(char_to_shift_with))
        return ''.join([chr(c) for c in decoded_chars])


# Define Vigenere encoding class with the shift
vigenere = Vigenere('abc')

# Encode string
encoded = vigenere.encode('Encode me!')
print(f'Vigenere encoded text: {encoded}')

# Encode string
decoded = vigenere.decode(encoded)
print(f'Vigenere decoded text: {decoded}')
