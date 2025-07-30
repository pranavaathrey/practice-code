#include <stdio.h>

int main(){
	int num, steps = 0;
	printf("Enter a number: ");
	scanf("%d", &num);
	
	for(; num > 0; steps++){
		if(num%2 == 0) num /= 2;
		else num -= 1;
	}
	printf("Number of steps to reduce it to 0 is %d.", steps);
}