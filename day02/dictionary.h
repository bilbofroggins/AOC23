#ifndef DICT_H
#define DICT_H

typedef struct dict_t dict_t;

dict_t* dict_init();
void dict_set(dict_t* d, char* key, int val);
int dict_get(dict_t* d, char* key);

#endif // DICT_H
