#include <iostream>
#include <string>

using namespace std;

void naiveMatch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
            j++;
        if (j == m) // use a bool to say if not found
            cout << "Pattern found at index " << i << endl;
    }
}

int main() {
    cout << "Enter searchspace text: ";
    string text; getline(cin, text);
    cout << "Enter pattern to match: ";
    string pattern; getline(cin, pattern);
    
    cout << "Searching... " << endl;
    naiveMatch(text, pattern);

    return 0;
}