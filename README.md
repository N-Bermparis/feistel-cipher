# Feistel Cipher - Educational Reference Implementation  
[![Language: C](https://img.shields.io/badge/language-C-blue.svg)]()
[![Cryptography](https://img.shields.io/badge/topic-cryptography-purple.svg)]()
[![Block Cipher](https://img.shields.io/badge/category-block--cipher-green.svg)]()
[![License: MIT](https://img.shields.io/badge/license-MIT-yellow.svg)]()

---

## 1. Overview

This repository provides a minimal, academic-oriented implementation of a **Feistel block cipher** in the C programming language.  
Its purpose is strictly educational: to illustrate how Feistel networks operate mathematically and programmatically.

The repository contains:

- `feistel.c` - A compact 4-round Feistel cipher implementation in C  
- `index.html` - A simple academic explanation of Feistel networks, including the mathematical formulation and diagram
---

## 2. The Feistel Structure (Mathematical Summary)

![Feistel Cipher Diagram](https://upload.wikimedia.org/wikipedia/commons/f/fa/Feistel_cipher_diagram_en.svg)

A Feistel cipher divides the input block into two halves:

M = (L0, R0)

For each round \(i\), with subkey \(K_i\), the transformation is:

L_{i+1} = R_i
R_{i+1} = L_i XOR F(R_i, K_i)

This process:

- Does **not** require the round function \(F\) to be invertible  
- Ensures that encryption and decryption share the **same structure**  
- Allows decryption simply by reversing key order  

A full mathematical walkthrough and diagram are available in `index.html`.

---

## 3. Round Function \(F\)

The round function may be any transformation, such as:

- XOR operations  
- Modular addition  
- S-box substitutions  
- Bit permutations  

In this educational implementation, the round function is:

```c
F(r, k) = r ^ k;
