/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

hash_table dict;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return hasht_lookup(&dict, word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Open the file
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
        return false;
    
    // Initialize the hash table
    hasht_init(&dict);
    
    // Load words from dictionary
    char buffer[LENGTH + 2];
    while (fgets(buffer, LENGTH + 2, f))
    {
        // Overwrite \n with \0
        buffer[strlen(buffer) - 1] = '\0';
        
        // Append the word to the hash table
        hasht_append(&dict, buffer);
    }
    
    // Debug - print the contents of a hash-table
    #ifdef DEBUG
    hasht_print(&dict);
    #endif
        
    fclose(f);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dict.dict_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return hasht_free(&dict);
}

unsigned long hash(const char *str)
{
    unsigned long hash_val = 5381;
    int c;
    
    while ((c = *str++))
    {
        hash_val = ((hash_val << 5) + hash_val) + tolower(c);
    }
    
    return hash_val;
}

/**
* Initializes a hash-table with a given size
*/
bool hasht_init(hash_table *tbl)
{
    tbl->dict_size = 0;
    
    return true;
}
 
/**
* Frees a hash-table
*/
bool hasht_free(hash_table *tbl)
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
        node_free(tbl->values[i]);
    
    return true;
}
 
/**
* Appends a string to a hash-table
*/
bool hasht_append(hash_table *tbl, char *str)
{
    // Calculate the correct hash
    unsigned int hash_value = hash(str) % HASH_TABLE_SIZE;
    
    // Append the string
    node_add(&(tbl->values[hash_value]), str);
    
    tbl->dict_size++;
    
    return true;
}
 
/**
* Checks if a string is in a hash-table
*/
bool hasht_lookup(hash_table *tbl, const char *str)
{   
    // Calculate the correct hash
    unsigned int hash_value = hash(str) % HASH_TABLE_SIZE;
    
    // Find the string
    return node_lookup(tbl->values[hash_value], str);
}

/**
 * Creates a new node.
 */
node *new_node(char *val)
{
    node *result = (node *)malloc(sizeof(node));
    
    strncpy(result->value, val, strlen(val) + 1);   // Copy the string
    result->next = NULL;
    
    return result;
}

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool node_lookup(node *list, const char *val)
{
    node *t = list;
    
    while (t != NULL)
    {
        if (!(strcasecmp(val, t->value)))   // Case-insensitive comparing
            return true;
    
        t = t->next;
    }
    
    return false;
}

/**
 * Puts a new node containing i at the front (head) of the list.
 */
void node_add(node **list, char *val)
{
    node *new = new_node(val);
    
    new->next = *list;
    *list = new;
}

/**
 * Frees the space allocated by a single linked list.
 */
void node_free(node *list)
{
    node *t = list;
    
    while (t != NULL)
    {
        node* next = t->next;
        
        free(t);
        
        t = next;
    }
}

/**
 * Debug - prints the contents of a node to a file. File must be opened.
 * Returns a number of elements in the list
 */
int node_print(FILE *f, unsigned int idx, node *list)
{
    int count = 0;
    node *t = list;
    
    if (t != NULL)
    {
        fprintf(f, "%d:\t", idx);
        
        while (t != NULL)
        {
            fprintf(f, "%s\t", t->value);
            t = t->next;
            count++;
        }
        
        fprintf(f, "\n");
    }
    
    return count;
}