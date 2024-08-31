#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Helper function to remove non-alphabetic characters and replace 'J' with 'I'
string parseString(const string& input) {
    string parsed = "";
    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];
        if (isalpha(ch)) {
            parsed += toupper(ch);
        }
    }
    replace(parsed.begin(), parsed.end(), 'J', 'I');
    return parsed;
}

// Function to create the Playfair cipher key table
vector<vector<char> > createCipherTable(const string& key) {
    vector<vector<char> > table(5, vector<char>(5, ' '));
    string keyString = parseString(key) + "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string usedChars = "";

    int row = 0, col = 0;
    for (size_t i = 0; i < keyString.size(); ++i) {
        char ch = keyString[i];
        if (usedChars.find(ch) == string::npos) {
            usedChars += ch;
            table[row][col] = ch;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    return table;
}

// Helper function to get the position of a character in the table
pair<int, int> getCharPosition(const vector<vector<char> >& table, char ch) {
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (table[row][col] == ch) {
                return make_pair(row, col);
            }
        }
    }
    return make_pair(-1, -1); // Should not reach here if character is in table
}

// Function to encode a digraph using the Playfair cipher rules
string encodeDigraph(const vector<vector<char> >& table, char a, char b) {
    pair<int, int> posA = getCharPosition(table, a);
    pair<int, int> posB = getCharPosition(table, b);

    int r1 = posA.first, c1 = posA.second;
    int r2 = posB.first, c2 = posB.second;

    if (r1 == r2) {
        c1 = (c1 + 1) % 5;
        c2 = (c2 + 1) % 5;
    } else if (c1 == c2) {
        r1 = (r1 + 1) % 5;
        r2 = (r2 + 1) % 5;
    } else {
        swap(c1, c2);
    }

    return string(1, table[r1][c1]) + table[r2][c2];
}

// Function to decode a digraph using the Playfair cipher rules
string decodeDigraph(const vector<vector<char> >& table, char a, char b) {
    pair<int, int> posA = getCharPosition(table, a);
    pair<int, int> posB = getCharPosition(table, b);

    int r1 = posA.first, c1 = posA.second;
    int r2 = posB.first, c2 = posB.second;

    if (r1 == r2) {
        c1 = (c1 + 4) % 5;
        c2 = (c2 + 4) % 5;
    } else if (c1 == c2) {
        r1 = (r1 + 4) % 5;
        r2 = (r2 + 4) % 5;
    } else {
        swap(c1, c2);
    }

    return string(1, table[r1][c1]) + table[r2][c2];
}

// Function to prepare the plaintext by splitting into digraphs and replacing duplicates
string prepareText(const string& text) {
    string prepared = parseString(text);
    string result = "";

    for (size_t i = 0; i < prepared.size(); i += 2) {
        if (i + 1 == prepared.size()) {
            result += prepared[i];
            result += 'X';
        } else if (prepared[i] == prepared[i + 1]) {
            result += prepared[i];
            result += 'X';
            i--;
        } else {
            result += prepared[i];
            result += prepared[i + 1];
        }
    }
    return result;
}

// Function to encrypt a message
string encrypt(const vector<vector<char> >& table, const string& text) {
    string preparedText = prepareText(text);
    string encrypted = "";

    for (size_t i = 0; i < preparedText.size(); i += 2) {
        encrypted += encodeDigraph(table, preparedText[i], preparedText[i + 1]);
    }

    return encrypted;
}

// Function to decrypt a message
string decrypt(const vector<vector<char> >& table, const string& text) {
    string decrypted = "";

    for (size_t i = 0; i < text.size(); i += 2) {
        decrypted += decodeDigraph(table, text[i], text[i + 1]);
    }

    return decrypted;
}

int main() {
    string key, plaintext;

    cout << "Enter the key for Playfair cipher: ";
    getline(cin, key);

    vector<vector<char> > table = createCipherTable(key);

    cout << "Enter the plaintext to be encipher: ";
    getline(cin, plaintext);

    string encrypted = encrypt(table, plaintext);
    string decrypted = decrypt(table, encrypted);

    cout << "Playfair Cipher Key Matrix:" << endl;
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            cout << table[row][col] << " ";
        }
        cout << endl;
    }

    cout << "Encrypted Message: " << encrypted << endl;
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}
