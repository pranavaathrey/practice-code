#include <iostream>

using namespace std;

// TODO: learn what a Menacher is 
class Solution {
    string expandHere(string s, int i, int j) {
        while(i >= 0 && j < s.length() && s[i] == s[j]) {
            i--; j++;
        }   i++; j--;
        return s.substr(i, j - i + 1);
    }

    public:
    string longestPalindrome(string s) {
        if(s.length() <= 1) return s;
        string longestPalin = "";

        for(int i = 0; i < s.length(); i++) {
            string odd = expandHere(s, i, i);
            if(odd.length() > longestPalin.length())
                longestPalin = odd;
            string even = expandHere(s, i, i + 1);
            if(even.length() > longestPalin.length())
                longestPalin = even;
        }
        return longestPalin;
    }
};

int main() {
    Solution s;
    string a; cin >> a;
    cout << s.longestPalindrome(a);
    return 0;
}