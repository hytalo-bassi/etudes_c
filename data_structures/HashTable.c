#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define FNV_PRIME 1099511628211U
#define FNV_OFFSET_BASIS 14695981039346656037U

typedef struct _entry {
  char *key;
  int val;
} Entry;

typedef struct _ht {
  size_t len;
  size_t cap;
  Entry* entries;
} Ht;

// Hashes a key
// Arguments:
//  char* key: The key to be hashed
// Returns: the FNV-1a hash of the key
uint64_t fnv1a(char *key);

// Initializes a hash table
// Arguments:
//  size_t len: The initial length of the hash table
// Returns: a hash table with all entries defined with key = NULL and
//          val = 0, len = len;
void mkht(Ht *ht, size_t len);

// Free hash table and its entries
// Arguments:
//  Ht* ht: pointer to the hash table
// Returns: nothing
void freeht(Ht* ht);

// Returns the entry of the specified key in Hash Table
// Arguments:
//  Ht* ht: pointer to the hash table
//  char *key: the key
// Returns: the entry or NULL
Entry* ht_get(Ht* ht, char *key);

// Doubles the length of the hash table
// Arguments:
//  Ht* ht: pointer to the hash table
// Returns: nothing
void ht_expand(Ht* ht);


// Places a key in entries. Uses linear probing in case of collisions.
// Arguments:
//  Entry *entry: pointer to the entries
//  size_t cap: pointer to the total number of entries
//  const char *key: the key
//  int val: Value of the key
// Returns: nothing
void ht_set_entry(Entry *entries, size_t cap, const char *key, int val);

// Sets a key in hash table
// Arguments:
//  Ht* ht: pointer to the hash table
//  const char *key: the key
//  int val: the value of the key
// Returns: nothing
void ht_set(Ht *ht, const char *key, int val);

// Prints a hash table
// Arguments:
//  Ht *ht: pointer to the hash table
void print(Ht ht);

int main() {
  char key[1024];
  Ht ht;
  mkht(&ht, 2);

  while (scanf("%1023s", key) != EOF) {
    int val;
    scanf("%d", &val);
    ht_set(&ht, key, val);
  }
  
  print(ht);
  
  printf("%s: %d\n", key, ht_get(&ht, key)->val);

  freeht(&ht);
  return EXIT_SUCCESS;
}

uint64_t fnv1a(char *key) {
  uint64_t hash = FNV_OFFSET_BASIS;
  for (char *c = key; *c; c++) {
    hash ^= (uint64_t)(unsigned char) *c;
    hash *= FNV_PRIME;
  }
  
  return hash;
}

void print(Ht ht) {
  if (ht.len == 0)
    return;

  puts("{");
  for (size_t i = 0; i < ht.cap; i++) {
    Entry e = ht.entries[i];

    if (e.key == NULL)
      continue;

    if (i + 1 == ht.cap)
      printf("\t\"%s\": %d\n", e.key, e.val);
    else
      printf("\t\"%s\": %d,\n", e.key, e.val);
  }

  puts("}");
}

void mkht(Ht *ht, size_t cap) {
  ht->cap = cap;
  ht->len = 0;
  ht->entries = calloc(cap, sizeof(Entry));
}

void freeht(Ht *ht) {
  free(ht->entries);
}

void ht_set(Ht *ht, const char *key, int val) {
  if (ht == NULL)
    return;
  if (key == NULL)
    return;

  ht->len++;
  if ((float) ht->len / ht->cap >= .7)
    ht_expand(ht);

  ht_set_entry(ht->entries, ht->cap, key, val);
}

void ht_set_entry(Entry *entries, size_t cap, const char *key, int val) {
  uint64_t i = fnv1a((char *) key) % cap;
  
  while(entries[i].key != NULL && strcmp(entries[i].key, key) != 0) {
    if (i > cap - 1)
      i = 0;
    else
      i++;
  }

  entries[i].key = strdup((const char *) key);
  entries[i].val = val;
}

void ht_expand(Ht *ht) {
  Entry *new_entries = calloc(ht->cap * 2, sizeof(Entry));
  
  for (size_t i = 0; i < ht->cap; i++) {
    Entry e = ht->entries[i];
    if (e.key != NULL)
      ht_set_entry(new_entries, ht->cap * 2, e.key, e.val);
  }

  free(ht->entries);
  ht->entries = new_entries;
  ht->cap = ht->cap * 2;
}

Entry *ht_get(Ht *ht, char *key) {
  uint64_t i = fnv1a(key) % ht->cap;

  if (strcmp(ht->entries[i].key, key) == 0)
    return ht->entries + i;
  
  uint64_t pos = i + 1;
  
  while (pos != i) {
    if (strcmp(ht->entries[pos].key, key) == 0)
      return ht->entries + pos;
    
    if (pos >= ht->cap - 1)
      pos = 0;
    pos++;
  }

  return NULL;
}
