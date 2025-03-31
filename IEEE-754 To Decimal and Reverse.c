#include <stdio.h>

void DecimalToFloatingPoint(float num)
{
    float numToWrite = num;
    char sign = (num < 0) ? '1' : '0';

    if (num < 0)
        num = -num;

    int number = (int)num;
    float floatingPart = num - number;

    char intPartBin[32] = {0};
    int intPartLen = 0;

    if (number == 0)
    {
        intPartBin[intPartLen++] = '0';
    }
    else
    {
        while (number > 0)
        {
            intPartBin[intPartLen++] = (number % 2) + '0';
            number /= 2;
        }
    }

    for (int i = 0; i < intPartLen / 2; i++)
    {
        char temp = intPartBin[i];
        intPartBin[i] = intPartBin[intPartLen - i - 1];
        intPartBin[intPartLen - i - 1] = temp;
    }

    int exponent;
    int firstOneIndex = 0;

    if (num >= 1.0f)
    {
        while (firstOneIndex < intPartLen && intPartBin[firstOneIndex] != '1')
        {
            firstOneIndex++;
        }
        exponent = (intPartLen - firstOneIndex - 1) + 127;
    }
    else if (num > 0.0f)
    {
        exponent = 127;
        while (floatingPart < 1.0f)
        {
            floatingPart *= 2;
            exponent--;
        }
        floatingPart -= 1.0f;
    }
    else // 0.0
    {
        exponent = 0;
    }

    char mantissa[24];
    int mantissaIndex = 0;

    if (num >= 1.0f)
    {
        for (int i = firstOneIndex + 1; i < intPartLen && mantissaIndex < 23; i++)
            mantissa[mantissaIndex++] = intPartBin[i];
    }

    while (mantissaIndex < 23 && floatingPart > 0.0f)
    {
        floatingPart *= 2;
        if (floatingPart >= 1.0f)
        {
            mantissa[mantissaIndex++] = '1';
            floatingPart -= 1.0f;
        }
        else
        {
            mantissa[mantissaIndex++] = '0';
        }
    }

    while (mantissaIndex < 23)
    {
        mantissa[mantissaIndex++] = '0';
    }
    mantissa[23] = '\0';

    char exponentBin[9] = {0};
    int expTemp = exponent;

    for (int i = 7; i >= 0; i--)
    {
        exponentBin[i] = (expTemp % 2) + '0';
        expTemp /= 2;
    }

    exponentBin[8] = '\0';

    printf("Floating point representation of %f is: %c%s%s\n",  numToWrite, sign, exponentBin, mantissa);
}

/*void DecimalToFloatingPoint(float num)
{
    float numToWrite = num;
    char sign = 0;

    if (num < 0)
    {
        sign = '1';
        num = -num;
    }
    else
        sign = '0';

    int number = (int)num;

    float floatingPart = num - number;

    int i = 0;
    char binArr[9];

    if (number == 0)
    {
        binArr[i++] = '0';
    }
    else
    {
        while(number >= 0)
        {
            binArr[i++] = (number % 2) + '0';
            number /= 2;
        }
    }

    binArr[i] = '\0';
    int temp_i = i;

    int binArrLength = i;

    for (int a = 0; a < binArrLength / 2; a++)//Reversing the 8 bit int part
    {
        char temp = binArr[a];
        binArr[a] = binArr[binArrLength - a - 1];
        binArr[binArrLength - a - 1] = temp;
    }
    //printf("%s \n", binArr);

    int firstOneIndex = 0;

    while (binArr[firstOneIndex] != '1' && binArr[firstOneIndex] != '\0')
        firstOneIndex++;

    int exp = (temp_i - firstOneIndex - 1) + 127;//bias

    char mantissa[24];
    int mantissaIndex = 0;

    for (int i = firstOneIndex + 1; i < temp_i; i++)//Adding all bits after the first 1 from binArr and then floatingPart's bits
    {
        mantissa[mantissaIndex++] = binArr[i];
    }

    //printf("%s \n ", mantissa);

    int whileSizeForMantissa = 23;

    while (mantissaIndex < whileSizeForMantissa)
    {
        floatingPart *= 2;
        if (floatingPart >= 1.0f)
        {
            mantissa[mantissaIndex++] = '1';
            floatingPart -= 1.0f;
        }
        else
        {
            mantissa[mantissaIndex++] = '0';
        }
    }
    mantissa[mantissaIndex] = '\0';

    char arrToExp[9];

    for (int a = 7; a >= 0; a--)
    {
        arrToExp[a] = (exp % 2) + '0';
        exp /= 2;
    }
    arrToExp[8] = '\0';

    printf(" Floating point representation of number %f is %c%s%s \n\n",numToWrite , sign, arrToExp, mantissa);//Sign exponent mantissa
}
*/
void BitToDecimal(char arr[])
{
    char tempSign = arr[0];
    int sign = tempSign - '0';

    int tempExponent = 0;
    int i;
    for (i = 1; i < 9; i++)
        tempExponent = tempExponent * 2 + (arr[i] - '0');


    float mantissa = 1.0f; //Adding 1 because they are normally in 1.ffff format
    float frac = 0.5f;// 2^(-1)
    for (i = 9; i < 32; i++)
    {
        if (arr[i] == '1')
            mantissa += frac;

        frac = frac / 2.0f;
    }

    int realExp = tempExponent - 127;

    float result = mantissa;
    int exp;
    if (realExp > 0)
    {
        for (exp = 0; exp < realExp; exp++)
            result *= 2;
    }
    else if (realExp < 0)
    {
        for (exp = 0; exp < -realExp; exp++)
            result /= 2;
    }

    if (sign == 1)//First character. If 1 then it is negative
        result *= -1;

    printf(" Decimal representation of number %s is %f\n\n", arr, result);
}

int main()
{
    int choice;
    float number;
    char bitRepresentedNum[33];
    printf(" Welcome to floating point bit model\n");

    while(1)
    {
        printf(" 1-For decimal number to floating point bit model\n");
        printf(" 2-For 32 bit represented floating point number to decimal number\n");
        printf(" 3-Quit\n");
        printf(" Your selection:");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf(" Enter number: ");
            scanf("%f", &number);
            DecimalToFloatingPoint(number);
            break;
        case 2:
            printf(" Enter 32 bit binary float point bit model: ");
            scanf("%s", &bitRepresentedNum);
            BitToDecimal(bitRepresentedNum);
            break;
        case 3:
            return 0;
            break;
        /*default:
            printf(" Please enter a valid input\n");//Sometimes it causes infinite loop
            break;*/
        }
    }
}
