#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

int main() {
    string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Generate random substitution key
    srand(time(0));
    random_shuffle(key.begin(), key.end());

    cout << "Random Key: " << key << endl;

    string text;
    cout << "\nEnter Plaintext: ";
    getline(cin, text);

    string cipher = "";

    // Encryption
    for (char ch : text) {
        if (isalpha(ch)) {
            if (isupper(ch))
                cipher += key[ch - 'A'];
            else
                cipher += tolower(key[ch - 'a']);
        } else {
            cipher += ch;
        }
    }

    cout << "\nCiphertext: " << cipher << endl;

    // Frequency Analysis
    int freq[26] = {0};

    for (char ch : cipher) {
        if (isalpha(ch))
            freq[toupper(ch) - 'A']++;
    }

    cout << "\nLetter Frequencies:\n";
    for (int i = 0; i < 26; i++) {
        cout << char('A' + i) << " : " << freq[i] << endl;
    }

    // Top 3 frequent letters
    cout << "\nTop 3 Most Frequent Letters:\n";

    for (int k = 0; k < 3; k++) {
        int max = -1, index = -1;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > max) {
                max = freq[i];
                index = i;
            }
        }

        if (index != -1) {
            cout << char('A' + index) << " -> " << max << " times" << endl;
            freq[index] = -1; // Prevent selecting it again
        }
    }

    return 0;
}
