// get each triangle's sides (as ints), and sort them by their areas.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int sideA;
    int sideB;
    int sideC;
    double area;
}triangle;

int compare(const void *a, const void *b){
    triangle *t1 = (triangle *)a;
    triangle *t2 = (triangle *)b;
    
    return (t1->area > t2->area) 
         - (t1->area < t2->area);
}

int isValidTriangle(int a, int b, int c){ 
    // to avoid negative values from being passed to heron's sqrt
    return (a + b) > c
        && (b + c) > a
        && (c + a) > b;
}

int main(){
    int n;
    scanf("%d", &n);
    
    triangle *tris = (triangle *)malloc(n * sizeof(triangle));
    for(int i = 0; i < n; i++){ //input
        scanf("%d %d %d", &(*(tris + i)).sideA, 
                          &(*(tris + i)).sideB, 
                          &(*(tris + i)).sideC);
    }
    for(int i = 0; i < n; i++){ //area calc
        if(isValidTriangle((*(tris + i)).sideA, (*(tris + i)).sideB, (*(tris + i)).sideC))
        {
            double s = ((*(tris + i)).sideA + (*(tris + i)).sideB
                                            + (*(tris + i)).sideC) / 2.0;
            (*(tris + i)).area = sqrt(s*(s - (*(tris + i)).sideA)
                                       *(s - (*(tris + i)).sideB)
                                       *(s - (*(tris + i)).sideC));
            //printf("%d\n", (*(tris + i)).area);
        } else (*(tris + i)).area = 0;
    }
    qsort(tris, n, sizeof(triangle), compare); //sort
    
    for(int i = 0; i < n; i++){ //print
        printf("%d %d %d\n", (*(tris + i)).sideA, 
                             (*(tris + i)).sideB, 
                             (*(tris + i)).sideC);
    }
    free(tris);
}
