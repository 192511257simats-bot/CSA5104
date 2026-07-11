#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Encryption
string encrypt(string text, int key) {
    if (key == 1) return text;

    vector<string> rail(key);
    int row = 0;
    bool down = true;

    for (char ch : text) {
        rail[row] += ch;

        if (row == 0)
            down = true;
        else if (row == key - 1)
            down = false;

        row += down ? 1 : -1;
    }

    cout << "\nRail Matrix:\n";
    for (int i = 0; i < key; i++)
        cout << rail[i] << endl;

    string cipher = "";
    for (int i = 0; i < key; i++)
        cipher += rail[i];

    return cipher;
}

// Decryption
string decrypt(string cipher, int key) {
    if (key == 1) return cipher;

    int n = cipher.length();

    vector<vector<char>> rail(key, vector<char>(n, '\n'));

    bool down;
    int row = 0, col = 0;

    // Mark zigzag path
    down = false;
    for (int i = 0; i < n; i++) {
        if (row == 0 || row == key - 1)
            down = !down;

        rail[row][col++] = '*';
        row += down ? 1 : -1;
    }

    // Fill cipher letters
    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < n; j++)
            if (rail[i][j] == '*' && index < n)
                rail[i][j] = cipher[index++];

    // Read plaintext
    string result = "";
    row = 0;
    col = 0;
    down = false;

    for (int i = 0; i < n; i++) {
        if (row == 0 || row == key - 1)
            down = !down;

        result += rail[row][col++];
        row += down ? 1 : -1;
    }

    return result;
}

int main() {
    string text;

    cout << "Enter Plaintext: ";
    getline(cin, text);

    int rails;
    cout << "Enter Number of Rails: ";
    cin >> rails;

    string cipher = encrypt(text, rails);

    cout << "\nEncrypted Text: " << cipher << endl;

    string plain = decrypt(cipher, rails);

    cout << "Decrypted Text: " << plain << endl;

    cout << "\nTime Complexity Analysis\n";
    cout << "Encryption : O(n)\n";
    cout << "Decryption : O(n)\n";
    cout << "Space Complexity : O(n)\n";

    cout << "\nTry rails from 2 to 10 to observe different ciphertext structures.\n";

    return 0;
}
