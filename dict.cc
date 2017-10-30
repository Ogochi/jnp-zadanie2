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

#ifdef __cplusplus
extern "C" {
#endif

using std::size_t;
using std::string;
using std::unordered_map;
using std::make_pair;
using DICT = unordered_map<string, string>;

static unordered_map<unsigned long, DICT > dicts ( {{dict_global(), DICT ()}} );
static unsigned long id_for_new_dict = 1;

unsigned long dict_new() {
  if (debug)
    std::cerr << "dict_new()\n";

  DICT new_dict;

  dicts.insert({id_for_new_dict, new_dict});

  if (debug)
    std::cerr << "dict_new: dict " << id_for_new_dict << " has been created\n";

  id_for_new_dict++;

  return id_for_new_dict - 1;
}

void dict_delete(unsigned long id) {
  if (debug)
    std::cerr << "dict_delete(" << id << ")\n";

  if (dicts.find(id) != dicts.end()) {
    if(id != dict_global()) {
      if(debug)
        std::cerr << "dict_delete: dict " << id << " has been deleted\n";

      dicts.erase(id);
    }
    else if (debug) {
      std::cerr << "dict_delete: attempt to delete Global Dict\n";
    }

  }
  else if (debug) {
    std::cerr << "dict_delete: dict " << id << " not found\n";
  }


}

size_t dict_size(unsigned long id) {
  if (debug)
    std::cerr << "dict_size(" << id << ")\n";

  auto it = dicts.find(id);

  if (it != dicts.end()) {
    if (debug) {
      std::cerr << "dict_size: dict " << id << " contains ";
      std::cerr << (it -> second).size() << " elements\n";
    }

    return (it -> second).size();
  }
  else {
    if (debug)
      std::cerr << "dict_size: dict with id " << id << " doesn't exist\n";

    return 0;
  }
}

void dict_insert(unsigned long id, const char* key, const char* value) {
  if (debug) {
    string key2 = key == NULL ? "NULL" : string(key);
    string value2 = value == NULL ? "NULL" : string(value);
    std::cerr << "dict_insert(" << id << ", " << key2 << ", ";
    std::cerr << string(value2) << ")\n";
  }

  if (key == NULL ||  value == NULL) {
    if (debug)
      std::cerr << "dict_insert: attempt to insert to dict " << id << " NULL key or value\n";

    return;
  }

  if (id == dict_global() && dicts[dict_global()].size() == MAX_GLOBAL_DICT_SIZE) {
    if(debug)
      std::cerr << "dict_insert: attempt to make Global Dict size exceed its max size\n";

      return;
  }

  auto dictIter = dicts.find(id);
  if (dictIter != dicts.end()) {
    dictIter -> second.insert(std::make_pair<string,string>(string(key),
                                                          string(value)));

    if (debug) {
      std::cerr << "dict_insert: dict " << id << ", the pair (" << string(key);
      std::cerr << ", " << string(value) << ") has been inserted\n";
    }
  }
  else {
    if (debug)
      std::cerr << "dict_insert: dict " << id << " not found\n";
  }
}

void dict_remove(unsigned long id, const char* key) {
  if (debug)
    std::cerr << "dict_remove(" << id << ", " << string(key) << ")\n";

  auto dictIter = dicts.find(id);
  string s_key(key);

  if (dictIter != dicts.end()) {
    if(dictIter -> second.find(s_key) != dictIter -> second.end()) {
      dictIter -> second.erase(s_key);

      if(debug) {
        std::cerr << "dict_remove: dict " << id << ", key " << string(key);
        std::cerr << " has been removed\n";
      }
    }
    else if (debug) {
      std::cerr << "dict_remove: dict " << id << ", key " << string(key) << " not found\n";
    }
  }
  else if (debug) {
    std::cerr << "dict_remove: dict " << id << " not found\n";
  }
}

const char* dict_find(unsigned long id, const char* key) {
  if (debug)
    std::cerr << "dict_find(" << id << ", " << string(key) << ")\n";

  auto dictIter = dicts.find(id);
  string s_key(key);
/*
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
  }*/

  if (dictIter != dicts.end()) {
    auto dictIter2 = dictIter -> second.find(s_key);

    if (dictIter2 != dictIter -> second.end()) {
      if (debug) {
        std::cerr << "dict_find: key " << string(key) << " in dict ";
        std::cerr << id << " that has value " << dictIter2 -> second << "\n";
      }

      return dictIter2 -> second.c_str();
    }
    else if (debug) {
      std::cerr << "dict_find: key " << string(key) << " not found, ";
    }
  }
  else if (debug) {
    std::cerr << "dict_find: dict " << id << " not found, ";
  }

  if (debug)
    std::cerr << "looking up the Global Dictionary\n";

  auto globalIter = dicts.find(dict_global());
  auto foundIter = globalIter -> second.find(s_key);

  if (foundIter == globalIter -> second.end()) {
    if (debug) {
      std::cerr << "dict_find: key " << string(key);
      std::cerr << " not found in the Global Dictionary, return NULL\n";
    }

    return NULL;
  }
  else {
    if (debug) {
      std::cerr << "dict_find: key " << string(key);
      std::cerr << " in the Global Dictionary has value " << foundIter -> second << "\n";
    }

    return foundIter -> second.c_str();
  }
}

void dict_clear(unsigned long id) {
  if (debug)
    std::cerr << "dict_clear(" << id << ")\n";

  auto dictIter = dicts.find(id);

  if (dictIter != dicts.end()) {
    dictIter -> second.clear();

    std::cerr << "dict_clear: dict " << id << " has been cleared\n";
  }
  else if (debug) {
    std::cerr << "dict_clear: dict " << id << " not found\n";
  }
}

void dict_copy(unsigned long src_id, unsigned long dst_id) {
  if (debug)
    std::cerr << "dict_copy(" << src_id << ", " << dst_id << ")\n";

  if (dicts.find(dst_id) != dicts.end()) {
  	if (dicts.find(src_id) != dicts.end()) {
      for (auto key_value_pair : dicts[src_id]) {
        dict_insert(dst_id, key_value_pair.first.c_str(),
          key_value_pair.second.c_str());
      }

      if (debug) {
        std::cerr << "dict_copy: dict " << src_id << " has been copied to ";
        std::cerr << dst_id << "\n";
      }
    }
    else if (debug) {
      std::cerr << "dict_copy: source dict " << src_id << " not found\n";
    }
  }
  else if (debug) {
    std::cerr << "dict_copy: destination dict " << dst_id << " not found\n";
  }
}

#ifdef __cplusplus
}
#endif

// co zrobić z powtarzającymi się sprawdzeniami czy dict istnieje
// Marian: pamiętaj żeby wcięcia robić dwoma spacjami
