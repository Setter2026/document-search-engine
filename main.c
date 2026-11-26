#include <stdio.h>
#include <string.h>
#include "hashtable.h"


int main(int argc, char *argv[]) {

    printf("======================================\n");
    printf("      Document Search Engine\n");
    printf("======================================\n");

    char folderpath[256];
    printf("Enter folder to index: ");
    if (fgets(folderpath, sizeof(folderpath), stdin) == NULL)  {

        printf("\nError reading input!\n");
        return 1;
    }

    folderpath[strcspn(folderpath, "\n")] = '\0';
    static Hashtable table = {0};

    if(!index_folder(&table, folderpath)){
        printf("\nCannot index folder (perhaps invalid path?)\n");
        return 1;
    }

    
    char query[WORD_SIZE];
    printf("Indexed '%s'. Type a word to search (or 'exit' to quit):\n", folderpath);

    while (1) {
        printf("\nsearch> ");
        if (fgets(query, sizeof(query), stdin) == NULL) break;
        query[strcspn(query, "\n")] = '\0';

        if (strcmp(query, "exit") == 0) break;

        IndexEntry result;
        if(!search_index(&table, query, &result)){
            printf("\nCannot find word\n");
            continue;
        }

        printf("\nResults for '%s' (%d documents)\n", result.word, result.doc_count);
        for(int i = 0; i < result.doc_count; ++i){
            printf("\n%d. %s (%d occurence)", i+1, result.record[i].filename, result.record[i].frequency);
        }

        printf("\n");
    }

    return 0;
}
