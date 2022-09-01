#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100

struct fraction {
    int whole, numerator, denominator;
};

/**
 * @brief make sure the string only contain digits, . , /
 * 
 * @param input string input
 * @return int 1 if valid 0 if not
 */
int correctCharacters(char *input){
    int x;

    for(x = 0; (isdigit(input[x]) || input[x] == '.' || input[x] == '/') && x < strlen(input); x++){}

    return x < strlen(input) ? 0 : 1;
}

/**
 * @brief determine the format is correct: 23.4 or 4/5
 * 
 * @param input string input
 * @return ** int 1 if valid 0 if not
 */
int correctFormat(char *input){
    int dot_or_slash = 0, x;

    for(x = 0; dot_or_slash < 2 && x < strlen(input); x++){
        if(input[x] == '.' || input[x] == '/'){
            dot_or_slash++;
            if(x == 0 || x == strlen(input) - 1){
                break;
            }
        }
    }

    return x < strlen(input) ? 0 : 1;
}

/**
 * @brief determine if the input is a fraction: 4/5
 * 
 * @param input string input
 * @return ** int 1 if fraction, 0 if not
 */
int isFraction(char *input){
    int x;

    for(x = 0; input[x] != '/' && x < strlen(input); x++){}

    return x < strlen(input) ? 1 : 0;
}

/**
 * @brief determine whether the input is a decimal or fraction
 * 
 * @param input string input of user
 * @return int 0 if decimal, 1 if fraction
 */
int analyzeInput(char *input){
    int type = -1;

    if(correctCharacters(input) && correctFormat(input)){
        type = isFraction(input) ? 1 : 0;
    }

    return type;
}

/**
 * @brief find the correct denominator
 * 
 * @param number decimal places
 * @return ** int correct denominator
 */
int findDenominator(int number){
    int denominator = 1;

    while(number > 0){
        denominator *= 10;
        number /= 10;
    }

    return denominator;
}

/**
 * @brief find GCF of 2 numbers
 * 
 * @param num1 numerator
 * @param num2 denominator
 * @return ** int GCF
 */
int findGCF(int num1, int num2){
    int GCF = 1;
    int min = (num1 < num2) ? num1 : num2;

    int x;

    for(x = 2; x <= min; x++){
        if(num1 % x == 0 && num2 % x == 0){
            GCF = x;
        }
    }

    return GCF;
}

void decimal_to_fraction(char *input){
    char temp[SIZE];
    strcpy(temp, input);

    /* split string: whole number and decimal point */
    float number = atof(temp);
    int whole_number = atoi(strtok(temp, "."));
    int decimal = atoi(strtok(NULL, "."));

    struct fraction frac;

    int denominator = findDenominator(decimal);

    /* convert to fraction */
    frac.numerator = (int) (number * denominator);
    frac.denominator = denominator;

    /* lowest term */
    int GCF = findGCF(frac.numerator, frac.denominator);
    frac.numerator /= GCF;
    frac.denominator /= GCF;

    if(frac.numerator < frac.denominator){
        printf("%s => %d/%d", input, frac.numerator, frac.denominator);
    } else if(frac.numerator > frac.denominator && frac.denominator != 1){
        frac.whole = frac.numerator / frac.denominator;
        frac.numerator %= denominator;
        printf("%s => %d %d/%d", input, frac.whole, frac.numerator, frac.denominator);
    } else {
        printf("%s => %d", input, frac.numerator / frac.denominator);
    }
}

void fraction_to_decimal(char *input){
    char temp[SIZE];
    strcpy(temp, input);

    struct fraction frac;

    frac.numerator = atof(strtok(temp, "/"));
    frac.denominator = atof(strtok(NULL, "/"));
    float decimal = (float) frac.numerator / frac.denominator;

    printf("%s => %f", input, decimal);
}

void main(){
    char input[SIZE];

    char car;

    do{
        printf("\nPress [y] to terminate function: ");
        printf("\nPlease enter a fraction or a decimal: ");
        scanf("%s", input);
        
        if(strcmp(input, "y") != 0 && strcmp(input, "Y") != 0){
            switch(analyzeInput(input)){
                case 0 : decimal_to_fraction(input); break;
                case 1 : fraction_to_decimal(input); break;
                default : printf("Invalid input. Please try again!");
            }
        }
    }while(strcmp(input, "y") != 0 && strcmp(input, "Y") != 0);
}