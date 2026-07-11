#include <iostream>
#include <string>
#include <map>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Caesar Cipher
string caesar(string text, int shift)
{
    string result = "";
    for(char c : text)
    {
        if(isalpha(c))
            result += char((toupper(c)-'A'+shift)%26+'A');
    }
    return result;
}

// Monoalphabetic Cipher
string monoalphabetic(string text, string key)
{
    string result="";
    for(char c:text)
    {
        if(isalpha(c))
            result += key[toupper(c)-'A'];
    }
    return result;
}

// Vigenere Cipher
string vigenere(string text,string key)
{
    string result="";
    int j=0;

    for(char c:text)
    {
        if(isalpha(c))
        {
            int shift=toupper(key[j%key.length()])-'A';
            result += char((toupper(c)-'A'+shift)%26+'A');
            j++;
        }
    }
    return result;
}

// Hill Cipher (2x2)
string hillCipher(string text)
{
    int key[2][2]={{3,3},{2,5}};

    if(text.length()%2!=0)
        text+='X';

    string result="";

    for(int i=0;i<text.length();i+=2)
    {
        int a=text[i]-'A';
        int b=text[i+1]-'A';

        int c1=(key[0][0]*a+key[0][1]*b)%26;
        int c2=(key[1][0]*a+key[1][1]*b)%26;

        result+=char(c1+'A');
        result+=char(c2+'A');
    }

    return result;
}

// Frequency Distribution
void frequency(string text)
{
    map<char,int> freq;

    for(char c:text)
        freq[c]++;

    for(auto x:freq)
        cout<<x.first<<":"<<x.second<<" ";
}

// Repeated Letter Count
int repeatedLetters(string text)
{
    map<char,int> m;
    int count=0;

    for(char c:text)
    {
        m[c]++;
        if(m[c]==2)
            count++;
    }
    return count;
}

int main()
{
    string plaintext;

    cout<<"Enter Plaintext (UPPERCASE): ";
    cin>>plaintext;

    string monoKey="QWERTYUIOPASDFGHJKLZXCVBNM";
    string vigKey="KEY";

    string c1,c2,c3,c4;

    auto start=high_resolution_clock::now();
    c1=caesar(plaintext,3);
    auto stop=high_resolution_clock::now();
    auto t1=duration_cast<nanoseconds>(stop-start).count();

    start=high_resolution_clock::now();
    c2=monoalphabetic(plaintext,monoKey);
    stop=high_resolution_clock::now();
    auto t2=duration_cast<nanoseconds>(stop-start).count();

    start=high_resolution_clock::now();
    c3=vigenere(plaintext,vigKey);
    stop=high_resolution_clock::now();
    auto t3=duration_cast<nanoseconds>(stop-start).count();

    start=high_resolution_clock::now();
    c4=hillCipher(plaintext);
    stop=high_resolution_clock::now();
    auto t4=duration_cast<nanoseconds>(stop-start).count();

    cout<<"\n================ Comparative Security Analysis ================\n";

    cout<<"\n---------------------------------------------------------------\n";
    cout<<"Cipher\t\tCiphertext\tRepeated\tTime(ns)\n";
    cout<<"---------------------------------------------------------------\n";

    cout<<"Caesar\t\t"<<c1<<"\t\t"<<repeatedLetters(c1)<<"\t\t"<<t1<<endl;
    cout<<"Monoalpha\t"<<c2<<"\t\t"<<repeatedLetters(c2)<<"\t\t"<<t2<<endl;
    cout<<"Vigenere\t"<<c3<<"\t\t"<<repeatedLetters(c3)<<"\t\t"<<t3<<endl;
    cout<<"Hill\t\t"<<c4<<"\t\t"<<repeatedLetters(c4)<<"\t\t"<<t4<<endl;

    cout<<"\n================ Frequency Distribution ================\n";

    cout<<"\nCaesar : ";
    frequency(c1);

    cout<<"\nMonoalphabetic : ";
    frequency(c2);

    cout<<"\nVigenere : ";
    frequency(c3);

    cout<<"\nHill : ";
    frequency(c4);

    cout<<"\n\n================ Ciphertext Pattern Analysis ================\n";

    cout<<"Caesar        : Fixed shift of every letter.\n";
    cout<<"Monoalphabetic: One-to-one substitution using fixed alphabet.\n";
    cout<<"Vigenere      : Polyalphabetic substitution using keyword.\n";
    cout<<"Hill          : Matrix-based encryption, letters encrypted in pairs.\n";

    return 0;
}
