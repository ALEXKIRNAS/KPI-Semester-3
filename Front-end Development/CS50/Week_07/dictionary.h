/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
  
// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define HASH_TABLE_SIZE 12000017

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

typedef struct node
{
    // The string to store in the node
    char value[LENGTH + 1];

    // The link to the next node in the list
    struct node* next;
}
node;

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool node_lookup(node *list, const char *val);

/**
 * Puts a new node containing i at the front (head) of the list.
 */
void node_add(node **list, char *val);

/**
 * Frees the space allocated by a single linked list
 */
void node_free(node *list);

/**
 * Debug - prints the contents of a node to a file. File must be opened.
 * Returns a number of elements in the list
 */
int node_print(FILE *f, unsigned int idx, node *list);

typedef struct
{
   // An array of singly-linked lists
   node *values[HASH_TABLE_SIZE];
    
   // The size of a dictionary
   unsigned int dict_size;
}
hash_table;
 
/**
* Initializes a hash-table with a given size
*/
bool hasht_init(hash_table *tbl);
 
/**
* Frees a hash-table
*/
bool hasht_free(hash_table *tbl);
 
/**
* Appends a string to a hash-table
*/
bool hasht_append(hash_table *tbl, char *str);
 
/**
* Checks if a string is in a hash-table
*/
bool hasht_lookup(hash_table *tbl, const char *str);

#endif // DICTIONARY_H
