#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

