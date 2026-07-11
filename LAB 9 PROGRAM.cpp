#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Get column order from key
vector<int> getOrder(string key)
{
    vector<pair<char,int>> temp;

    for(int i=0;i<key.length();i++)
        temp.push_back({key[i],i});

    sort(temp.begin(),temp.end());

    vector<int> order(key.length());

    for(int i=0;i<temp.size();i++)
        order[i]=temp[i].second;

    return order;
}

// Columnar Transposition Encryption
string encrypt(string text,string key)
{
    int cols=key.length();
    int rows=(text.length()+cols-1)/cols;

    while(text.length()<rows*cols)
        text+='X';

    vector<vector<char>> mat(rows,vector<char>(cols));

    int k=0;

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            mat[i][j]=text[k++];

    vector<int> order=getOrder(key);

    string cipher="";

    for(int x=0;x<cols;x++)
    {
        int col=order[x];

        for(int i=0;i<rows;i++)
            cipher+=mat[i][col];
    }

    return cipher;
}

// Columnar Transposition Decryption
string decrypt(string cipher,string key)
{
    int cols=key.length();
    int rows=cipher.length()/cols;

    vector<vector<char>> mat(rows,vector<char>(cols));

    vector<int> order=getOrder(key);

    int k=0;

    for(int x=0;x<cols;x++)
    {
        int col=order[x];

        for(int i=0;i<rows;i++)
            mat[i][col]=cipher[k++];
    }

    string text="";

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            text+=mat[i][j];

    while(!text.empty() && text.back()=='X')
        text.pop_back();

    return text;
}

int main()
{
    string plaintext,key1,key2;

    cout<<"Enter Plaintext: ";
    getline(cin,plaintext);

    cout<<"Enter First Key: ";
    cin>>key1;

    cout<<"Enter Second Key: ";
    cin>>key2;

    // Single Transposition
    auto start=high_resolution_clock::now();
    string single=encrypt(plaintext,key1);
    auto stop=high_resolution_clock::now();

    auto singleTime=
    duration_cast<microseconds>(stop-start).count();

    // Double Transposition
    start=high_resolution_clock::now();

    string first=encrypt(plaintext,key1);
    string second=encrypt(first,key2);

    stop=high_resolution_clock::now();

    auto doubleTime=
    duration_cast<microseconds>(stop-start).count();

    // Step-by-step Decryption
    string step1=decrypt(second,key2);
    string original=decrypt(step1,key1);

    cout<<"\n========== RESULT ==========\n";

    cout<<"Single Transposition : "<<single<<endl;

    cout<<"After First Key      : "<<first<<endl;

    cout<<"After Second Key     : "<<second<<endl;

    cout<<"\nStep 1 Decryption    : "<<step1<<endl;

    cout<<"Original Plaintext   : "<<original<<endl;

    cout<<"\nExecution Time\n";
    cout<<"Single : "<<singleTime<<" microseconds"<<endl;
    cout<<"Double : "<<doubleTime<<" microseconds"<<endl;

    cout<<"\nSecurity Comparison\n";
    cout<<"Single Transposition : Moderate Security"<<endl;
    cout<<"Double Transposition : Higher Security"<<endl;
    cout<<"Double Transposition produces more randomized ciphertext."<<endl;

    return 0;
}
