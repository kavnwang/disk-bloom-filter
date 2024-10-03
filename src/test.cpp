#include "filter.cpp"
#include <iostream>

const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main() {
    BloomFilter bf("filter.dat",10000,10e-10);

    for(int i = 0;i<5000;i++) {
        string key = "";
        for(int j = 0;j<20;j++) {
            key += CHARACTERS[rand() % CHARACTERS.length()];
        }
        bf.Add(key);
    }

    bf.Add("a");
    bf.Add("b");
    bf.Add("c");
    bf.Add("d");

    if (bf.Contains("a")) cout << "Contains check for 'a' passed" << endl;
    if (bf.Contains("b")) cout << "Contains check for 'b' passed" << endl;
    if (bf.Contains("c")) cout << "Contains check for 'c' passed" << endl;
    if (!bf.Contains("e")) cout << "Contains check for 'e' passed" << endl;

    cout << "Filter Size: " << bf.Size() << std::endl;
    
    cout << "Elements Count: " << bf.Count() << std::endl;

    bf.Clear();

    return 0;
}
