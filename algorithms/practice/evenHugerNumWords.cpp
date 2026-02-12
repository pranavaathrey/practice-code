#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std;

class NumberToWords {
private:
    static const vector<string> ONES;
    static const vector<string> TENS;
    
    // Latin prefixes for generating scales > Nonillion
    static const vector<string> LATIN_ONES;
    static const vector<string> LATIN_TENS;

    // Standard hardcoded scales for 1 to 9 (Million to Nonillion)
    // Used to ensure standard English spelling (e.g., "Billion" instead of "Duomillion")
    static const vector<string> STANDARD_ILLIONS;

    // Converts a number 0-999 to words
    static string convertChunk(int num) {
        if (num == 0) return "";
        
        string str;
        if (num >= 100) {
            str += ONES[num / 100] + " Hundred";
            num %= 100;
            if (num > 0) str += " ";
        }
        
        if (num > 0) {
            if (num < 20) {
                str += ONES[num];
            } else {
                str += TENS[num / 10];
                if (num % 10 > 0) str += " " + ONES[num % 10];
            }
        }
        return str;
    }

    // Generates scale names: Thousand, Million, Billion ... Unvigintillion, etc.
    static string getScaleName(size_t chunkIndex) {
        if (chunkIndex == 0) return "";
        if (chunkIndex == 1) return "Thousand";

        // "Illion" index calculation: 
        // Chunk 2 = Million (1st illion), Chunk 3 = Billion (2nd illion)
        size_t illionIndex = chunkIndex - 1;

        // Use standard names for small indices (Million -> Nonillion)
        if (illionIndex <= 9) {
            return STANDARD_ILLIONS[illionIndex - 1];
        }

        // Generate names algorithmically for Decillion (10) and above
        // Format: [Unit Prefix][Ten Prefix]illion
        // Example: 12 -> Duo-dec-illion
        size_t ones = illionIndex % 10;
        size_t tens = illionIndex / 10;

        string scale = LATIN_ONES[ones] + LATIN_TENS[tens] + "illion";
        
        // Capitalize first letter (optional, for consistency)
        if (!scale.empty()) scale[0] = toupper(scale[0]);
        
        return scale;
    }

    public:
    static string convert(cpp_int num) {
        if (num == 0) return "Zero";

        string result = "";
        size_t chunkIndex = 0;
        
        // Process in chunks of 1000 (base 10^3)
        while (num > 0) {
            // Extract lowest 3 digits
            int chunk = (int)(num % 1000);
            num /= 1000;

            if (chunk > 0) {
                string chunkText = convertChunk(chunk);
                string scaleName = getScaleName(chunkIndex);

                string part = chunkText;
                if (!scaleName.empty()) {
                    part += " " + scaleName;
                }

                if (result.empty()) {
                    result = part;
                } else {
                    result = part + " " + result;
                }
            }
            chunkIndex++;
        }
        return result;
    }
};
const vector<string> NumberToWords::ONES = {
    "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
};
const vector<string> NumberToWords::TENS = {
    "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
};
const vector<string> NumberToWords::LATIN_ONES = {
    "", "un", "duo", "tre", "quattuor", "quin", "sex", "septen", "octo", "novem"
};
const vector<string> NumberToWords::LATIN_TENS = {
    "", "dec", "vigint", "trigint", "quadragint", "quinquagint", 
    "sexagint", "septuagint", "octogint", "nonagint", "cent"
};
const vector<string> NumberToWords::STANDARD_ILLIONS = {
    "Million", "Billion", "Trillion", "Quadrillion", "Quintillion", 
    "Sextillion", "Septillion", "Octillion", "Nonillion"
};

int main() {
    cpp_int input; 
    cout << "Enter a massive number: ";
    if (cin >> input) 
        cout << "\nResult:\n" << NumberToWords::convert(input) << endl;
    return 0;
}