#include <stdio.h>

typedef struct{
    char name[50];
    long population;
} City;

int main(){
    int n = 3; //number of cities
    City cities[n];
    //store city names and populations in City struct
    for(int i = 0; i < n; i++){
        scanf("%s %ld", &cities[i].name, &cities[i].population);
    }
    
    //calculating total population and avg population
    long totalPop = 0;
    City *ptr = cities;
    for(int i = 0; i < n; i++){
        totalPop += (ptr + i)->population;
    }
    double avgPop = (double)totalPop/n;
    
    printf("%ld\n%.2lf", totalPop, avgPop);
}