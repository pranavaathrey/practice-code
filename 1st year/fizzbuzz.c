#include <stdio.h>

int main(){
	char fizzbuzz[2][5] = {"Fizz", "Buzz"}; 
	//this is including one extra char in each string for the null terminator (\0)
	int until;

	printf("n = ");
	scanf("%d", &until);
	
	for(int i = 1; i <= until; i++){
		if(i%3 == 0 && i%5 == 0) printf("%s%s ", fizzbuzz[0], fizzbuzz[1]);
		else if(i%3 == 0) printf("%s ", fizzbuzz[0]);
		else if(i%5 == 0) printf("%s ", fizzbuzz[1]);
		else printf("%d ", i);
	}
}