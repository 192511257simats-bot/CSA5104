#include <iostream>
#include <string>
using namespace std;

// Encryption
string encrypt(string text, string key) {
    string cipher = "";
    int j = 0;

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char ch = toupper(text[i]);
            cipher += char(((ch - 'A') + (toupper(key[j % key.length()]) - 'A')) % 26 + 'A');
            j++;
        } else {
            cipher += text[i];
        }
    }
    return cipher;
}

// Decryption
string decrypt(string cipher, string key) {
    string text = "";
    int j = 0;

    for (int i = 0; i < cipher.length(); i++) {
        if (isalpha(cipher[i])) {
            char ch = toupper(cipher[i]);
            text += char(((ch - 'A') - (toupper(key[j % key.length()]) - 'A') + 26) % 26 + 'A');
            j++;
        } else {
            text += cipher[i];
        }
    }
    return text;
}

// Basic Kasiski Approach
void kasiski(string cipher) {
    cout << "\nRepeated 3-letter sequences:\n";

    bool found = false;

    for (int i = 0; i < cipher.length() - 2; i++) {
        string s = cipher.substr(i, 3);

        for (int j = i + 3; j < cipher.length() - 2; j++) {
            if (s == cipher.substr(j, 3)) {
                cout << s << " found at " << i << " and " << j;
                cout << "  Distance = " << j - i << endl;
                found = true;
            }
        }
    }

    if (!found)
        cout << "No repeated sequences found.\n";
}

int main() {
    string plaintext, keyword;

    cout << "Enter Plaintext: ";
    getline(cin, plaintext);

    cout << "Enter Keyword: ";
    cin >> keyword;

    string cipher = encrypt(plaintext, keyword);

    cout << "\nEncrypted Text: " << cipher << endl;

    cout << "Decrypted Text: " << decrypt(cipher, keyword) << endl;

    kasiski(cipher);

    return 0;
}
