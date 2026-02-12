#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
    private:
    bool isVowel(char ch) {
        ch = tolower(ch);
        if(ch == 'a' || ch == 'e' || ch == 'i' 
        || ch == 'o' || ch == 'u')
            return true;
        return false;
    }
    public:
    string sortVowels(string s) {
        string vowels = "";
        for(char ch: s)
            if(isVowel(ch)) vowels += ch;
        sort(vowels.begin(), vowels.end());

        for(int i = 0, j = 0; i < s.length(); i++)
            if(isVowel(s[i])) {
                s[i] = vowels[j];
                j++;
            }
        return s;
    }
};

int main() {
    Solution s;
    string input; cin >> input;
    cout << s.sortVowels(input);
    return 0;
}