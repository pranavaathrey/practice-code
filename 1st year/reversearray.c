#include <stdio.h>

int main(){
	int array[] = {1222220, 20, 3332, 40, 54250, 620}, 
		length = sizeof(array)/sizeof(array[0]);
	
	printf("The original array: ");	
	for(int i = 0; i < length; i++){
		printf("%d ", array[i]);
	}

	for(int i = 0; i < length/2; i++){
		int temp = array[i];
		array[i] = array[length-1 - i];
		array[length-1 - i] = temp;
	}
	
	printf("\nThe reversed array: ");
	for(int i = 0; i < length; i++){
		printf("%d ", array[i]);
	}
}