#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    //create a pointer to the file argument
    char *dictionary = argv[1];
    //create a string pointer to hold current word
    char *current_word = malloc(45*sizeof(char));
    //open file
   FILE *dp = fopen(dictionary, "r");
    if (dp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }

    while (fscanf (dp, "%s", current_word) != EOF)
    {
        int stringlen = strlen(current_word);

        //iterate through each letter of current word
        for(int i = 0; i < stringlen + 2; i++)
        {
            //full word, then one letter at a time spaced, word length
            printf("\nCurrent Word:%s \tLetters:%c \tValue:%i \tWord Length%i", current_word, current_word[i], \
            current_word[i], stringlen);
        }
        printf("\n");
    }
    fclose(dp);
    free(current_word);
    return 0;

}