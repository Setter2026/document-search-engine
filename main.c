#include <stdio.h>
#include <string.h>
#include <assert.h>

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
    
    search_engine(documents, "no", 3);
    
}

