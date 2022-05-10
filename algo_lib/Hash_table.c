#include "basic_utils.h"
#include "Hash_table.h"
#include <string.h>
#include <math.h>

typedef struct HASH_TABLE {
	LinkedList_pt* table;
	int size;
}Hash_table;



typedef struct NODE {
	char* key;
	void* data;
}Node;

Hash_table_pt new_hash_table(int size)
{
	Hash_table_pt table = (Hash_table_pt)malloc(sizeof(Hash_table));
	table->size = size;
	table->table = (LinkedList_pt*)malloc(size * sizeof(LinkedList_pt));
	for (int i = 0; i < size; i++)
		table->table[i] = new_linked_list();
	return table;
}

int hash_function(char* key)
{
	int p = 29;
	int hkey = 0;
	int len = strlen(key);
	int power = 1;
	for (int i = 0; i < len; i++)
	{
		hkey += power * key[i];
		power *= p;
	}
		
	return hkey;
}
void add_hash(Hash_table_pt table,void* val, char* key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
	strcpy(node->key, key);
	node->data = val;
	add_linked(table->table[hash_function(key) % table->size], node);
}

void* get_hash(Hash_table_pt table, char* key)
{
	LinkedList_pt list = table->table[hash_function(key) % table->size];
	reset_list(list);
	Node* node;
	while ((node = (Node*)get_current(list)) != NULL)
	{
		if (strcmp(node->key, key) == 0)
			return node->data;
	}
	return NULL;
}

void delete_hash(Hash_table_pt table)
{
	for (int i = 0; i < table->size; i++)
	{
		LinkedList_pt list = table->table[i];
		reset_list(list);
		Node* node;
		while ((node = (Node*)get_current(list)) != NULL)
		{
			free(node->key);
			free(node);
		}
		delete_list(list);
	}
	free(table->table);
	free(table);
}
