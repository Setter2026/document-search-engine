#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "hashtable.h"

void test_normal_inserts(void) {
    static Hashtable h = {0};

    Hashtable table = {0};

    insert_word("cat", &table, "doc1.txt");
    insert_word("dog", &table, "doc1.txt");
    insert_word("cat", &table, "doc2.txt");
    insert_word("bird", &table, "doc3.txt");

    print_index(&table);
}


int main(void) {
    printf("Running Hashtable Unit Tests...\n\n");

    test_normal_inserts();
    test_duplicates_and_case();
    test_invalid_inputs();
    test_collisions();

    printf("\nAll separate tests passed!\n");
    return 0;
}
