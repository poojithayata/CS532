/*
filename : pyata_Lab01.c
github : https://github.com/poojithayata/CS532
Compile command : gcc -o a pyata_HW01.c
execute command : ./a
*/

#include <stdio.h>
#include <stdbool.h>

int isPrime(int p){
    for(int i = 2; i<=p/2; i++){
        if(p%i == 0){
            return 0;
        }
    }
    return 1;
}

int isPower2(int n){
    if(n == 0){
        return 0;
    }
    return (n & (n-1)) == 0;
}

int digitsSum(int n){
    int sum = 0;
    int rem;
    while(n>0){
        rem = n%10;
        sum += rem;
        n = n/10;
    }
    return sum;
}

char * numberTransform(int n){

    if(isPrime(n) && n!=3 && n!=5){
        return "Go Blazers";
    }

    if(isPower2(n)){
        
        int n_Prime = 1;
        int p = n-1;
        while(p > 0){
            if (isPrime(p)){
                n_Prime = p;
                break;
            }
            p -= 1;
        }
        // printf("%d\n", n_Prime);
        static char s[25];
        sprintf(s, "%d", (n+n_Prime) );
        return s;
    }

    if(n%3 == 0 && n%5 == 0){
        return "UAB CS 332&532";
    }

    if(digitsSum(n) %3 == 0 ){
        return "CS";
    }

    static char string[25]; 
    sprintf(string, "%d", (digitsSum(n)*digitsSum(n)) );
    return string;
    
}

bool UABNumber(){

    int n2;
    printf("Enter an integer (UABNumber) : ");
    scanf("%d", &n2);

    int divisors_sum = 0;
    for(int i = 1; i <= n2/2; i++){
        if( n2%i == 0 ){
            divisors_sum += i;
        }
    }
    // printf("%d\n", divisors_sum);
    if(n2 == divisors_sum){
        return true;
    }
    return false;

}

int reverseNum(int n){
    int rev = 0;
    int rem;
    while(n > 0){
        rem = n %10;
        rev = rev*10 + rem;
        n = n/10;
    }
    return rev;
}

int smallerThanIndex(){

    int numbers = 0;

    int n;
    printf("SmallerThanIndex function : \n");
    printf("Enter number of array elements : ");
    scanf("%d", &n);

    int nums[n];

    printf("Enter SmallerThanIndex Array elements : \n");
    for(int i=0; i<n; i++){
        printf("Enter nums[%d] : ", i);
        scanf("%d", &nums[i]);
    }

    printf("Numbers = [");
    for(int i =0; i<n; i++){
        printf("%d, ", nums[i]);
    }
    printf("]\n");

    for(int i = 0; i<n; i++){
        // Pointer to manipulate the array for bonus points.
        if(i > *(nums+i)){
            numbers+=1;
        }
    }

    return numbers;
}

void arrayDetails(){

    int n;
    printf("ArrayDetails function : \n");
    printf("Enter the size of an array : ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter Array elements : \n");
    for(int i = 0; i <n ; i++){
        printf("Enter arr[%d] : ", i);
        scanf("%d", &arr[i]);
    }

    printf("arr = [");
    for(int i =0; i<n; i++){
        printf("%d, ", arr[i]);
    }
    printf("]\n");

    double details[6];
    details[0] = n;

    details[1] = arr[0];
    details[2] = 0;
    details[4] = arr[0];
    details[5] = 0;
    for(int i=1; i < n; i++){
        if(details[1] > arr[i]){
            details[1] = arr[i];
            details[2] = i;
        }
        if(details[4] < arr[i]){
            details[4] = arr[i];
            details[5] = i;
        }
    }

    double sum = 0;
    for(int i = 0; i< n; i++){
        sum += arr[i];
    }
    details[3] = sum/n;

    printf("Details Array = ");
    for(int i = 0; i<6; i++){
        if(i != 3){
            printf("%d, ", (int)details[i]);
        }
        else{
            printf("%.2f, ", details[i]);
        }
    }
    printf("\n");
}

int main(int argc, char** argv){

    // numberTransform(n)
    // int n;
    // printf("Enter number (numberTransform) : ");
    // scanf("%d", &n);
    // printf("%s\n", numberTransform(n));

    // UABNumber
    // if(UABNumber() == true){
    //     printf("UABNumber = True\n");
    // }
    // else{
    //     printf("UABNumber = False\n");
    // }

    // reverseNum(n3)
    // int n3;
    // printf("Enter an integer (reverseNum) : ");
    // scanf("%d", &n3);
    // printf("Reverse Number = %d\n", reverseNum(n3));


    // SmallerThanIndex() - Even implemented pointers for bonus marks.
    // printf("Count of integers in the array smaller than index : %d\n",smallerThanIndex());

    // arrayDetails()
    arrayDetails();

    return 0;
}