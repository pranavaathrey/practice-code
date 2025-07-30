#include <stdio.h>
#include <string.h>

const char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

const char *illions[] = {"", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion", "octillion", "nonillion"};
const char *modifiers[] = {"", "un", "duo", "tre", "quattuor", "quin", "se", "septe", "octo", "nove"};
const char *gintillions[] = {"", "dec", "vigint", "trigint", "quadragint", "quinquagint", "sexagint", "septuagint", "octogint", "nonagint"};
const char *entillions[] = {"", "centi", "ducent", "trecent", "quadringent", "quingent", "sescent", "septingent", "octingent", "nongent", "millin"};

const char *conjugates[] = {"a", "n", "m", "s", "i" "illion"};

//improves input readability (adds a comma every three digits)
void makeReadable(char *num, char *result) {
    int len = sizeof(num)/sizeof(num[0]) - 1;
    for(int i = 1; i <= len; i++){
        if(i%3 == 0){
            strcat(result, num[len - i]);
            strcat(result, ",");
        } else strcat(result, num[len - i]);
    }
}

//converts inputs between 0 - 999 into words
void convert999(int num, char *result) {
    
}

//converts the rest into words
void numberToWords(char *num, char *result) {
    
}

int main(){
    char num[3100], result[999999];
    printf("Enter a large number (no commas): ");
    scanf("%s", &num);

    makeReadable(num, result);
    printf("Number in words: %s\n", result);

    return 0;
}