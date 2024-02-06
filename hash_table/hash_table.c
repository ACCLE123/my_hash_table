//
//  hash_table.c
//  hash_table
//
//  Created by yangqi on 2024/2/6.
//

#include "hash_table.h"
#include "prime.h"

#include <stdlib.h>
#include <string.h>


static ht_item* ht_new_item(const char* key, const char* value) {
//    printf("new item\n");
    
    ht_item* item = malloc(sizeof(ht_item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

static ht_hash_table* ht_new_sized(int base_size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    int size = next_prime(base_size);
    ht->base_size = base_size;
    ht->size = size;
    ht->count = 0;
    ht->items = calloc((size_t)size, sizeof(ht_item*));
    return ht;
}

ht_hash_table* ht_new(void) {
    return ht_new_sized(ht_init_base_size);
}

static void ht_resize(ht_hash_table* ht, int base_size) {
    // we need to change the ht
    if (base_size < ht_init_base_size) return;
    
    ht_hash_table* new_ht = ht_new_sized(base_size);
    
    // copy old to new
    for (int i = 0; i < ht->size; i++)
        if (ht->items[i] != NULL && ht->items[i] != &ht_delete_item)
            ht_insert(new_ht, ht->items[i]->key, ht->items[i]->value);
    
    ht->count = new_ht->count;
    ht->base_size = new_ht->base_size;
    
    const int size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = size;
    
    ht_item** items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = items;
    
    ht_del_hash_table(new_ht);
}

void ht_size_up(ht_hash_table* ht) {
    ht_resize(ht, ht->base_size << 1);
}
static void ht_size_down(ht_hash_table* ht) {
    ht_resize(ht, ht->base_size >> 1);
}

static void ht_del_item(ht_item* item) {
//    printf("del item \n");
    
    free(item->key);
    free(item->value);
    free(item);
}

void ht_del_hash_table(ht_hash_table* ht) {
//    printf("del hash table \n");
    
    for (int i = 0; i < ht->size; i++)
        // use size rather than count, because hash table is not contiguous
        if (ht->items[i] == &ht_delete_item)
            ht->items[i] = NULL;
        else if (ht->items[i] != NULL)
            ht_del_item(ht->items[i]);
    free(ht);
}

static int ht_hash(const char* s, const int p, const int m) {
    const int n = (int)strlen(s);
    int hash = 0;
    for (int i = 0; i < n; i++)
        hash = (hash * p % m + s[i] % m) % m;
    return hash % m;
}

static int ht_get_hash(const char* key, const int m, const int i) {
    const int hash_a = ht_hash(key, prime_1, m);
    const int hash_b = ht_hash(key, prime_2, m);
    return (hash_a + i * (hash_b + 1)) % m;
}


void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load >= 70) ht_size_up(ht);
        
    ht_item* item = ht_new_item(key, value);
    
    int i = 0;
    int index = ht_get_hash(key, ht->size, i++);
    
    ht_item* cur_item = ht->items[index];
    while (cur_item != NULL) {
        if (cur_item == &ht_delete_item) {
            break;
        }
        if (strcmp(cur_item->key, key) == 0) {
            ht_del_item(ht->items[index]);
            ht->items[index] = item;
            return;
        }
        index = ht_get_hash(key, ht->size, i++);
        cur_item = ht->items[index];
    }
    ht->items[index] = item;
    ht->count++;
}
char* ht_search(ht_hash_table* ht, const char* key) {
    int i = 0;
    int index = ht_get_hash(key, ht->size, i++);
    
    ht_item* cur_item =  ht->items[index];
    // in each iterator in loop, we need to check the key
    while (cur_item != NULL && cur_item != &ht_delete_item && strcmp(cur_item->key, key)) {
        index = ht_get_hash(key, ht->size, i++);
        cur_item = ht->items[index];
    }
    
    return cur_item != NULL && cur_item != &ht_delete_item ? cur_item->value : NULL;
}


void ht_delete(ht_hash_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load <= 10) ht_size_down(ht);
    
    int i = 0;
    int index = ht_get_hash(key, ht->size, i++);
    ht_item* cur_item = ht->items[index];
    while (strcmp(cur_item->key, key)) {
        index = ht_get_hash(key, ht->size, i++);
        cur_item = ht->items[index];
    }
    ht->items[index] = &ht_delete_item;
//    ht_del_item(cur_item);
    ht->count--;
}

