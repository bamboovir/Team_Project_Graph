
#ifndef MY_HASHTABLE_H
#define MY_HASHTABLE_H 

#define HASHTAB_MAX_NODES 10000
#define EINVAL 1
#define EEXIST 2
#define ENOMEM 3

struct hashtab_node {
	void *key;
	void *datum;
	struct hashtab_node *next;
};

struct hashtab {
	struct hashtab_node **htable;					 /* hash table */
	unsigned int size;                               /* number of slots in hash table */
	unsigned int nel;                                /* number of elements in hash table */
	unsigned int(*hash_value)(int hashtablesize, void *key);            /* hash function */
	int(*keycmp)(void *key1, void *key2);			 /* key comparison function */
};

struct hashtab *hashtab_create(unsigned int(*hash_value)(int hashtablesize, void *key),
	int(*keycmp)(void *key1, void *key2),
	unsigned int size);
int hashtab_insert(struct hashtab *h, void *key, void *datum);
void *hashtab_search(struct hashtab *h, void *key);
void *hashtab_delete(struct hashtab *h, void *key);
void hashtab_destroy(struct hashtab *h);
int hashtab_print_all_keys(struct hashtab *h);

#endif
