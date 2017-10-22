/*******************************************************************
 * Implements a dictionary's functionality.
 *
 *CS50
 *
 *pset5
 *
 ******************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"

//set root
node* root;
//traversal/movable pointer
node *trav;

//counter for size of dictionary
unsigned int dict_size;

//prototype function
bool recursive_unload(node* tmp);



/********************************************************************************************************
 *
 * Returns true if word is in dictionary else false.
 *******************************************************************************************************/
bool check(const char *word)
{
    //reset trav to point to root
    trav = root;
    //create a variable to hold the length of the current word
    int slen = strlen(word);
    //variable for index to use for children[]
    //unsigned int ind = 0;



    //itterate through each letter in the word
    for (int i = 0; i < slen + 1 ; i++)
    {
        char d = tolower(word[i]);
        //convert chars of word to appropriate ints for children[index]
        if (d == '\'')
        {
            d = 123;
        }

        //if last letter, check if is_word
        if (i == slen)
        {
            if (trav->is_word == true)
                return true;
            else
                return false;
        }

        struct node* new_node = trav->children[d-97];

        //check if the letter entry exists in the dictionary
        if (new_node == NULL)
        {
            return false;
        }
        else
        {
            trav = new_node;
        }



    }

    return false;
}


/**************************************************************************************************************************
 * Loads dictionary into memory. Returns true if successful else false.
 ************************************************************************************************************************/
bool load(const char *dictionary)
{
    //create static root node
    root = calloc(1, sizeof(node));
    trav = root;

    //set dictionary size to zero
    dict_size = 0;

    FILE *dp = fopen(dictionary, "r");
    if (dp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

   //scan in words 1 char at a time from dictionary
    for (char c = fgetc(dp); c != EOF; c = fgetc(dp))
    {
        //check for complete word
        if (c == '\n')
        {
            //verify "word" is at least 1 letter
            if (trav != root)
            {
                //add 1 to the diction size counter
                dict_size ++;
                //set the bool to true for is actually a word
                trav->is_word = true;
                //reset the traversal pointer back to the root
                trav = root;
            }
        }
        //continue mapping word
        else
        {
            //if the character is an apostraphe it's "children" index number will go last/26
            if (c == 39)
                c = 123; //if we want apostraphe to go at end(26)


            //check if path exists
            struct node *new_node = trav->children[c-97];
            if(new_node == NULL)
            {
                trav->children[c-97] = calloc(1, sizeof(node));
                //move trav to new node
                trav = trav->children[c-97];

            }
            else
            {
                trav = new_node;
            }
        }
    }

    fclose(dp);
    return true;
}



/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dict_size;
}

//custom recursive function to imbed inside of unload
bool recursive_unload(node* tmp)
{
    //recursive function
    for (int i = 0; i < 27; i++)
    {
        if( tmp->children[i] != NULL)
        {

            recursive_unload(tmp->children[i]);
        }
    }

    //base case
    free(tmp);
    return true;
}


/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //reset our old friend trav the traveller
    trav = root;

    if (recursive_unload(trav))
    {
        return true;
    }

    else
        return false;
}

