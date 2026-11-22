#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "hashtable.h"

void test_normal_inserts(void) {
     static Hashtable table = {0};

    insert_word("cat", &table, "doc1.txt");
    insert_word("dog", &table, "doc1.txt");
    insert_word("cat", &table, "doc2.txt");
    insert_word("bird", &table, "doc3.txt");

    print_index(&table);
}

void test_normal_search(void){
    static Hashtable table = {0};
    assert(insert_word("CAT", &table, "doc1.txt"));
    assert(insert_word("mouse", &table, "doc2.txt"));

    IndexEntry result;

    assert(search_index(&table, "cat", &result));
    assert(strcmp(result.word, "cat") == 0);
    assert(result.doc_count == 1);
    assert(strcmp(result.documents[0], "doc1.txt") == 0);

    assert(search_index(&table, "CAT", &result));
    assert(strcmp(result.word, "cat") == 0);
    assert(result.doc_count == 1);
    assert(strcmp(result.documents[0], "doc1.txt") == 0);


    assert(!search_index(&table, "dog", &result));

    assert(search_index(&table, "mouse", &result));
    assert(strcmp(result.word, "mouse") == 0);
    assert(result.doc_count == 1);
    assert(strcmp(result.documents[0], "doc2.txt") == 0);
}

int main(void) {
    printf("Running Hashtable Unit Tests...\n\n");

    test_normal_inserts();
    test_normal_search();


    printf("\nAll separate tests passed!\n");
    return 0;
}
