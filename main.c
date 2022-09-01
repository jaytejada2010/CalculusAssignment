#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100

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

int findDenominator(int number){
    int denominator = 1;

    while(number > 0){
        denominator *= 10;
        number /= 10;
    }

    return denominator;
}

void decimal_to_fraction(char *input){
    /* split string: whole number and decimal point */
    int whole_number = atoi(strtok(input, "."));
    int decimal = atoi(strtok(NULL, "."));

    printf("%d %d %d", whole_number, decimal, findDenominator(decimal));

    int denominator = 1;
}

void fraction_to_decimal(char *input){
    float numerator = atof(strtok(input, "/"));
    float denominator = atof(strtok(NULL, "/"));
    float decimal = numerator / denominator;

    printf("%s => %.2f", input, decimal);
}

void main(){
    char input[SIZE];

    printf("Please enter a decimal or a fraction: ");
    scanf("%s", input);
    
    switch(analyzeInput(input)){
        case 0 : decimal_to_fraction(input); break;
        case 1 : fraction_to_decimal(input); break;
        default : printf("Invalid input");
    }
}