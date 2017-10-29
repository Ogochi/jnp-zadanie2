#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include "dict.h"
#include "dictglobal.h"

#ifdef NDEBUG
  const bool debug = false;
#else
  const bool debug = true;
#endif

using std::size_t;
using std::string;
using std::unordered_map;
using std::make_pair;
using DICT = unordered_map<string, string>;

static unordered_map<unsigned long, DICT > dicts ( {{dict_global(), DICT ()}} );
static unsigned long id_for_new_dict = 1;

unsigned long dict_new() {
  DICT new_dict;

  dicts.insert({id_for_new_dict, new_dict});
  return id_for_new_dict++;
}

void dict_delete(unsigned long id) {
  if (dicts.find(id) != dicts.end() && id != dict_global())
    dicts.erase(id);
}

size_t dict_size(unsigned long id) {
  unordered_map<unsigned long, DICT >::iterator it = dicts.find(id);

  if (it != dicts.end())
    return (it -> second).size();
  else
    return 0;
}

void dict_insert(unsigned long id, const char* key, const char* value) {
  if (key == NULL ||  value == NULL)
    return;
  auto dictIter = dicts.find(id);
  if (dictIter == dicts.end())
    return;
  dictIter -> second.insert(std::make_pair<string,string>(string(key),
                                                        string(value)));
}

void dict_remove(unsigned long id, const char* key) {
  auto dictIter = dicts.find(id);
  string s_key(key);
  if (dictIter != dicts.end() &&
      dictIter -> second.find(s_key) != dictIter -> second.end()) {
    dictIter -> second.erase(s_key);
  }
}

const char* dict_find(unsigned long id, const char* key) {
  auto dictIter = dicts.find(id);
  string s_key(key);

  if (dictIter == dicts.end() ||
      dictIter -> second.find(s_key) == dictIter -> second.end()) {
    auto globalIter = dicts.find(dict_global());
    auto foundIter = globalIter -> second.find(s_key);
    if (foundIter == globalIter -> second.end())
      return NULL;
    else
      return foundIter -> second.c_str();
  }
  else {
    return dictIter -> second.find(s_key) -> second.c_str();
  }
}

void dict_clear(unsigned long id) {
  auto dictIter = dicts.find(id);
  if (dictIter != dicts.end())
    dictIter -> second.clear();
}

void dict_copy(unsigned long src_id, unsigned long dst_id) {
  if (dicts.find(dst_id) != dicts.end() &&
  	  dicts.find(src_id) != dicts.end()) {

    for (auto key_value_pair : dicts[src_id]) {
      dict_insert(dst_id, key_value_pair.first.c_str(),
        key_value_pair.second.c_str());
    }
  }
}

// co zrobić z powtarzającymi się sprawdzeniami czy dict istnieje
// Marian: pamiętaj żeby wcięcia robić dwoma spacjami
