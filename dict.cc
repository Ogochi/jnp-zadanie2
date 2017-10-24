#ifdef NDEBUG
  const bool debug = false;
#else
  const bool debug = true;
#endif

#include <iostream>
#include <string>
#include <map>

static unordered_map<int, unordered_map<string, string> > dicts;

unsigned long dict_new();

void dict_delete(unsigned long id);

size_t dict_size(unsigned long id);

void dict_insert(unsigned long id, const char* key, const char* value);

void dict_remove(unsigned long id, const char* key);

const char* dict_find(unsigned long id, const char* key);

void dict_clear(unsigned long id);

void dict_copy(unsigned long src_id, unsigned long dst_id);
