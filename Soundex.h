#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>

// soundexTable - soundex encoding of each alphabet, according to alphabetical position
// A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z 
static const char soundexTable[26] = {'0','1','2','3','0','1','2','*','0','2','2','4','5','5','0','1','2','6','2','3','0','1','*','2','0','2'}; 


/* Function Prototypes */
void deleteCharFromStringByIndex(char *inputString, int charIndex);
void generateSoundex_ReplaceCharacters(const char *inputString, char *soundex);
int compareSubstringForSoundex(char *soundex, int index);
void generateSoundex_SimplifyAdjacentCharactersSeparatedBySoundex(char *soundex);
void generateSoundex_SimplifyRepeatedAdjacentCharacters(char *soundex);
void generateSoundex_RemoveVowels(char *soundex);
void generateSoundex_AddZeroPadding(char *soundex);
int calculateSoundexStartingLength(const char *inputString);
void generateSoundex(const char *inputString, char *soundex);

/* Function Description: delete the character at the given index from the given string */
/* Parameters:
      inputString - string from which a character to be deleted
      charIndex - index of the character which is to be deleted
*/
void deleteCharFromStringByIndex(char *inputString, int charIndex) {        
    int len = strlen(inputString); /* len - length of the input string */
    for(int index = charIndex; index < len-1; ++index) {
        inputString[index] = inputString[index+1];
    }
    inputString[index] = '\0';            //Inserting NULL character
}

/* Function Description: replace characters of the input string with their corresponding soundex encoding */
/* Parameters:
      inputString - input string whose characters are to be replaced
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_ReplaceCharacters(const char *inputString, char *soundex) { 
    int sIndex = 0; /* sIndex - index of soundex at which the next code is to be inserted */
    int index = 0;
    
    while(inputString[index] != '\0') {
        if(isalpha(inputString[index])) {
            soundex[sIndex++] = soundexTable[(toupper(inputString[index]) - 65)];
        }
        ++index;
    }
    
    soundex[sIndex] = '\0';
}


/* Function Description: checks if the 3-character substring is a string with the same character separated by '*' (which is the encoding for h and w) */
/* Parameters:
      soundex - string with soundex code (intermediate)
      index - index of the soundex code to checked for separation by h or w
*/
int compareSubstringForSoundex(char *soundex, int index) {
    char substr1[4] = {soundex[index-2],soundex[index-1],soundex[index],'\0'}; /* substr1 - substring from the soundex code */
    char substr2[4] = {soundex[index],'*',soundex[index],'\0'}; /* substr2 - substring in the format [character_at_index][*][character_at_index] */
    return (!strcmp(substr1, substr2));
}

/* Function Description: removes adjacent characters that are separated by either 'h' or 'w', if they encode to the same value */
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_SimplifyAdjacentCharactersSeparatedBySoundex(char *soundex) {
    int index = 2;
    while(soundex[index] != '\0') {
        if(compareSubstringForSoundex(soundex,index)) {
            deleteCharFromStringByIndex(soundex,index);
        } else {
            ++index;
        }
    }
}

/* Function Description: removes adjacent characters that encode the same value */
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_SimplifyRepeatedAdjacentCharacters(char *soundex) {
    int index = 1;
    while(soundex[index] != '\0') {
        if(soundex[index] == soundex[index-1]) {
            deleteCharFromStringByIndex(soundex,index);
        } else {
            ++index;
        }
    }
}

/* Function Description: removes a,e,i,o,u,y,h,w from the soundex code */
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_RemoveVowels(char *soundex) {
    int index = 1;
    while(soundex[index] != '\0') {
        if((strchr("0*", soundex[index]))) {
            deleteCharFromStringByIndex(soundex,index);
        } else {
            ++index;
        }
    }
}

/* Function Description: pads the soundex code with zeros, if it is less than 4 characters */
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_AddZeroPadding(char *soundex) {
    int len = strlen(soundex); /* len - current length of the soundex code */
    while(len < 4) {
        soundex[len++] = '0';
    }
    soundex[4] = '\0';
}

/* Function Description: calculates the required length of the intermediate soundex code string */
/* Parameters:
      inputString - string whose soundex is to be calculated
*/
int calculateSoundexStartingLength(const char *inputString) {
    return (strlen(inputString) < 5) ? 5 : strlen(inputString);
}

/* Function Description: generates the soundex code for the given input string */
/* Parameters:
      inputString - input string whose soundex code is to be generated
      soundex - string with soundex code (intermediate)
*/
void generateSoundex(const char *inputString, char *soundex) {
    /* check for empty string */
    if(strlen(inputString) == 0) {
        strcpy(soundex,"\0");
    } else {
        /* creating a temporary soundex string to hold indermediate soundex code */
        char soundexTemp[calculateSoundexStartingLength(inputString)];
       
        generateSoundex_ReplaceCharacters(inputString, soundexTemp);        
        generateSoundex_SimplifyAdjacentCharactersSeparatedBySoundex(soundexTemp);        
        generateSoundex_SimplifyRepeatedAdjacentCharacters(soundexTemp);        
        generateSoundex_RemoveVowels(soundexTemp);        
        generateSoundex_AddZeroPadding(soundexTemp);
        soundexTemp[0] = toupper(inputString[0]); /* First character of the input string is retained */

        /* copy the final soundex code into the function argument */
        strcpy(soundex,soundexTemp);
    }
}

#endif // SOUNDEX_H
