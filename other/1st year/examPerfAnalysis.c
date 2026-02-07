#include <stdio.h>
#include <stdlib.h>

int readScores(int scores[]){
    for(int i = 0; i < 50; i++){
        int temp;
        scanf("%d", &temp);
        if(temp < 0 || temp > 100)
            return -1;
        else
            *(scores + i) = temp;
    }
    return 0;
}

float calculateAverage(const int scores[]){
    float sum = 0;
    for(int i = 0; i < 50; i++){
        sum += *(scores + i);
    }
    return sum / 50;
}

int findMax(const int scores[]){
    int max = *(scores);
    for(int i = 0; i < 50; i++){
        if(*(scores + i) > max) 
            max = *(scores + i);
    }
    return max;
}

int findMin(const int scores[]){
    int min = *(scores);
    for(int i = 0; i < 50; i++){
        if(*(scores + i) < min) 
            min = *(scores + i);
    }
    return min;
}

void sortScores(int scores[]){
    int swappage = 0;
    for(int i = 0; i < 49; i++){
        swappage = 0;
        for(int j = 0; j < 49 - i; j++){
            if(*(scores + j) > *(scores + j + 1)){
                *(scores + j) += *(scores + j + 1);
                *(scores + j + 1) = *(scores + j) - *(scores + j + 1);
                *(scores + j) = *(scores + j) - *(scores + j + 1);
                swappage = 1;
            }
        }
        if(swappage == 0)
            break;
    }
}

void displayScores(const int scores[], int min, int max, float avg){
    printf("The scores: \n");
    for(int i = 0; i < 50; i++){
        printf("%d ", *(scores + i));
    }
    printf("\n The minimum value: %d\n", min);
    printf("\n The maximum value: %d\n", max);
    printf("\n The average value: %.2f\n", avg);
}

int main(){
    int *scores = (int *)malloc(50 * sizeof(int));

    readScores(scores);
    if (readScores(scores) == -1) {
        printf("Invalid input: all scores must be between 0 and 100.\n");
        free(scores);
        return 1;
    }
    float avg = calculateAverage(scores);
    int min = findMin(scores);
    int max = findMax(scores);
    sortScores(scores);

    displayScores(scores, min, max, avg);

    free(scores);
    return 0;
}