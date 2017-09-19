#include "BigMultiply.h"

char *BigMultiply(char *num1, char *num2){

    int lengthA = strlen(num1)-1;
    int lengthB = strlen(num2)-1;
    int i;
    int j;

    int product[lengthA+lengthB];
    for(i=0; i<lengthA+lengthB; i++){
        product[i]=0;
    }
    int value;
    int k=lengthA+lengthB-1;
    //long multiplication
    for(i=lengthA-1; i>=0; i--){
        int carry = 0;
        for(j=lengthB-1; j>=0; j--, k--){
            //multiplying and adding digit
            value = (num1[i]-'0') * (num2[j]-'0')  + carry;

            //storing the carry over
            carry = value/10;
            //only one digit per index, store the last index digit
            product[k] += value%10;
            if(product[k]>=10){
                carry += (product[k]/10);
                product[k] %= 10;

            }


        }
        product[k] += carry;
        k += lengthB-1;

    }
    //takes into account if there is an extra digit in the front
    int flag=0;
    if(product[0]==0){
        flag=1;
    }
    //convert back into string format
    char *result;
    result = malloc(200000*sizeof(char));
    for(i=0; i<lengthA+lengthB-flag; i++){

        result[i] = (char)product[i+flag] + '0';
    }
    //last digit comes from the final carry
    result[lengthA+lengthB-flag] = '\0';
    return result;
}
