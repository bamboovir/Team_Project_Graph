
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "hashtable.h"

/* SDBM Hash Function */
unsigned int SDBM_hash(int hashtablesize, char *str)
{
	unsigned int hash = 0;

	while (*str)
	{
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}

	return ((hash & 0x7FFFFFFF) % hashtablesize);
}

struct hashtab *hashtab_create(unsigned int(*hash_value)(int hashtablesize, void *key),
	int(*keycmp)(void *key1, void *key2),
	unsigned int size)
{
	struct hashtab *p;
	unsigned int i;

	p = calloc(1, sizeof(*p));
	if (p == NULL)
		return p;

	p->size = size;
	p->nel = 0;
	p->hash_value = hash_value ? hash_value : SDBM_hash;
	p->keycmp = keycmp ? keycmp : strcmp;
	p->htable = calloc(size, sizeof(*(p->htable)));
	if (p->htable == NULL) {
		free(p);
		return NULL;
	}

	for (i = 0; i < size; i++)
		p->htable[i] = NULL;

	return p;
}

int hashtab_insert(struct hashtab *h, void *key, void *datum)
{
	unsigned int hvalue;
	struct hashtab_node *prev, *cur, *newnode;

	if (!h || h->nel == HASHTAB_MAX_NODES)
		return -EINVAL;

	hvalue = h->hash_value(h->size, key);
	prev = NULL;
	cur = h->htable[hvalue];
	while (cur && h->keycmp(key, cur->key) > 0) {
		prev = cur;
		cur = cur->next;
	}

	if (cur && (h->keycmp(key, cur->key) == 0))
		return -EEXIST;

	newnode = calloc(1, sizeof(*newnode));
	if (newnode == NULL)
		return -ENOMEM;
	newnode->key = key;
	newnode->datum = datum;
	if (prev) {
		newnode->next = prev->next;
		prev->next = newnode;
	}
	else {
		newnode->next = h->htable[hvalue];
		h->htable[hvalue] = newnode;
	}

	h->nel++;
	return 0;
}

void *hashtab_search(struct hashtab *h, void *key)
{
	unsigned int hvalue;
	struct hashtab_node *cur;

	if (!h)
		return NULL;

	hvalue = h->hash_value(h->size, key);
	cur = h->htable[hvalue];
	while (cur != NULL && h->keycmp(key, cur->key) > 0)
		cur = cur->next;

	if (cur == NULL || (h->keycmp(key, cur->key) != 0))
		return NULL;

	return cur->datum;
}

void *hashtab_delete(struct hashtab *h, void *key)
{
	unsigned int hvalue;
	struct hashtab_node *cur;
	struct hashtab_node *prev = NULL;

	if (!h)
		return NULL;

	hvalue = h->hash_value(h->size, key);
	cur = h->htable[hvalue];
	while (cur != NULL && h->keycmp(key, cur->key) > 0)
	{
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL || (h->keycmp(key, cur->key) != 0))
		return NULL;

	if (prev)
		prev->next = cur->next;
	else
		h->htable[hvalue] = cur->next;

	if (cur->datum)	free(cur->datum);
	free(cur->key);
	free(cur);

	return h;
}

void hashtab_destroy(struct hashtab *h)
{
	unsigned int i;
	struct hashtab_node *cur, *temp;

	if (!h)
		return;

	for (i = 0; i < h->size; i++) {
		cur = h->htable[i];
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;

	/*		if (temp->datum)
			{
					free(temp->datum);
			}
            */
			free(temp->key);
			free(temp);
		}
		h->htable[i] = NULL;
	}

	free(h->htable);
	h->htable = NULL;

	free(h);
}


/* print all keys of the hashtable */
int hashtab_print_all_keys(struct hashtab *h)
{
	unsigned int i;
	struct hashtab_node *cur;
	int count = 0;

	if (!h)
		return count;

	for (i = 0; i < h->size; i++) {
		cur = h->htable[i];
		while (cur != NULL) {
			count++;
			printf("%s ", cur->key);
			cur = cur->next;
		}
	}

	return count;
}

