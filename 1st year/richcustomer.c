#include <stdio.h>

int main(){
	int data[3][3] = {{7, 1, 3}, {2, 8, 7}, {1, 9, 5}};
	int cus[3] = {0}, wealth = 0; 
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
			cus[i] += data[i][j];
	}
	for(int k = 0; k < 3; k++){
		if(cus[k] > wealth)
			wealth = cus[k];
	}
	printf("The wealth of the richest customer as per the data: ₹%d lakh", wealth);
	//unicode characters don't work, search for a fix
}