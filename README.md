# 🔐 Classical Cipher Collection in C

This repository contains C implementations of **13 classical encryption and decryption algorithms**, often taught in cryptography and computer security courses. Each cipher represents foundational concepts in classical cryptography—ranging from substitution and transposition techniques to polyalphabetic and matrix-based approaches.

---

## 📜 List of Ciphers Implemented

1. **Caesar Cipher**  
   A monoalphabetic substitution cipher where each letter is shifted by a fixed number of places.

2. **Atbash Cipher**  
   Substitution cipher that maps each letter to its reverse in the alphabet (A ↔ Z, B ↔ Y, etc.).

3. **August Cipher**  
   A lesser-known polyalphabetic cipher using keyword-based shifting.

4. **Affine Cipher**  
   Applies a linear transformation (ax + b mod m) to the letters of the alphabet.

5. **Vigenère Cipher**  
   A polyalphabetic cipher using a keyword to determine letter shifts.

6. **Gronsfeld Cipher**  
   Similar to Vigenère but uses digits (0–9) as keys.

7. **Beaufort Cipher**  
   A Vigenère variant where decryption and encryption processes are reversed.

8. **Autokey Cipher (Running Key Cipher)**  
   Extends the key using the plaintext itself for encryption.

9. **N-Gram Cipher**  
   Encrypts based on groups of letters (bigrams, trigrams, etc.).

10. **Hill Cipher**  
    Uses matrix multiplication with modular arithmetic for encryption/decryption.

11. **Rail Fence Cipher**  
    A transposition cipher that writes characters in a zig-zag (fence-like) pattern.

12. **Route Cipher**  
    Writes the message in a matrix and reads it in a specific route (e.g., column-wise).

13. **Myszkowski Cipher**  
    A columnar transposition cipher using keys with repeating characters.

---

## 🛠️ How to Compile

Make sure you have GCC installed. Then run:

```bash
gcc -o ciphers main.c
