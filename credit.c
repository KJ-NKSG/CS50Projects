//Problem Set 1 : Credit Card problem
//Code will use Switch to determine type of credit card.
//If no match exists, then will return invalid
//Code will also use a count   &  checksum function based on the
//definition provided

#include <cs50.h>
#include <stdio.h>

int count_func(long long int num, int type);
int checksum(long long int num, int count);

int main()
{
    long long int CCNo;
    int checkvalue;
    int x;

    //Prompt user to input CC No
    do
    {
        CCNo = get_long("Number: ");
    }
    while (CCNo <= 0);

    // Use 2 functions defined to find Count and First 2 Digits of the CC No
    int count = count_func(CCNo, 1);
    int First2Digit = count_func(CCNo, 2);
    int First1Digit = First2Digit / 10;

    if (First1Digit == 4)
    {
        x = 4 ;
    }
    else
    {
        x = First2Digit ;
    }

    // Use function to check the check sum. Must be 0 to be valid.
    checkvalue = checksum(CCNo, count);

    if (checkvalue != 0)
    {
        printf("INVALID\n");
    }

    //Type of card using if and switch statement
    else if (count == 13 || count == 15 || count == 16)
    {
        switch (x)
        {
            case 34:
                printf("AMEX\n");
                break;
            case 37:
                printf("AMEX\n");
                break;

            case 51:
                printf("MASTERCARD\n");
                break;
            case 52:
                printf("MASTERCARD\n");
                break;
            case 53:
                printf("MASTERCARD\n");
                break;
            case 54:
                printf("MASTERCARD\n");
                break;
            case 55:
                printf("MASTERCARD\n");
                break;

            case 4:
                printf("VISA\n");
                break;

            default:
                printf("INVALID\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }

    //printf("%d, count = %d , first2digit = %d\n", checkvalue, count, First2Digit);
    return 0;
}

//Function to count CC number and also return first 2 digits
//Type 1 = return length of CC number
//Type 2 = return first 2 digits of CC Number

int count_func(long long int num, int type)
{
    int count = 0;
    if (type == 1)
    {
        while (num > 0)
        {
            num = num / 10;
            count = count + 1;
        }
        return count;
    }
    else if (type == 2)
    {
        while (num >= 100)
        {
            num = num / 10;
        }
        return num;
    }
    else
    {
        printf("Error in function count_func\n");
    }
    return 0;
}

// second function to conduct checksum using Luhn's algorithm
int checksum(long long int num, int count)
{
    int digit = 0;
    int sum = 0;
    int digit1 = 0;
    int sum1 = 0;
    long long int num1 = 0;
    int lastdigit = 0;

    // loop through each sdigit and multiple by 2 / summation based on the algorithm
    for (int i = 1 ; i <= count ; i++)
    {
        digit = num % 10;
        num = num / 10;

        if (i % 2 == 0)
        {
            num1 = digit * 2;

            if (num1 >= 10) // check if more then 1 digits after x2
            {
                digit1 = num1 % 10;
                num1 = num1 / 10;
                sum1 = num1 + digit1; // add the two digits together
                sum = sum + sum1;
            }
            else
            {
                sum = sum + num1;
            }
        }
        else
        {
            sum = sum + digit;
        }
    }
    lastdigit = sum % 10;
    return lastdigit;
}