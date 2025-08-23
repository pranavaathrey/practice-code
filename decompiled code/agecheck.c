#include <stdio.h>

int main(){
	int age;
	printf("Enter your age: \n");
	scanf("%d", &age);
	
	if(age >= 0){
		printf("You are a minor.");
	}else if(age >= 18){
		printf("You are an adult.");	
	}else{
		printf("Age invalid.");
	}
	int bruh = (age * 3 + 4) / 2 - 1;
}