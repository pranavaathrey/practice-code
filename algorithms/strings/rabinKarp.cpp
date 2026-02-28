#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define BASE 256

using namespace std;

int rabinKarp(const string& text, const string& pattern, int Q) {
    int n = text.length(), m = pattern.length();    
    int base = BASE;
    int h = 1;
    // h = pow(base, m-1) % Q
    for(int i = 0; i < m - 1; i++)
        h = (h * base) % Q;

    int pHash = 0;      // hash for pattern
    int tHash = 0;      // hash for text window
    // calculate initial hash values
    for(int i = 0; i < m; i++) {
        pHash = (base * pHash + pattern[i]) % Q;
        tHash = (base * tHash + text[i]) % Q;
    }

    // slide the pattern over text
    for(int i = 0; i <= n - m; i++) {
        if(pHash == tHash) {
            // potential match, check char-by-char
            bool match = true;
            for(int j = 0; j < m; j++) 
                if(text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            if(match) return i;
        }
        // calculate hash for proceeding text window
        if(i < n - m) {
            tHash = (base * (tHash - text[i] * h) 
                    + text[i + m]) % Q;
            if (tHash < 0) tHash = (tHash + Q); // ensure positive result
        }
    }
    return -1;
}

int main() {
    cout << "Enter searchspace text: ";
    string text; getline(cin, text);
    cout << "Enter pattern to match: ";
    string pattern; getline(cin, pattern);
    
    cout << "Searching... " << endl;
    int Q = 7919; // A large prime number
    int index = rabinKarp(text, pattern, Q);

    if(index != -1)
        cout << "Pattern found at index " << index << endl;    
    else
        cout << "Pattern not found :(" << endl;    
    return 0;
}