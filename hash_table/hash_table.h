//
//  hash_table.h
//  hash_table
//
//  Created by yangqi on 2024/2/6.
//

#ifndef hash_table_h
#define hash_table_h

#include <stdio.h>

#endif /* hash_table_h */

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int size;
    int base_size;
    int count;
    ht_item** items;
} ht_hash_table;

static ht_item ht_delete_item = {NULL, NULL};
static int prime_1 = 131;
static int prime_2 = 13331;
static int ht_init_base_size = 50;


void ht_del_hash_table(ht_hash_table* ht);

ht_hash_table* ht_new(void);

void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);

void ht_size_up(ht_hash_table* ht);
