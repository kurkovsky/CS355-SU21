#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// an example of using qsort with an array of strings
// also see https://man7.org/linux/man-pages/man3/qsort.3.html

// a comparison function that will be used by qsort()
#define MaxWords 9
#define MaxWordLength 20

int myStringCompare(const void *a, const void *b) {
    return -strcmp((const char*)a, (const char*)b);
}

int main(){
    char words[MaxWords][MaxWordLength] = {"apple", "orange", "banana","pear", "strawberry","grape","watermelon","1234","Apple"};
    qsort(words, MaxWords, MaxWordLength,myStringCompare);

    for(int i=0; i<MaxWords; i++)   // verify the correctness of sorting
        printf("%d: %s\n", i, words[i]);

    return 0;
}