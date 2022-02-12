#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 100

struct SubstringParams {
    int startIndex;
    int length;
};

int charToInt(char c) {
    int x = c - '0';
    return x;
}

//checks if char is valid for our double substring, returns 0 if bad, returns 1 if good
int forDub(char c) {
    int arr[] = {46, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
    int size = sizeof(arr)/sizeof(arr[0]);
    int dub = 0;
    for (int i = 0; i < size; i++) {
        if (c == arr[i]) {
            dub = 1;
        }
    }
    return dub;
}

//checks if given character is an opperator
int isOpp(char c) {
    int arr[] = {42, 43, 45, 47};
    int size = sizeof(arr)/sizeof(arr[0]);
    int opp = 0;
    for (int i = 0; i < size; i++) {
        if (c == arr[i]) {
            opp = 1;
        }
    }
    return opp;
}

double strToNum(char str[SIZE]){
    //instance variables
    double returnDub;
    //boolean trackers
    int endDub = 0;
    int endOpp = 0;
    int endExpo = 0;
    int whitespace= 0;
    //counter
    int whitespaceCount = 0;
    //tracking substrings and vars
    struct SubstringParams dub;
    struct SubstringParams expo; 
    char opp;
    
    //putting placehold vals in the structs
    dub.startIndex = -1;
    dub.length = -1;
    expo.startIndex = -1;
    expo.length = -1;

    //loop that will find us our substrings and assign the opperation
    for (int i = 0; i < SIZE; i++) {
        //gets rid of whitespace characters
        if (str[i] == ' ') {
            whitespace = 1;
            whitespaceCount++;
        } else {
            whitespace = 0;
            whitespaceCount = 0;
        }

        //tracks double substring
        if (endDub == 0 && whitespace == 0 && dub.startIndex == -1) {
            dub.startIndex = i;
            dub.length = 1;
        } else if (endDub != 1) {
            if (forDub(str[i]) == 0) {
                printf("vals for tracking dub substring\nendDub: %d\nendOpp: %d\nendExpo: %d\ndub.startIndex: %d\ndub.length: %d", endDub, endOpp, endExpo, dub.startIndex, dub.length);
                endDub = 1;
            } else {
                dub.length++;
                printf("dub.length: %d\n", dub.length);
            }
        }
        //assigns our opperator character
        if (endDub == 1 && isOpp == 1 && endOpp == 0) {
            opp = str[i];
            printf("vals for tracking opperator\nendDub: %d\nendOpp: %d\nendExpo: %d\nopp: %c", endDub, endOpp, endExpo, opp);
            endOpp = 1;
        }
        //tracks exponent substring
        if (endDub == 1 && endOpp == 1 && whitespace == 0) {
            if (str[i] == 40) {
                expo.startIndex = i+1;
                expo.length = 0;
                printf("vals for tracking expo substring\nendDub: %d\nendOpp: %d\nendExpo: %d\nexpo.startIndex: %d\nexpo.length: %d", endDub, endOpp, endExpo, expo.startIndex, expo.length);

            } 
            if (expo.startIndex != -1 && str[i] != 41) {
                expo.length++;
            }
            if (str[i] == 41) {
                endExpo = 1;
            }
        }
    }
    printf("dub struct vals %d %d", dub.startIndex, dub.length);
    printf("expo struct vals %d %d", expo.startIndex, expo.length);
    printf("opp val %c", opp);
    //building the substrings into their own arrays
    char dubArr[dub.length];
        for (int s = 0; s < dub.length; s++) {
            dubArr[s] = str[dub.startIndex + s];
        }
    char expoArr[expo.length];
        for (int e = 0; e < expo.length; e++) {
            expoArr[e] = str[expo.length + e];
        }
    //testing strtod function
    printf("given double is: %s\n", dubArr);
    printf("given opperator is: %c\n", opp);
    printf("given exponent is: %s\n", expoArr);
    returnDub = atof(dubArr);
    return returnDub;
}

int main() {
    char equation[SIZE];
    printf("Enter your input number in the following format a.b x 10^(e)\n");
    scanf(" %s", equation);
    double dub = strToNum(equation);
    printf("double entered %f", dub);
    return 0;
}