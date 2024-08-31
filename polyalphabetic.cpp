#include <iostream>
using namespace std;

// Function to generate the key in a cyclic manner
string generateKey(string str, string key) {
    int strLength = str.length();
    int keyLength = key.length();
    
    // Repeat the key until it's the same length as the text
    for (int i = 0; key.length() < strLength; i++) {
        key += key[i % keyLength];
    }
    return key;
}

// Function to encrypt the plaintext
string encrypt(string str, string key) {
    string cipherText = "";

    for (int i = 0; i < str.length(); i++) {
        // Encrypt each character
        char x = (str[i] + key[i]) % 26;
        x += 'A';
        cipherText += x;
    }
    return cipherText;
}

// Function to decrypt the ciphertext
string decrypt(string cipherText, string key) {
    string origText = "";

    for (int i = 0; i < cipherText.length(); i++) {
        // Decrypt each character
        char x = (cipherText[i] - key[i] + 26) % 26;
        x += 'A';
        origText += x;
    }
    return origText;
}

int main() {
    string str = "HELLO";      // Plaintext
    string keyword = "KEY";    // Key

    string key = generateKey(str, keyword);
    string cipherText = encrypt(str, key);

    cout << "Ciphertext: " << cipherText << endl;

    string originalText = decrypt(cipherText, key);
    cout << "Original Text: " << originalText << endl;

    return 0;
}
