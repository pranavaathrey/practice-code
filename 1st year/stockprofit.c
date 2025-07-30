#include <stdio.h>

int main(){
	int days, max = 0, dstrt = 0, dend = 0;
	scanf("%d", &days);

	int stprcs[days];
	for(int i = 0; i < days; i++)
		scanf("%d", &stprcs[i]);
	
	for(int size = 0; size < days; size++){
		int diff = 0;
		for(int j = 0; j < (days - size); j++){
			diff = stprcs[j + size] - stprcs[j];
			if(diff > max){
				max = diff;
				dstrt = j + 1;
				dend = j + size + 1;
			}
		}
	}
	if(max > 0) printf("Buy on day %d and sell on %d for a profit of %d.\n", dstrt, dend, max);
	else printf("No profitable trade");
}