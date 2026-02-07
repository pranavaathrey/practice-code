#include <stdio.h>

int main(){
	int n, i = 0, num, sum = 0, arr[100];
	
	printf("Enter the number at which you want to stop the running sum: ");
	scanf("%d", &n);

	printf("Enter the numbers of the array, separated by spaces. \n(The array can have a maximum of 99 numbers.) \nEnd input with a non-numeric character: ");
	for(; (scanf("%d", &num)) == 1; i++)
		arr[i] = num;
	
	if(n < i){
		for(int j = 0; j < n; j++)
			sum += arr[j];
		printf("The running sum until the %dth number is: %d", n, sum);
	} else printf("Enter a number that is within the bounds of the array you\'ve entered. \nTry again.");
}