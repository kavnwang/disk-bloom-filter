#include "filter.cpp"
#include <iostream>

const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main() {
    BloomFilter bloomfilter("filter.dat",10000,10e-10);

    for(int i = 0;i<5000;i++) {
        string key = "";
        for(int j = 0;j<20;j++) {
            key += CHARACTERS[rand() % CHARACTERS.length()];
        }
        bloomfilter.Add(key);
    }

    bloomfilter.Add("a");
    bloomfilter.Add("b");
    bloomfilter.Add("c");
    bloomfilter.Add("d");

    if (bloomfilter.Contains("a")) cout << "Contains check for 'a' passed" << endl;
    if (bloomfilter.Contains("b")) cout << "Contains check for 'b' passed" << endl;
    if (bloomfilter.Contains("c")) cout << "Contains check for 'c' passed" << endl;
    if (!bloomfilter.Contains("e")) cout << "Contains check for 'e' passed" << endl;

    cout << "Filter Size: " << bloomfilter.Size() << std::endl;
    
    cout << "Elements Count: " << bloomfilter.Count() << std::endl;
    bloomfilter.Clear();
    return 0;
}
