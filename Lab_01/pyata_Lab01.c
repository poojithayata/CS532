/*
filename : pyata_Lab01.c
github : https://github.com/poojithayata/CS532
Compile command : gcc -o a pyata_Lab01.c
execute command : ./a
*/

#include <stdio.h>

int main(int argc, char** argv){

    int given_number;
    printf("Enter a number : ");
    scanf("%d", &given_number);

    int count = 0;
    for(int i = 1; i <= given_number; i++){
        if((given_number%i) == 0){
            count++;
        }
    }

    if(count == 2){
        printf("The number is prime.\n");
    }
    else{
        printf("The number is not prime.\n");
    }
    
    return 0;
}