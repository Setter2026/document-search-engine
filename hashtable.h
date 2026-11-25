#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 100
#define ENTRIES_SIZE 100
#define WORD_SIZE 50
#define FILENAME_SIZE 256
#define RECORD_SIZE 100


//TO DO: FIX THE COMMENTS

//Store the file's name and how often the word shows up in doc
typedef struct{
    char filename[FILENAME_SIZE];
    int frequency;
}DocumentRecord;

//Stores the word, what documents have that word, and document count
typedef struct{
    int doc_count;
    DocumentRecord record[RECORD_SIZE];
    char word[WORD_SIZE];
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

/// @brief searches if word exist in index
/// @param h 
/// @param word 
/// @param found_entry 
/// @return true if found, false if not
bool search_index(const Hashtable *h, const char *word, IndexEntry *found_entry);

/// @brief grabs words and adds the doc name to its index
/// @param h 
/// @param filename 
/// @return true for success, false for null args, cannot find file, or invalid word insert   
bool index_document(Hashtable *h, const char *filename);

/// @brief does index_document but for multiple documents
/// @param h 
/// @param filenames 
/// @param file_num 
/// @return true for success, false for null args, or invalid individual doc insert
bool index_documents(Hashtable *h, const char *filenames[], const int file_num);

/// @brief Goes through folder and only accepts txt files
/// @param h 
/// @param foldername 
/// @return true for success, false for null args, or insertion failure
bool index_folder(Hashtable *h, const char *foldername);

/// @brief Sorts document record by how often it shows up in file
/// @param e 
void sort_by_frequency(IndexEntry *e);
#endif

