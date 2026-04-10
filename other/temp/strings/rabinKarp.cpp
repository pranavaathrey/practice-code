#include <iostream>
#include <string>

#define BASE 256

using namespace std;

int rabinKarp(const string& text, const string& pattern, int Q) {
    int n = text.length(), m = pattern.length();
    if (m == 0) return 0;
    if (m > n) return -1;
    int base = BASE;
    int h = 1;
    for(int i = 0; i < m - 1; i++)
        h = (h * base) % Q;

    int pHash = 0;
    int tHash = 0;
    for(int i = 0; i < m; i++) {
        pHash = (base * pHash + pattern[i]) % Q;
        tHash = (base * tHash + text[i]) % Q;
    }

    for(int i = 0; i <= n - m; i++) {
        if(pHash == tHash) {
            bool match = true;
            for(int j = 0; j < m; j++) 
                if(text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            if(match) return i;
        }
        if(i < n - m) {
            tHash = (base * (tHash - text[i] * h) + text[i + m]) % Q;
            if (tHash < 0) tHash = (tHash + Q);
        }
    }
    return -1;
}

int main() {
    string text, pattern;
    if (!getline(cin, text)) return 0;
    if (!getline(cin, pattern)) return 0;
    int Q = 7919;
    cout << rabinKarp(text, pattern, Q) << "\n";
    return 0;
}