#include <stdio.h>

typedef struct {
    int x;
    int y;
} coordinate;

int compareCoordinates(coordinate a, coordinate b) {
    if(a.x > b.x)
        return 1;
    else if(a.x < b.x)
        return -1;
    else if(a.x == b.x) {
        if(a.y > b.y)
            return 1;
        else if(a.y < b.y)
            return -1;
        else
            return 0;
    }
}

void swap(coordinate *a, coordinate *b) {
    coordinate temp = *a;
    *a = *b;
    *b = temp;
}

int partition(coordinate list[], int low, int high, 
                    int (*compare)(coordinate, coordinate)) {
    swap(&list[low + (high - low) / 2], &list[high]);
    coordinate pivot = list[high];
    
    int i = low - 1;
    for(int j = i + 1; j < high; j++) {
        if(compare(list[j], pivot) == -1) {
            i++;
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[high]);
    return i + 1;
}

void quickSort(coordinate list[], int low, int high, 
                    int (*compare)(coordinate, coordinate)) {
    if(low < high) {
        int pi = partition(list, low, high, compare);

        quickSort(list, low, pi - 1, compare);
        quickSort(list, pi + 1, high, compare);
    }
}

int main() {
    printf("Enter the number of coordinates: ");
    int n; scanf("%d", &n);

    printf("\nEnter the Cartesian coordinates, one after each other.\n");
    printf("Write in this format - (x, y):\n");
    coordinate list[n];
    for(int i = 0, k = 1; i < n; i++) {
        printf("#%d: ", k++);
        scanf(" (%d, %d)", &list[i].x, &list[i].y);
    }

    quickSort(list, 0, n - 1, compareCoordinates);

    printf("\nThe sorted coordinates (in ascending): \n");
    for(int i = 0, k = 1; i < n; i++) 
        printf("#%d  (%d, %d)\n", k++, list[i].x, list[i].y);
    return 0;
}