/*
filename : pyata_Lab03.c
github : https://github.com/poojithayata/CS532
Compile command : gcc -o a pyata_Lab03.c
execute command : ./a
*/

#include <stdio.h>
#include <stdlib.h>

void displayArray(float *arr, int n){
    printf("[");
    for (int i = 0; i < n-1; i++)
    {
        printf("%.1f, ", arr[i]);
    }
    printf("%.1f]\n", arr[n-1]);
    
}

void sortArray(float *arr, int n){
    printf("Applying Sorting....\n");
    int key, j;
    for(int i =1; i<n; i++){
        key = arr[i];
        j = i-1;
        while (j >= 0 && arr[j]>key){
            arr[j+1] = arr[j];     
            j -= 1;
        }
        arr[j+1] = key;
    }
}

int main(int argc, char** argv){

    int N;
    printf("Enter the number of array elements : ");
    scanf("%d", &N);

    // Dynamic Mmemory Allocation
    float *arr = (float*)malloc(N*sizeof(float)) ;
    for(int i =0; i< N; i++){
        printf("Array[%d] = ", i);
        scanf("%f", &arr[i]);
    }

    printf("Array Before Sorting : ");
    displayArray(arr, N);

    // Applying insertion sort
    sortArray(arr, N);

    printf("Array After Sorting : ");
    displayArray(arr, N);

    return 0;
}