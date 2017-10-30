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
  if(debug)
    cerr << "dict_new()\n";

  DICT new_dict;

  dicts.insert({id_for_new_dict, new_dict});

  if(debug)
    cerr << "dict_new: dict " << id_for_new_dict << " has been created\n";

  id_for_new_dict++;

  return id_for_new_dict;
}

void dict_delete(unsigned long id) {
  if(debug)
    cerr << "dict_delete(" << id << ")\n";

  if (dicts.find(id) != dicts.end()) {
    if(id != dict_global()) {
      if(debug)
        cerr << "dict_delete: dict " << id << "has been deleted\n";

      dicts.erase(id);
    }
    else if(debuf) {
      cerr << "dict_delete: attempt to delete Global Dict\n";
    }

  }
  else if (debug) {
    cerr << "dict_delete: dict " << id << "not found\n";
  }


}

size_t dict_size(unsigned long id) {
  if(debug)
    cerr << "dict_size(" << id << ")\n";

  auto it = dicts.find(id);

  if (it != dicts.end()) {
    if(debug) {
      cerr << "dict_size: dict " << id << "contains ";
      cerr << (it -> second).size() << " elements\n";
    }

    return (it -> second).size();
  }
  else {
    if(debug)
      cerr << "dict_size: dict with id " << id << "doesn't exist\n";

    return 0;
  }
}

void dict_insert(unsigned long id, const char* key, const char* value) {
  if(debug)
    cerr << "dict_insert(" << id << ", " << string(key) << ", " << string(value) ")\n";

  if (key == NULL ||  value == NULL) {
    if(debug)
      cerr << "dict_insert: attempt to insert to dict " << id << "NULL key or value\n";

    return;
  if (id == dict_global() && dicts[dict_global()].size() == MAX_GLOBAL_DICT_SIZE) {
    if(debug)
      cerr << "dict_insert: attempt to make Global Dict size exceed its max size\n";

      return;
  }

  auto dictIter = dicts.find(id);
  if (dictIter != dicts.end()) {
    dictIter -> second.insert(std::make_pair<string,string>(string(key),
                                                          string(value)));

    if(debug) {
      cerr << "dict_insert: dict " << id << ", the pair (" << string(key);
      cerr << ", " << string(value) << " has been added\n";
    }
  }
  else {
    if(debug)
      cerr << "dict_insert: dict " << id << " not found\n";
  }



}

void dict_remove(unsigned long id, const char* key) {
  if(debug)
    cerr << "dict_remove(" << id << ", " << string(key) << ")\n";

  auto dictIter = dicts.find(id);
  string s_key(key);

  if (dictIter != dicts.end()) {
    if(dictIter -> second.find(s_key) != dictIter -> second.end()) {
      dictIter -> second.erase(s_key);

      if(debug) {
        cerr << "dict_remove: dict " << id << ", key " << string(key);
        cerr << " has been removed\n";
      }
    }
    else if (debug) [
      cerr << "dict_remove: dict " << id << ", key " << string(key) << " not found\n";
    ]
  }
  else if (debug) {
    cerr << "dict_remove: dict " << id << " not found\n";
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
