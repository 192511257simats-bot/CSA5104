#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string text, key;

    cout << "Enter Plaintext: ";
    getline(cin, text);

    cout << "Enter Keyword: ";
    cin >> key;

    int cols = key.length();
    int rows = (text.length() + cols - 1) / cols;

    // Padding
    while (text.length() < rows * cols)
        text += 'X';

    // Original Matrix
    vector<vector<char>> mat(rows, vector<char>(cols));
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mat[i][j] = text[k++];

    // Generate Ranking (Handles duplicate letters)
    vector<pair<char, int>> temp;
    for (int i = 0; i < cols; i++)
        temp.push_back({key[i], i});

    sort(temp.begin(), temp.end());

    vector<int> rank(cols);

    for (int i = 0; i < cols; i++)
        rank[temp[i].second] = i + 1;

    cout << "\nKey Ranking:\n";
    for (int i = 0; i < cols; i++)
        cout << key[i] << "(" << rank[i] << ") ";
    cout << endl;

    // Display Original Matrix
    cout << "\nOriginal Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }

    // Encryption
    string cipher = "";

    cout << "\nPermuted Matrix:\n";

    for (int r = 1; r <= cols; r++) {
        int col;
        for (col = 0; col < cols; col++)
            if (rank[col] == r)
                break;

        for (int i = 0; i < rows; i++) {
            cout << mat[i][col] << " ";
            cipher += mat[i][col];
        }
        cout << endl;
    }

    cout << "\nCiphertext: " << cipher << endl;

    // Decryption
    vector<vector<char>> dec(rows, vector<char>(cols));
    k = 0;

    for (int r = 1; r <= cols; r++) {
        int col;
        for (col = 0; col < cols; col++)
            if (rank[col] == r)
                break;

        for (int i = 0; i < rows; i++)
            dec[i][col] = cipher[k++];
    }

    string plain = "";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            plain += dec[i][j];

    while (!plain.empty() && plain.back() == 'X')
        plain.pop_back();

    cout << "Decrypted Text: " << plain << endl;

    return 0;
}
