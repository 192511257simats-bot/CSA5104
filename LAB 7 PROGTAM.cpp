#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string text;
    int key;
    char pad;

    cout << "Enter Plaintext: ";
    getline(cin, text);

    cout << "Enter Key Length: ";
    cin >> key;

    cout << "Enter Padding Character: ";
    cin >> pad;

    // Calculate rows
    int rows = text.length() / key;
    if (text.length() % key != 0)
        rows++;

    // Add padding
    while (text.length() < rows * key)
        text += pad;

    vector<vector<char>> mat(rows, vector<char>(key));

    // Fill matrix row-wise
    int index = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < key; j++)
            mat[i][j] = text[index++];

    // Display matrix
    cout << "\nMatrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }

    // Encryption (column-wise)
    string cipher = "";
    for (int j = 0; j < key; j++)
        for (int i = 0; i < rows; i++)
            cipher += mat[i][j];

    cout << "\nCiphertext: " << cipher << endl;

    // Decryption
    vector<vector<char>> dec(rows, vector<char>(key));
    index = 0;

    for (int j = 0; j < key; j++)
        for (int i = 0; i < rows; i++)
            dec[i][j] = cipher[index++];

    string plain = "";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < key; j++)
            plain += dec[i][j];

    // Remove padding
    while (!plain.empty() && plain.back() == pad)
        plain.pop_back();

    cout << "Decrypted Text: " << plain << endl;

    return 0;
}
