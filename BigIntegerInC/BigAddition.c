// Jonathan Chin
// 11/7/2015

#include "BigAddition.h"
#define MAX(a, b)((a) > (b) ? (a) : (b))

char *BigAdd(char *num1, char *num2)
{
    int lengthA = strlen(num1);
    int lengthB = strlen(num2);
    int length = MAX(lengthA, lengthB);
    //no matter what two numbers get added together there can only be one extra digit in the result
    int storage[length+1];
    int i = lengthA-1;
    int j = lengthB-1;
    int k=0;
    int carry=0;

    //store digits until we reach the start of the first digit in one of the numbers
    while(i>=0 && j>=0)
    {
        //insert numbers into the front and later reverse it
        int digit = (num1[i]-'0')+ (num2[j]-'0');
        if( digit > 9)
        {
            //stores the last digit of the sum
            storage[k]= (digit+carry)%10;
            //will carry 1 over to the next digit
            carry=1;
        }
        else
        {
            //this means digit + carry is 10
            if(digit + carry == 10)
            {
                storage[k] = 0;
                carry=1;
            }
            else
            {
                storage[k] = digit+carry;
                carry=0;
            }

        }

        i--;
        j--;
        k++;

    }

    //finishing up the rest of the digits in the larger number
    while(i>=0){
        if(num1[i]-'0' + carry == 10){
            storage[k]=0;
        }
        else{
            storage[k] = num1[i]-'0' + carry;
            carry=0;
        }

        i--;
        k++;
    }
    while(j>=0){
        if(num2[j]-'0' + carry == 10){
            storage[k]=0;
        }
        else{
            storage[k] = num2[j]-'0'+carry;
            carry=0;
        }

        j--;
        k++;
    }
    //keeps track if there is an extra final carry over
    int flag=1;
    if(carry==1){

        storage[k]=1;
        flag=0;
    }

    //k now represents the number of digits in the storage array
    //now we need to conver this back into a char array but we need to do it in reverse order
    char *result;
    result = malloc(200000*sizeof(char));

    for(i=k-flag, j=0; i>0; i--, j++){
        //converting back to char and storing it in the result in reverse order
        result[j] = (char)storage[i] + '0';


    }
    //string needs to have a null termination
    result[j] = '\0';

    return result;

}
