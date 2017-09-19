// Jonathan Chin
// 11/6/15
//This file will be used to test Big Integer functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigAddition.h"
#include "BigMultiply.h"
#include "BigSubtract.h"
#define MAX 200000


int main()
{
    FILE *ifp = fopen("input.txt", "r");
    //FILE *ofp = fopen("output.txt", "w");

    char value1[MAX+1];
    char value2[MAX+1];
    //reads from file
    fgets(value1, MAX , ifp);
    fgets(value2, MAX, ifp);
    //testing to see if BigAdd works
    //printf("The answer is %s\n", BigAdd(value1, value2));
    printf("The answer is %s\n", BigMultiply(value1, value2));
    //also outputs to file
    // fprintf(ofp, "%s\n", BigAdd(value1, value2));

    //closing files
    fclose(ifp);
    //fclose(ofp);

    return 0;
}
