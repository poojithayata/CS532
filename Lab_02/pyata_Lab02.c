/*
filename : pyata_Lab02.c
github : https://github.com/poojithayata/CS532
Compile command : gcc -o a pyata_Lab02.c
execute command : ./a
*/

#include <stdio.h>

int main(int argc, char** argv){

    int N;
    printf("Enter the number of array elements : ");
    scanf("%d", &N);

    int arr[N];
    for(int i =0; i< N; i++){
        printf("Array[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    printf("Array Before Sorting : {");
    for(int i =0; i<N; i++){
        printf("%d, ",arr[i]);
    }
    printf("}\n");

    printf("Applying Sorting....");
    int key, j;
    for(int i =1; i<N; i++){
        key = arr[i];
        j = i-1;
        while (j > 0 && arr[j]>key){
            arr[j+1] = arr[j];
            j -= 1;
        }
        arr[j+1] = key;
    }

    printf("Array After Sorting : {");
    for(int i =0; i<N; i++){
        printf("%d, ",arr[i]);
    }
    printf("}\n");

    return 0;
}