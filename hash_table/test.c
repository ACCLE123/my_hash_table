//
//  test.c
//  hash_table
//
//  Created by yangqi on 2024/2/6.
//

#include "test.h"
#include "hash_table.h"

void test1(void) {
    ht_hash_table* t1 = ht_new();
    char* key = NULL;
    char* value = NULL;
    
    key = "hello";
    value = "world";
    ht_insert(t1, key, value);
    
    printf("count: %d\nsize: %d\n", t1->count, t1->size);
    printf("key : %s\nvalue : %s\n", key, value);
    printf("\n");
    
    ht_delete(t1, key);
    value = ht_search(t1, key);
    printf("count: %d\nsize: %d\n", t1->count, t1->size);
    printf("key : %s\nvalue : %s\n", key, value);
    printf("\n");
    
    ht_insert(t1, key, "yangqi");
    value = ht_search(t1, key);
    printf("count: %d\nsize: %d\n", t1->count, t1->size);
    printf("key : %s\nvalue : %s\n", key, value);
    printf("\n");
    
    ht_del_hash_table(t1);
}

void test2(void) {
    ht_hash_table* t1 = ht_new();
    char* key = NULL;
    char* value = NULL;

    for (char i = 'a'; i <= 'z'; i++) {
        for (int j = 'a'; j <= 'z'; j++) {
            char* str = (char *)malloc(3 * sizeof(char));
            str[0] = i;
            str[1] = j;
            str[2] = '\0';
            key = str;
            ht_insert(t1, key, str);
            value = ht_search(t1, key);
            printf("count: %d\nsize: %d\n", t1->count, t1->size);
            printf("key : %s\nvalue : %s\n", key, value);
            printf("\n");
        }
    }
    ht_del_hash_table(t1);
}

void test3(void) {
    ht_hash_table* t1 = ht_new();
    char* key = NULL;
    char* value = NULL;
    
    key = "hello";
    value = "world";
    ht_insert(t1, key, value);
    
    ht_size_up(t1);
    ht_size_up(t1);
    ht_size_up(t1);
    printf("count: %d\nsize: %d\n", t1->count, t1->size);
    printf("key : %s\nvalue : %s\n", key, value);
    printf("\n");
    
    ht_delete(t1, key);
    value = ht_search(t1, key);
    printf("count: %d\nsize: %d\n", t1->count, t1->size);
    printf("key : %s\nvalue : %s\n", key, value);
    printf("\n");
}
