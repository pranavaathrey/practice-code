#include <stdio.h>
#include <string.h>

char result[99];

int longestPalSubstr(char str[])
{
	int n = strlen(str);

	// Stores the maximum length
	int maxLength = 1, start = 0;

	// Iterate over the string 0 to i
	for (int i = 0;	i < strlen(str); i++) {
		// Iterate over the string i to max
		for (int j = i;	j < strlen(str); j++) {
			int flag = 1;

			// Check for palindrome
			for (int k = 0;	k < (j - i + 1) / 2; k++){
				if (str[i + k] != str[j - k]){
					flag = 0;
                    break;
                }
            }
			// If string [i, j - i + 1] is palindromic
			if (flag && (j - i + 1) > maxLength) {
				start = i;
				maxLength = j - i + 1;
			}
		}
	}

    for(int i = 0; i < maxLength; i++)
        result[i] = str[start + i];

    result[maxLength] = '\0';
    return maxLength;
}

int main()
{
    char str[99];
	//eg: In "bruhmalayalambruh", the length of the longest palindromic substring: 9.
    scanf("%s", &str);

	printf("The length of the longest palindromic substring: %d", longestPalSubstr(str));
    printf("\n& said substring is: %s", result);
	return 0;
}
