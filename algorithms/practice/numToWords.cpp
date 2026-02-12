#include <iostream>

using namespace std;

// elegant
class Solution {
    inline static const string digits[] = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    inline static const string teens[] = {
        "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    inline static const string tens[] = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        return convert(num).substr(1);
    }

    private:
    string convert(int num) {
        if (num >= 1000000000) return convert(num / 1000000000) + " Billion" + convert(num % 1000000000);
        if (num >= 1000000)    return convert(num / 1000000) + " Million" + convert(num % 1000000);
        if (num >= 1000)       return convert(num / 1000) + " Thousand" + convert(num % 1000);
        if (num >= 100)        return convert(num / 100) + " Hundred" + convert(num % 100);
        if (num >= 20)         return " " + tens[num / 10] + convert(num % 10);
        if (num >= 10)         return " " + teens[num - 10];
        if (num >= 1)          return " " + digits[num];
        return "";
    }
};

// ugly
class uggoSolution {
    private:
    string addWord(string &word, string newWord) {
        if(newWord.empty()) return word;
        if(!word.empty()) word += " ";
        return word += newWord;
    }
    public:
    string numberToWords(int num) {
        static const string digits[] = {"", "One", "Two", "Three", 
            "Four", "Five", "Six", "Seven", "Eight", "Nine"};

        static const string teens[] = {"Nineteen", "Eighteen", "Seventeen",
            "Sixteen", "Fifteen", "Fourteen", "Thirteen", "Twelve", "Eleven", "Ten"};
        static const int teenints[] = {19, 18, 17, 16, 15, 14, 13, 12, 11, 10};

        static const string tens[] = {"Ninety", "Eighty", "Seventy", "Sixty", 
                        "Fifty", "Forty", "Thirty", "Twenty"};
        static const int tenints[] = {90, 80, 70, 60, 50, 40, 30, 20};

        static const string scale[] = {"Billion", "Million", "Thousand", "Hundred"};
        static const int scalints[] = {1000000000, 1000000, 1000, 100};

        if(num == 0) return "Zero";

        string words = "";
        for(int i = 0; i < 4; i++) {
            int quo = num / scalints[i];
            if(quo > 0) {
                addWord(words, numberToWords(quo) +" "+ scale[i]);
                num -= quo * scalints[i];
            }
        }
        for(int i = 0; i < 8; i++) {
            if((num / tenints[i]) != 1)
                continue;
            int rem = num % tenints[i];
            if(rem < 10) {
                addWord(words, tens[i]);
                num -= tenints[i];
            }
        }
        for(int i = 0; i < 10; i++) {
            if((num / teenints[i]) == 1) {
                addWord(words, teens[i]);
                num -= teenints[i];
            }
        }
        addWord(words, digits[num % 10]);
        return words;
    }
};

int main() {
    Solution s;
    int input; cin >> input;
    cout << s.numberToWords(input);
    return 0;
}