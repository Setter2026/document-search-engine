#include <stdio.h>
#include <string.h>
#include "hashtable.h"


int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("Invalid input\n");
        return 1;
    }
    printf("======================================\n");
    printf("      Document Search Engine\n");
    printf("======================================\n");

    static Hashtable table = {0};
    if(!index_folder(&table, argv[1])){
        printf("Cannot index folder (perhaps invalid path?)");
        return 1;
    }

    char query[WORD_SIZE];
    printf("Indexed '%s'. Type a word to search (or 'exit' to quit):\n", argv[1]);

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

        printf("\n%s: ", result.word);
        for(int i = 0; i < result.doc_count; ++i){
            printf("%s ", result.record[i].filename);
        }

        printf("\n");
    }

    return 0;
}
