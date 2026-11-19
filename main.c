#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#define TABLE_SIZE 100
#define ENTRIES_SIZE 100

typedef struct{
    int doc_count;
    char documents[100][256]; 
    char word[50];
}IndexEntry;

typedef struct{
    int entryCount;
    IndexEntry entries[ENTRIES_SIZE];
}Bucket;

typedef struct{
    Bucket buckets[TABLE_SIZE]; // <- we will store hash itself? Nope
}Hashtable;

bool insert_word(const char *word, Hashtable *h, const char *filename){
    if (word == NULL || h == NULL || filename == NULL || strcmp(word, "") == 0){
        return false;
    }

    char letter = word[0];
    char i = 0;
    int hash_code = 0;

    char copy_word[50];

    while(letter != '\0'){
        if (isalpha(letter))
        {
            hash_code += (tolower(letter) - 'a') + 1;
            copy_word[i] = tolower(letter);
        }
        else if (isdigit(letter))
        {
            hash_code += (letter - '0') + 27;
            copy_word[i] = letter;
        }

        letter = word[++i];

        if (i > 49){
            return false;
        }
    }

    copy_word[i] = '\0';

    hash_code %= TABLE_SIZE;

    Bucket *b = &h->buckets[hash_code];

    bool found = false;
    
    if (b->entryCount >= ENTRIES_SIZE){
        return false;
    }
    
    bool existing_word = false;
    
    for(int i = 0; i < b->entryCount; ++i){
        if (strcmp(b->entries[i].word, copy_word) == 0){
            found = true;
            for(int j = 0; j < b->entries[i].doc_count; ++j){
                if (strcmp(b->entries[i].documents[j], filename) == 0){
                    existing_word = true;
                    break;
                }
            }
    
            if (!existing_word){
                if (b->entries[i].doc_count >= 100 || strlen(filename) >= 256){
                    return false;
                }
                ++b->entries[i].doc_count;
                strcpy(b->entries[i].documents[b->entries[i].doc_count - 1], filename);
                break;
            }
        }
    }
    
    if (!found){
        IndexEntry e;
        e.doc_count = 1;
        strcpy(e.word, copy_word);
        strcpy(e.documents[0], filename);
        
        ++b->entryCount;
        b->entries[b->entryCount - 1] = e; 
    }
    return true;
}

bool search_document(char filename[], char query[]){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\nFile where?");
        return false;
    }

    char line[256];
    const char *delimiters = ", \t\r\n";

    while(fgets(line, sizeof(line), fp) != NULL){
        char *word = strtok(line, delimiters);
        while(word != NULL){
            if (strcmp(word, query) == 0){
                fclose(fp);
                return true;                
            }
            word = strtok(NULL, delimiters);
        }
    }

    fclose(fp);
    return false;
}

void search_engine(char *documents[], char query[], int doc_count){
    for(int i = 0; i < doc_count; ++i){
        if (search_document(documents[i], query)){
            printf("-%s\n", documents[i]);
        }
    }
}

void print_index(Hashtable *h){
    if (h == NULL){
        return;
    }

    for(int i = 0; i < TABLE_SIZE; ++i){
        for(int j = 0; j < h->buckets[i].entryCount; ++j){
            if (h->buckets[i].entries[j].doc_count > 0){
                printf("Bucket %d\n", i);
                printf("     word: %s -> ", h->buckets[i].entries[j].word);
                for(int k = 0; k < h->buckets[i].entries[j].doc_count; ++k){
                    printf("%s | ", h->buckets[i].entries[j].documents[k]);
                }
                printf("\n");
            }
        }    
    }
}

int main(void) {
    static Hashtable h = {0}; // Zero-initialize entire table


    // Test 1: Normal inserts across multiple files
    assert(insert_word("apple", &h, "/home/shermyn/document-search-engine/files/eh.txt") || strcmp(h.buckets->entries[0].word, "apple") == 0 
    || strcmp(h.buckets[0].entries->documents[0], "/home/shermyn/document-search-engine/files/eh.txt") == 0 || h.buckets->entryCount == 1);

    insert_word("apple", &h, "doc2.txt");
    insert_word("banana", &h, "doc1.txt");

    // Test 2: Duplicate word in the SAME file (should NOT increment doc_count)
    insert_word("apple", &h, "doc1.txt");

    // Test 3: Uppercase & symbols (should NOT crash with negative hash)
    insert_word("Apple123", &h, "doc3.txt");

    // Test 4: Empty and NULL inputs (should safely do nothing)
    insert_word("", &h, "doc1.txt");
    //insert_word(NULL, &h, "doc1.txt");

    print_index(&h);
    return 0;
}




