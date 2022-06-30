#include <stdlib.h>
#include <stdio.h>
#include "hash_tables.h"


/**
 * shash_table_create - creates a sorted hash table
 * @size: size of the array of the table
 * Return: pointer to the table
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *sht;

	if (size < 1)
		return (NULL);

	sht = malloc(sizeof(shash_table_t));

	if (sht == NULL)
		return (NULL);

	sht->size = size;
	sht->array = calloc(size, sizeof(shash_node_t *));
	sht->shead = NULL;
	sht->stail = NULL;

	if (sht->array == NULL)
	{
		free(sht);
		return (NULL);
	}

	return (sht);
}

/**
 * shash_table_set - set key / value pair in the hash table
 * @ht: ptr to the hash table
 * @key: the key
 * @value: value associated to the key
 * Return: 1 on success 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	int idx;
	shash_node_t *node, *tmp;

	if (key == NULL || strlen(key) == 0 || ht == NULL)
		return (0);
	idx = key_index((unsigned char *) key, ht->size), node = ht->array[idx];
	while (node != NULL)
	{
		if (strcmp(node->key, key) == 0)
		{
			free(node->value), node->value = strdup(value);
			return (1);
		}
		node = node->next; }
	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (0);
	node->key = strdup(key), node->value = strdup(value);
	node->next = ht->array[idx], ht->array[idx] = node;
	if (ht->shead == NULL)
	{
		ht->shead = node, node->sprev = NULL, node->snext = NULL, ht->stail = node;
		return (1); }
	tmp = ht->shead;
	while (tmp != NULL)
	{
		if (strcmp(node->key, tmp->key) < 0)
		{
			node->snext = tmp, node->sprev = tmp->sprev;
			if (tmp->sprev != NULL)
				tmp->sprev->snext = node;
			else
				ht->shead = node;
			tmp->sprev = node;
			return (1); }
		if (tmp->snext == NULL)
		{
			tmp->snext = node, node->sprev = tmp, node->snext = NULL, ht->stail = node;
			return (1); }
		tmp = tmp->snext; }
	return (0); }

/**
 * shash_table_get - gets value of a key from a sorted hash table
 * @ht: hash table
 * @key: the key to look for
 * Return: the value
 */

char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int idx;
	shash_node_t *node;

	if (ht == NULL || key == NULL || strlen(key) == 0)
		return (NULL);

	idx = key_index((unsigned char *) key, ht->size);

	if (ht->array[idx] == NULL || ht->array[idx] == 0)
		return (NULL);

	if (strcmp(ht->array[idx]->key, key) == 0)
		return (ht->array[idx]->value);
	node = ht->array[idx];
	while (node != NULL)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}

	return (NULL);
}

/**
 * shash_table_print - printthe hash table in the sorted way
 * @ht: pointer to the hash table
 * Return: void
 */

void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;
	int flag = 0;

	if (ht == NULL || ht->shead == NULL)
		return;

	printf("{");
	node = ht->shead;
	while (node != NULL)
	{
		if (flag == 1)
			printf(", ");

		if (node->snext == NULL)
		{
			printf("'%s': '%s'", node->key, node->value);
			flag = 1;
			break;
		}

		flag = 1;
		printf("'%s': '%s'", node->key, node->value);
		node = node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - printthe hash table in reverse
 * @ht: pointer to hash table
 * Return: void
 */

void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;
	int flag = 0;

	if (ht == NULL || ht->stail == NULL)
	return;

	printf("{");
	node = ht->stail;
	while (node != NULL)
	{
		if (flag == 1)
			printf(", ");

		if (node->sprev == NULL)
		{
			printf("'%s': '%s'", node->key, node->value);
			flag = 1;
			break;
		}

		flag = 1;
		printf("'%s': '%s'", node->key, node->value);
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - delete the sorted hash table
 * @ht: pointer to the hash table
 * Return: void
 */

void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node, *tmp;
	unsigned long int i;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		if (node != NULL)
		{
			if (node->next == NULL)
			{
				free(node->value);
				free(node->key);
				free(node);
				continue;
			}
			while (node != NULL)
			{
				tmp = node;
				node = node->next;
				free(tmp->value);
				free(tmp->key);
				free(tmp);
			}
		}
	}
	free(ht->array);
	free(ht);
}
