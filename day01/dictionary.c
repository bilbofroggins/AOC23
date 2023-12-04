#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

typedef struct KV {
    char* key;
    int val;
    struct KV* next;
} KV;

struct dict_t {
    KV* dict_list[MAX_SIZE];
};

unsigned long hsh(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % MAX_SIZE;
}

dict_t* dict_init() {
    dict_t* d = calloc(1, sizeof(dict_t));
    return d;
}

void dict_set(dict_t* d, char* key, int val) {
    int hash = hsh(key);

    KV* kv = d->dict_list[hash];

    KV* new_kv = malloc(sizeof(KV));
    new_kv->key = key;
    new_kv->val = val;
    new_kv->next = NULL;
    
    if(kv == NULL) {
        d->dict_list[hash] = new_kv;
        return;
    }
    KV* prev = kv;
    while(kv != NULL) {
        prev = kv;
        if(kv->key == key) {
            kv->val = val;
            free(new_kv);
            return;
        }
        kv = kv->next;
    }
    prev->next = new_kv;
}

int dict_get(dict_t* d, char* key) {
    int hash = hsh(key);

    KV* kv = d->dict_list[hash];
    if(kv == NULL) {
        return -1;
    }
    while(kv != NULL) {
        if(kv->key == key) {
            return kv->val;
        }
        kv = kv->next;
    }
    return -1;
}