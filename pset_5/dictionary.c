// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// idea: create another hash table - cache ???
// idea: create list of common words, but:
//                                        Capitalization aside, your implementation of check should only return true for words actually in dictionary. Beware hard-coding common words (e.g., the), lest we pass your implementation a dictionary without those same words. Moreover, the only possessives allowed are those actually in dictionary. In other words, even if foo is in dictionary, check should return false given foo's if foo's is not also in dictionary


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // case insensitive checking (istnieje funkcja strcasecmp)
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // hash func must be case insensitive
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO: zwalnianie zaalokowanej pamieci, w przypadku, gdy malloc zwroci null.
    char word[LENGTH + 1];
    unsigned int hash_val;
    FILE *file = fopen(dictionary, "r");
    if (file == NULL){
        return false;
    }

    while (fscanf(file, "%s", word) != EOF){
        hash_val = hash(word);
        printf("load word: %s with hash %i\n", word, hash_val);

        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        n->next = NULL;
        
        if (table[hash_val] == NULL){
            table[hash_val] = n;
            printf("add first node to table[%i]\n", hash_val);
        }
        else {
            int i = 0;
            node *tmp = table[hash_val];
            while (tmp->next != NULL){
                tmp = tmp->next;
                i++;
            }
            tmp->next = n;
            printf("add %i node to table[%i]\n", i + 1, hash_val);
        }
    }
    printf("all done\n");
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
