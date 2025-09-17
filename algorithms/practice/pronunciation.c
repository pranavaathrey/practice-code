#include <stdio.h>

int isVowel(char c) {
    if(c == 'a' || c == 'e'
    || c == 'i' || c == 'o' || c == 'u')
        return 1;
    else 
        return 0;
}

int main() {
    printf("Enter the number of test cases: ");
    int n; scanf("%d", &n); 
    
    while(n--) {
        printf("\nEnter the length of the word, followed by the word: ");
        int len; scanf("%d", &len); getchar();
        
        int consonantCount = 0;
        for(int i = 0; i < len; i++) {
            if(!isVowel(getchar())) consonantCount++;
            else consonantCount = 0;
            
            if(consonantCount >= 4) break;
        }
        if(consonantCount < 4) printf(">> YES, easy to pronounce\n");
        else printf(">> NO, difficult to pronounce\n");
    }
}

