#include <iostream>
#include <string>
using namespace std;

int main() {
    string text, result;
    int key, choice;

    cout << "1. Encrypt\n2. Decrypt\n3. Brute Force\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore();
    cout << "Enter text: ";
    getline(cin, text);

    if (choice == 1) {
        cout << "Enter key: ";
        cin >> key;
        result = text;

        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                char base = isupper(text[i]) ? 'A' : 'a';
                result[i] = (text[i] - base + key) % 26 + base;
            }
        }
        cout << "Encrypted Text: " << result;
    }

    else if (choice == 2) {
        cout << "Enter key: ";
        cin >> key;
        result = text;

        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                char base = isupper(text[i]) ? 'A' : 'a';
                result[i] = (text[i] - base - key + 26) % 26 + base;
            }
        }
        cout << "Decrypted Text: " << result;
    }

    else if (choice == 3) {
        for (key = 1; key <= 25; key++) {
            result = text;
            for (int i = 0; i < text.length(); i++) {
                if (isalpha(text[i])) {
                    char base = isupper(text[i]) ? 'A' : 'a';
                    result[i] = (text[i] - base - key + 26) % 26 + base;
                }
            }
            cout << "Key " << key << ": " << result << endl;
        }
    }

    return 0;
}
