#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 100
#define ENTRIES_SIZE 100

//Stores the word, what documents have that word, and document count
typedef struct{
    int doc_count;
    char documents[100][256]; 
    char word[50];
}IndexEntry;

//Stores the "minidrawers" of hashtables when multiple entries share the same spot in the index
typedef struct{
    int entryCount;
    IndexEntry entries[ENTRIES_SIZE];
}Bucket;

//The hash table themselves
typedef struct{
    Bucket buckets[TABLE_SIZE];
}Hashtable;

/// @brief inserts word and filepath in hashtable
/// @param word 
/// @param h 
/// @param filename 
/// @return true for success, false if parameters are null or entries or documents is full
bool insert_word(const char *word, Hashtable *h, const char *filename);

/// @brief prints the hashtable
/// @param h 
void print_index(const Hashtable *h);
#endif
