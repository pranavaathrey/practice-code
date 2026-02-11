#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

// >>----------------------|Comparator Functions|-----------------------<< //

typedef struct {
    char name[MAX_LENGTH];
    float GPA;
    int age; 
    char major[MAX_LENGTH];
} StudentRecord;

int compareByName(StudentRecord a, StudentRecord b) {
    return strcmp(a.name, b.name);
}
int compareByGPA(StudentRecord a, StudentRecord b) {
    if(a.GPA > b.GPA)
        return 1;
    else if(a.GPA < b.GPA)
        return -1;
    else
        return 0;
}
int compareByAge(StudentRecord a, StudentRecord b) {
    return a.age - b.age;
}
int compareByMajor(StudentRecord a, StudentRecord b) {
    return strcmp(a.major, b.major);
}

// >>--------------------|Quick Sort Implementation|--------------------<< //

void swap(StudentRecord *a, StudentRecord *b) {
    StudentRecord temp = *a;
    *a = *b;
    *b = temp;
}

int partition(StudentRecord list[], int left, int right,
                int (*comparator)(StudentRecord, StudentRecord)) {
    swap(&list[left + (right - left) / 2], &list[right]);
    StudentRecord pivot = list[right];
    
    int i = left - 1;
    for(int j = left; j < right; j++) {
        if(comparator(list[j], pivot) <= 0) {
            i++;
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[right]);
    return i + 1;
}

void quickSort(StudentRecord list[], int left, int right,
                int (*comparator)(StudentRecord, StudentRecord)) {
    if(left < right) {
        int pi = partition(list, left, right, comparator);
        
        quickSort(list, left, pi - 1, comparator);
        quickSort(list, pi + 1, right, comparator);
    }
}

// >>--------------------------|Main Function|--------------------------<< //

int main() {
    printf("\nEnter the number of student records: ");
    int n; scanf("%d", &n);
    
    StudentRecord records[n];
    printf("\nEnter the student records (name, GPA, age, major): \n");
    for(int i = 0; i < n; i++) {
        printf("Record %d: ", i + 1);
        scanf("%s", &records[i].name);
        scanf("%f", &records[i].GPA);
        scanf("%d", &records[i].age);
        scanf("%s", &records[i].major);
    }  
    printf("\nChoose sorting criteria (name, gpa, age, major): ");
    char sortChoice[MAX_LENGTH]; 
    scanf("%s", &sortChoice);
    
    int (*comparator)(StudentRecord, StudentRecord);
    
    if(strcmp(sortChoice, "name") == 0)
        comparator = compareByName;
    else if(strcmp(sortChoice, "gpa") == 0)
        comparator = compareByGPA;
    else if(strcmp(sortChoice, "age") == 0)
        comparator = compareByAge;
    else if(strcmp(sortChoice, "major") == 0)
        comparator = compareByMajor;
    
    quickSort(records, 0, n - 1, comparator);
    
    printf("\nSorted Student Records: \n");
    printf("%-12s%-8s%-8s%-8s\n", 
            "Name", "GPA", "Age", "Major");
    for(int i = 0; i < n; i++) {
        printf("%-12s", records[i].name);
        printf("%-8.2f", records[i].GPA);
        printf("%-8d", records[i].age);
        printf("%-8s\n", records[i].major);
    }  
    return 0;
}