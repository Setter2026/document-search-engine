#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define TABLE_SIZE 100

typedef struct{
    int doc_count;
    //char documents[]; <- array of strings
    char word[];
}IndexEntry;

typedef struct{
    int entryCount;
    IndexEntry entries[];
}Bucket;

typedef struct{
    int bucket_count;
    Bucket buckets[]; // <- we will store hash itself? Nope
}Hashtable;

unsigned int hash_word(const char *word){
    int i = 0;
    unsigned int hash_code = 0; //hash code is to assign predictable smaller "drawer"

    char letter = tolower(word[i]); //first letter to get number

    while(letter != '\0'){
        hash_code += (letter - 'a') + 1; //get the number of the letter then add to hash_code
        letter = tolower(word[++i]); //then move to next letter
    }

    return hash_code % TABLE_SIZE; //% TABLE_SIZE puts in in another predictable drawer when its too big
}

IndexEntry *find_entry_in_bucket(Bucket, bucket){

}

int insert_word()


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
int main(){
    char *documents[5] = {"/home/shermyn/document-search-engine/files/eh.txt", 
        "/home/shermyn/document-search-engine/files/hello.txt", 
        "/home/shermyn/document-search-engine/files/what.txt"};
    
    //search_engine(documents, "no", 3);
    char word = tolower('A');
    printf("%c", word);
    
}

