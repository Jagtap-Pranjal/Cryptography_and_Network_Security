#include <iostream> 
#include <string>   

using namespace std; 

// Function to encrypt the string using Caesar Cipher
string caesarCipher(string text, int s) {
    string result = ""; // Initialize an empty string to store the result

    // Traverse the input text
    for (int i = 0; i < text.length(); i++) {
        // Check if the character is an uppercase letter
        if (isupper(text[i])) {
            // Encrypt uppercase letters and append to result
            result += char(int(text[i] + s - 65) % 26 + 65);
        }
        // Check if the character is a lowercase letter
        else if (islower(text[i])) {
            // Encrypt lowercase letters and append to result
            result += char(int(text[i] + s - 97) % 26 + 97);
        }
        // If the character is neither uppercase nor lowercase
        else {
            // Append the character as it is to the result
            result += text[i];
        }
    }

    // Return the encrypted string
    return result;
}

int main() {
    string text; // Declare a variable to hold the input text
    int s;       // Declare a variable to hold the shift value

    // Prompt the user to enter the text to be encrypted
    cout << "Enter the text to be encrypted: ";
    getline(cin, text); // Read the entire line of text including spaces

    // Prompt the user to enter the shift value
    cout << "Enter the shift value: ";
    cin >> s; // Read the shift value

    // Display the encrypted text
    cout << "Encrypted Text: " << caesarCipher(text, s) << endl;

    return 0; // Return 0 to indicate successful program termination
}
