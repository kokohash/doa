#include <stdlib.h>
#include <stdio.h>

#include "table.h"
#include "dlist.h"
#include "array_1d.h"

#define HIGH 80000
#define LOW 0

/*
 * Implementation of a generic table for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
 *
 * Duplicates are handled by inspect and remove.
 *
 * Authors: Jaffar El-Tai (hed20jei)
 *	    
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version 2
 *   
 *   
 *   
 */

// ===========INTERNAL DATA TYPES============

struct table {
	array_1d *entries;
	compare_function *key_cmp_func;
	free_function key_free_func;
	free_function value_free_func;
};

struct table_entry {
	void *key;
	void *value;
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

/**
 * table_empty() - Create an empty table.
 * @key_cmp_func: A pointer to a function to be used to compare keys.
 * @key_free_func: A pointer to a function (or NULL) to be called to
 *		   de-allocate memory for keys on remove/kill.
 * @value_free_func: A pointer to a function (or NULL) to be called to
 *		     de-allocate memory for values on remove/kill.
 *
 * Returns: Pointer to a new table.
 */
table *table_empty(compare_function *key_cmp_func,
		   free_function key_free_func,
		   free_function value_free_func)
{
	// Allocate the table header.
	table *t = calloc(1, sizeof(table));
	// Create the list to hold the table_entry-ies.
	t->entries = array_1d_create(LOW, HIGH, NULL);
	// Store the key compare function and key/value free functions.
	
	t->key_cmp_func = key_cmp_func;
	t->key_free_func = key_free_func;
	t->value_free_func = value_free_func;

	return t;
}

/**
 * table_is_empty() - Check if a table is empty.
 * @table: Table to check.
 *
 * Returns: True if table contains no key/value pairs, false otherwise.
 */
bool table_is_empty(const table *t)
{
	bool empty =  array_1d_has_value(t->entries, LOW);

	if (empty == true)
	{
		return false;
	}
	else
	{
		return true; 
	}
	
	
}

/**
 * table_insert() - Add a key/value pair to a table.
 * @table: Table to manipulate.
 * @key: A pointer to the key value.
 * @value: A pointer to the value value.
 *
 * Insert the key/value pair into the table. No test is performed to
 * check if key is a duplicate. table_lookup() will return the latest
 * added value for a duplicate key. table_remove() will remove all
 * duplicates for a given key.
 *
 * Returns: Nothing.
 */
void table_insert(table *t, void *key, void *value)
{
	struct table_entry *entry2;
	bool inserted = false;
	int i = 0;

	for (i = LOW; array_1d_has_value(t->entries, i); i++)
	{
		entry2 = array_1d_inspect_value(t->entries, i);
		if (t->key_cmp_func(entry2->key, key) == 0)
		{
			inserted = true;
			if (t->key_free_func != NULL)
			{
				t->key_free_func(entry2->key);

			}
			if (t->value_free_func != NULL)
			{
				t->value_free_func(entry2->value);
			}
			
			entry2->key = key;
			entry2->value = value;
			array_1d_set_value(t->entries, entry2, i);
				
			break;
		}
	}

	if (inserted == false)
	{	
		// Allocate the key/value structure.
		struct table_entry *entry = malloc(sizeof(struct table_entry));
		// Set the pointers and insert first in the list. This will
		// cause table_lookup() to find the latest added value.
		entry->key = key;
		entry->value = value;

		array_1d_set_value(t->entries, entry, i);
			
	}
}

/**
 * table_lookup() - Look up a given key in a table.
 * @table: Table to inspect.
 * @key: Key to look up.
 *
 * Returns: The value corresponding to a given key, or NULL if the key
 * is not found in the table. If the table contains duplicate keys,
 * the value that was latest inserted will be returned.
 */
void *table_lookup(const table *t, const void *key)
{	
	// Iterate over the list. Return first match.
	struct table_entry *entry;
	for (int i = LOW; array_1d_has_value(t->entries, i); i++)
	{
		if (array_1d_has_value(t->entries, i))
		{
			entry = array_1d_inspect_value(t->entries, i);
			// Inspect the table entry
			// Check if the entry key matches the search key.
			if (t->key_cmp_func(entry->key, key) == 0) 
			{
				// If yes, return the corresponding value pointer.
				return entry->value;
			}
		}
	}
	// No match found. Return NULL.
	return NULL;
}

/**
 * table_choose_key() - Return an arbitrary key.
 * @t: Table to inspect.
 *
 * Return an arbitrary key stored in the table. Can be used together
 * with table_remove() to deconstruct the table. Undefined for an
 * empty table.
 *
 * Returns: An arbitrary key stored in the table.
 */
void *table_choose_key(const table *t)
{
	struct table_entry *entry;
	entry = array_1d_inspect_value(t->entries, LOW);

    return entry->key;
}

/**
 * table_remove() - Remove a key/value pair in the table.
 * @table: Table to manipulate.
 * @key: Key for which to remove pair.
 *
 * Any matching duplicates will be removed. Will call any free
 * functions set for keys/values. Does nothing if key is not found in
 * the table.
 *
 * Returns: Nothing.
 */
void table_remove(table *t, const void *key)
{
	struct table_entry *entry;

	bool removed = false;
	for (int i = LOW; array_1d_has_value(t->entries, i); i++)
	{
		if (!removed)
		{	
			entry = array_1d_inspect_value(t->entries, i);

			if (t->key_cmp_func(entry->key, key) == 0)
			{
				removed = true;

				if (t->key_free_func != NULL)
				{
					t->key_free_func(entry->key);
				}	

				if (t->value_free_func != NULL) 
				{
					t->value_free_func(entry->value);
				}
				
				free(entry);
				array_1d_set_value(t->entries, NULL, i);
			}
		}
		else
		{	
			//removes holes. 
			entry = array_1d_inspect_value(t->entries, i);
			array_1d_set_value(t->entries, entry, i - 1);
			array_1d_set_value(t->entries, NULL, i);
		}
	}
}

/*
 * table_kill() - Destroy a table.
 * @table: Table to destroy.
 *
 * Return all dynamic memory used by the table and its elements. If a
 * free_func was registered for keys and/or values at table creation,
 * it is called each element to free any user-allocated memory
 * occupied by the element values.
 *
 * Returns: Nothing.
 */
void table_kill(table *t)
{
	for (int i = LOW; array_1d_has_value(t->entries, i); i++)
	{
		if (array_1d_has_value(t->entries, i) == true)
		{
			// Inspect the key/value pair.
			struct table_entry *entry = array_1d_inspect_value(t->entries, i);
			// Free key and/or value if given the authority to do so.

			if (t->key_free_func != NULL) 
			{
				t->key_free_func(entry->key);
			}

			if (t->value_free_func != NULL) 
			{
				t->value_free_func(entry->value);
			}

			// Deallocate the table entry structure.
			free(entry);
		}
	}

	array_1d_kill(t->entries);
	free(t);
	
}

/**
 * table_print() - Print the given table.
 * @t: Table to print.
 * @print_func: Function called for each key/value pair in the table.
 *
 * Iterates over the key/value pairs in the table and prints them.
 * Will print all stored elements, including duplicates.
 *
 * Returns: Nothing.
 */
void table_print(const table *t, inspect_callback_pair print_func)
{
	array_1d_print(t->entries, NULL);
}
