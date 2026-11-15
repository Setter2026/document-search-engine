#include <stdio.h>
#include <string.h>
#include <assert.h>

bool search_document(char filename[], char query[]){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
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

int main(){
    assert(search_document("hello.txt", "no"));
    
}

