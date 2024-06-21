/*
filename : pyata_Lab03.c
github : https://github.com/poojithayata/CS532
Compile command : gcc -o a pyata_Lab03.c
execute command : ./a
*/

#include <stdio.h>
#include <stdlib.h>
# include <string.h>

char ** Input_Array(int *no){

    // This statement read the number of strings in an array
    printf("Enter the number of strings in an Array : ");
    scanf("%d", no);

    // This statement states the dynamic memory allocation for the strings of differen sizes
    char **stringArray = (char**)malloc((*no) * sizeof(char*));
    // Handling errors if error is there then program terminates
    if (stringArray == NULL){
        printf("Error!....");
        exit(1);
    }

    // Declaring a temporary variable
    char temp[1024];

    for(int i = 0; i < *no; i++){
        printf("String[%d] : ", i);
        scanf("%s", temp);

        // Each string memory alloction of the array
        stringArray[i] = (char*)malloc((strlen(temp)+ 1)* sizeof(char));
        // Handling errors if error is there then program terminates
        if(stringArray[i] == NULL){
            printf("Error!....");
            exit(1);
        }
        // Copying the buffer to the actual array - stringArray
        strcpy(stringArray[i], temp);
    }

    return stringArray;
}

void display_Array(char **string_Array, int num){
    printf("[");
    for (int i = 0; i < num-1; i++)
    {
        printf("%s, ", string_Array[i]);
    }
    printf("%s]\n", string_Array[num-1]);
    
}

void insertion_Sort(char **arr, int n){
    printf("Applying Sorting....\n");
    // int key, j;
    for(int i =1; i<n; i++){
        char *key = arr[i];
        int j = i-1;
        while (j >= 0 && strcmp(arr[j],key)>0){
            arr[j+1] = arr[j];     
            j -= 1;
        }
        arr[j+1] = key;
    }
}

int main(int argc, char** argv){

    int N;
    char **strArray = Input_Array(&N);


    printf("String Array Before Sorting : ");
    display_Array(strArray, N);

    // Applying insertion sort
    insertion_Sort(strArray, N);

    printf("String Array After Sorting : ");
    display_Array(strArray, N);

    // To free the memory of the strArray
    for(int i =0; i<N; i++){
        free(strArray[i]);
    }
    free(strArray);

    return 0;
}