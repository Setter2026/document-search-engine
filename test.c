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
    assert(strcmp(result.record[0].filename, "doc1.txt") == 0);

    assert(search_index(&table, "CAT", &result));
    assert(strcmp(result.word, "cat") == 0);
    assert(result.doc_count == 1);
    assert(strcmp(result.record[0].filename, "doc1.txt") == 0);


    assert(!search_index(&table, "dog", &result));

    assert(search_index(&table, "mouse", &result));
    assert(strcmp(result.word, "mouse") == 0);
    assert(result.doc_count == 1);
    assert(strcmp(result.record[0].filename, "doc2.txt") == 0);
}

void test_normal_index_doc(void){
    static Hashtable table = {0};

    assert(index_document(&table, "sample_files/doc1.txt"));

    IndexEntry result;

    assert(search_index(&table, "cat", &result));
    assert(strcmp(result.word, "cat") == 0 && strcmp(result.record[0].filename, "sample_files/doc1.txt") == 0 && result.doc_count == 1);
}

void test_normal_index_docs(void){
    static Hashtable table = {0};

    const char *files[] = {
        "sample_files/doc1.txt",
        "sample_files/doc2.txt",
        "sample_files/doc3.txt"
    };

    assert(index_documents(&table, files, 3));

    IndexEntry result;
    assert(search_index(&table, "cat", &result));
    assert(strcmp(result.word, "cat") == 0);
    assert(result.doc_count == 2);

    assert(search_index(&table, "dog", &result));
    assert(strcmp(result.word, "dog") == 0);
    assert(result.doc_count == 2);


    assert(search_index(&table, "mouse", &result));
    assert(strcmp(result.word, "mouse") == 0);
    assert(result.doc_count == 2);
}

void test_normal_index_folder(void){
    static Hashtable table = {0};

    assert(index_folder(&table, "sample_files"));
    
    IndexEntry result;
    assert(search_index(&table, "cat", &result));
    assert(strcmp(result.word, "cat") == 0);
    assert(result.doc_count == 2);

    assert(search_index(&table, "dog", &result));
    assert(strcmp(result.word, "dog") == 0);
    assert(result.doc_count == 2);


    assert(search_index(&table, "mouse", &result));
    assert(strcmp(result.word, "mouse") == 0);
    assert(result.doc_count == 2);
}

 void test_frequency_feature(void) {

    static Hashtable table = {0};

    insert_word("cat", &table, "doc1.txt");
    insert_word("dog", &table, "doc1.txt");
    insert_word("dog", &table, "doc1.txt");
    insert_word("dog", &table, "doc1.txt");
    insert_word("cat", &table, "doc2.txt");
    insert_word("cat", &table, "doc2.txt");
    insert_word("bird", &table, "doc3.txt");

   IndexEntry result;

   assert(search_index(&table, "cat", &result));
   assert(result.record[0].frequency == 2);

   assert(search_index(&table, "dog", &result));
   assert(result.record[0].frequency == 3);

   assert(search_index(&table, "bird", &result));
   assert(result.record[0].frequency == 1);

}

void test_sorting_by_frequency(void){

    static Hashtable table = {0};

    insert_word("cat", &table, "doc1.txt");
    insert_word("cat", &table, "doc2.txt");
    insert_word("cat", &table, "doc2.txt");
    insert_word("cat", &table, "doc2.txt");
    insert_word("cat", &table, "doc3.txt");
    insert_word("cat", &table, "doc3.txt");

    IndexEntry result;
    assert(search_index(&table, "cat", &result));
    sort_by_frequency(&result);

    assert(strcmp(result.record[0].filename, "doc2.txt") == 0);
    assert(strcmp(result.record[1].filename, "doc3.txt") == 0);
    assert(strcmp(result.record[2].filename, "doc1.txt") == 0);
}


int main(void) {
    printf("Running Hashtable Unit Tests...\n\n");

    //test_normal_inserts();
    test_normal_search();
    test_normal_index_doc();
    test_normal_index_docs();
    test_normal_index_folder();
    test_frequency_feature();
    test_sorting_by_frequency();

    printf("\nAll separate tests passed!\n");
    return 0;
}
