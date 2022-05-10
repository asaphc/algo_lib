#include <stdlib.h>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct HASH_TABLE* Hash_table_pt;

Hash_table_pt new_hash_table(int size);

int hash_function(char* key);

void add_hash(Hash_table_pt table, void* val, char* key);

void* get_hash(Hash_table_pt table, char* key);

void delete_hash(Hash_table_pt table);

#endif