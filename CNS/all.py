# Cipher Demonstrations in Python

import numpy as np

# 1) Caesar Cipher
def caesar_encrypt(text, shift):
    result = ""
    for char in text:
        if char.isalpha():
            base = 'A' if char.isupper() else 'a'
            result += chr((ord(char) - ord(base) + shift) % 26 + ord(base))
        else:
            result += char
    return result

def caesar_decrypt(cipher, shift):
    return caesar_encrypt(cipher, -shift)


# 2) Vigenère Cipher
def vigenere_encrypt(text, key):
    key = key.upper()
    result = ""
    j = 0
    for char in text:
        if char.isalpha():
            shift = ord(key[j % len(key)]) - ord('A')
            base = 'A' if char.isupper() else 'a'
            result += chr((ord(char) - ord(base) + shift) % 26 + ord(base))
            j += 1
        else:
            result += char
    return result

def vigenere_decrypt(cipher, key):
    key = key.upper()
    result = ""
    j = 0
    for char in cipher:
        if char.isalpha():
            shift = ord(key[j % len(key)]) - ord('A')
            base = 'A' if char.isupper() else 'a'
            result += chr((ord(char) - ord(base) - shift) % 26 + ord(base))
            j += 1
        else:
            result += char
    return result


# 3) Playfair Cipher (simplified: assumes input is even length, no J)
def generate_playfair_matrix(key):
    key = key.upper().replace("J", "I")
    matrix = []
    used = set()
    for c in key + "ABCDEFGHIKLMNOPQRSTUVWXYZ":
        if c not in used:
            matrix.append(c)
            used.add(c)
    return [matrix[i:i+5] for i in range(0, 25, 5)]

def find_pos(matrix, c):
    if c == 'J': c = 'I'
    for r in range(5):
        for c2 in range(5):
            if matrix[r][c2] == c:
                return r, c2

def playfair_process(text, matrix, encrypt=True):
    text = text.upper().replace("J", "I")
    result = ""
    step = 1 if encrypt else -1
    for i in range(0, len(text), 2):
        r1, c1 = find_pos(matrix, text[i])
        r2, c2 = find_pos(matrix, text[i+1])
        if r1 == r2:  # same row
            result += matrix[r1][(c1 + step) % 5]
            result += matrix[r2][(c2 + step) % 5]
        elif c1 == c2:  # same column
            result += matrix[(r1 + step) % 5][c1]
            result += matrix[(r2 + step) % 5][c2]
        else:  # rectangle
            result += matrix[r1][c2]
            result += matrix[r2][c1]
    return result


# 4) Hill Cipher (2x2 matrix example)
def hill_encrypt(text, key_matrix):
    text = text.upper().replace(" ", "")
    while len(text) % 2 != 0:
        text += "X"
    result = ""
    for i in range(0, len(text), 2):
        vec = np.array([ord(text[i])-65, ord(text[i+1])-65])
        prod = np.dot(key_matrix, vec) % 26
        result += "".join(chr(p+65) for p in prod)
    return result

def hill_decrypt(cipher, key_matrix):
    det = int(round(np.linalg.det(key_matrix)))
    det_inv = pow(det % 26, -1, 26)
    adj = np.round(det * np.linalg.inv(key_matrix)).astype(int) % 26
    inv_matrix = (det_inv * adj) % 26
    result = ""
    for i in range(0, len(cipher), 2):
        vec = np.array([ord(cipher[i])-65, ord(cipher[i+1])-65])
        prod = np.dot(inv_matrix, vec) % 26
        result += "".join(chr(int(p)+65) for p in prod)
    return result


# 5) Vernam Cipher (XOR mod 26 version)
def vernam_encrypt(text, key):
    text, key = text.upper(), key.upper()
    result = ""
    for t, k in zip(text, key):
        if t.isalpha():
            result += chr(((ord(t)-65) ^ (ord(k)-65)) % 26 + 65)
        else:
            result += t
    return result

def vernam_decrypt(cipher, key):
    return vernam_encrypt(cipher, key)  # same as encrypt


# 6) Transposition Cipher (Columnar with numeric key)
def transposition_encrypt(text, key_order):
    n = len(key_order)
    text = text.upper().replace(" ", "")
    while len(text) % n != 0:
        text += "X"
    grid = [text[i:i+n] for i in range(0, len(text), n)]
    cipher = ""
    for k in key_order:
        cipher += "".join(row[k] for row in grid)
    return cipher

def transposition_decrypt(cipher, key_order):
    n = len(key_order)
    rows = len(cipher)//n
    grid = [[""]*n for _ in range(rows)]
    idx = 0
    for k in key_order:
        for r in range(rows):
            grid[r][k] = cipher[idx]
            idx += 1
    return "".join("".join(row) for row in grid)


# 7) Rail Fence Cipher
def railfence_encrypt(text, rails):
    text = text.replace(" ", "")
    fence = [[] for _ in range(rails)]
    rail, step = 0, 1
    for c in text:
        fence[rail].append(c)
        rail += step
        if rail == 0 or rail == rails-1:
            step = -step
    return "".join("".join(row) for row in fence)

def railfence_decrypt(cipher, rails):
    pattern = list(range(rails)) + list(range(rails-2,0,-1))
    idxs = [pattern[i % len(pattern)] for i in range(len(cipher))]
    rail_counts = [idxs.count(r) for r in range(rails)]
    rails_text = []
    i = 0
    for count in rail_counts:
        rails_text.append(list(cipher[i:i+count]))
        i += count
    result, pos = "", [0]*rails
    for r in idxs:
        result += rails_text[r][pos[r]]
        pos[r] += 1
    return result


# --- DEMO ---
if __name__ == "__main__":
    print("=== Cipher Demonstration ===")
    
    # Caesar
    print("\nCaesar:")
    text, shift = "Attack at dawn!", 3
    enc = caesar_encrypt(text, shift)
    print("Enc:", enc)
    print("Dec:", caesar_decrypt(enc, shift))
    
    # Vigenere
    print("\nVigenere:")
    text, key = "ATTACKATDAWN", "LEMON"
    enc = vigenere_encrypt(text, key)
    print("Enc:", enc)
    print("Dec:", vigenere_decrypt(enc, key))
    
    # Playfair
    print("\nPlayfair:")
    matrix = generate_playfair_matrix("PLAYFAIR EXAMPLE")
    text = "HIDETHEGOLDINTHETREESTUMP"
    enc = playfair_process(text, matrix, True)
    print("Enc:", enc)
    print("Dec:", playfair_process(enc, matrix, False))
    
    # Hill (2x2)
    print("\nHill:")
    key_matrix = np.array([[3,3],[2,5]])
    text = "HI"
    enc = hill_encrypt(text, key_matrix)
    print("Enc:", enc)
    print("Dec:", hill_decrypt(enc, key_matrix))
    
    # Vernam
    print("\nVernam:")
    text, key = "HELLO", "XMCKL"
    enc = vernam_encrypt(text, key)
    print("Enc:", enc)
    print("Dec:", vernam_decrypt(enc, key))
    
    # Transposition
    print("\nTransposition:")
    text, key_order = "HELLOWORLD", [2,0,1]  # column order
    enc = transposition_encrypt(text, key_order)
    print("Enc:", enc)
    print("Dec:", transposition_decrypt(enc, key_order))
    
    # Rail Fence
    print("\nRail Fence:")
    text, rails = "HELLOWORLD", 3
    enc = railfence_encrypt(text, rails)
    print("Enc:", enc)
    print("Dec:", railfence_decrypt(enc, rails))
