#include <cstddef>
#include <string>
#include <unordered_map>
#include <cassert>
#include "dict.h"
#include "dictglobal.h"

namespace {
  #ifdef NDEBUG
    const bool debug = false;
  #else
    const bool debug = true;
  #endif
}

using std::size_t;
using std::string;
using std::unordered_map;
using std::make_pair;
using std::cerr;

/*
 * Typ danych reprezentujacy słownik czyli mape o kluczach typu string oraz
 * wartościach typu string
 */
using dict_t = unordered_map<string, string>;

namespace jnp1 {
  unordered_map<unsigned long, dict_t>& dicts() {
    //TODO czy warto tu spacje po dicts ???
    static unordered_map<unsigned long, dict_t> dicts ( {{dict_global(), dict_t()}} );
    return dicts;
  }
  unsigned long dict_new() {
    static unsigned long id_for_new_dict = 1;

    if (debug)
      cerr << "dict_new()\n";

    assert(id_for_new_dict != 0);

    dicts().insert({id_for_new_dict, dict_t()});

    if (debug)
      cerr << "dict_new: dict " << id_for_new_dict << " has been created\n";

    return id_for_new_dict++;
  }

  void dict_delete(unsigned long id) {
    if (debug)
      cerr << "dict_delete(" << id << ")\n";

    if (dicts().find(id) != dicts().end()) {
      if (id != dict_global()) {
        if (debug)
          cerr << "dict_delete: dict " << id << " has been deleted\n";

        dicts().erase(id);
      }
      else if (debug) {
        cerr << "dict_delete: attempt to delete Global Dict\n";
      }
    }
    else if (debug) {
      cerr << "dict_delete: dict " << id << " not found\n";
    }
  }

  size_t dict_size(unsigned long id) {
    if (debug)
      cerr << "dict_size(" << id << ")\n";

    auto it = dicts().find(id);

    if (it != dicts().end()) {
      if (debug) {
        cerr << "dict_size: dict " << id << " contains "
             << (it -> second).size() << " elements\n";
      }

      return (it -> second).size();
    }
    else {
      if (debug)
        cerr << "dict_size: dict with id " << id << " doesn't exist\n";

      return 0;
    }
  }

  void dict_insert(unsigned long id, const char* key, const char* value) {
    if (debug) {
      string key2 = key == NULL ? "NULL" : string(key);
      string value2 = value == NULL ? "NULL" : string(value);
      cerr << "dict_insert(" << id << ", " << key2 << ", "
           << string(value2) << ")\n";
    }

    if (key == NULL ||  value == NULL) {
      if (debug)
        cerr << "dict_insert: attempt to insert to dict " << id 
             << " NULL key or value\n";

      return;
    }

    if (id == dict_global() &&
        dicts()[dict_global()].size() == MAX_GLOBAL_DICT_SIZE) {
      if(debug)
        cerr << "dict_insert: attempt to make Global Dict size"
             << "exceed its max size\n";

        return;
    }

    auto dictIter = dicts().find(id);
    if (dictIter != dicts().end()) {
      dictIter -> second.insert(make_pair<string,string>(string(key),
                                                            string(value)));

      if (debug) {
        cerr << "dict_insert: dict " << id << ", the pair (" << string(key)
             << ", " << string(value) << ") has been inserted\n";
      }
    }
    else {
      if (debug)
        cerr << "dict_insert: dict " << id << " not found\n";
    }
  }

  void dict_remove(unsigned long id, const char* key) {
    if (debug)
      cerr << "dict_remove(" << id << ", " << string(key) << ")\n";

    auto dictIter = dicts().find(id);
    string s_key(key);

    if (dictIter != dicts().end()) {
      if(dictIter -> second.find(s_key) != dictIter -> second.end()) {
        dictIter -> second.erase(s_key);

        if(debug) {
          cerr << "dict_remove: dict " << id << ", key " << string(key)
               << " has been removed\n";
        }
      }
      else if (debug) {
        cerr << "dict_remove: dict " << id << ", key " << string(key) 
             << " not found\n";
      }
    }
    else if (debug) {
      cerr << "dict_remove: dict " << id << " not found\n";
    }
  }

  const char* dict_find(unsigned long id, const char* key) {
    if (debug)
      cerr << "dict_find(" << id << ", " << string(key) << ")\n";

    auto dictIter = dicts().find(id);
    string s_key(key);

    if (dictIter != dicts().end()) {
      auto dictIter2 = dictIter -> second.find(s_key);

      if (dictIter2 != dictIter -> second.end()) {
        if (debug) {
          cerr << "dict_find: key " << string(key) << " in dict "
               << id << " that has value " << dictIter2 -> second << "\n";
        }

        return dictIter2 -> second.c_str();
      }
      else if (debug) {
        cerr << "dict_find: key " << string(key) << " not found, ";
      }
    }
    else if (debug) {
      cerr << "dict_find: dict " << id << " not found, ";
    }

    if (debug)
      cerr << "looking up the Global Dictionary\n";

    auto globalIter = dicts().find(dict_global());
    auto foundIter = globalIter -> second.find(s_key);

    if (foundIter == globalIter -> second.end()) {
      if (debug) {
        cerr << "dict_find: key " << string(key)
             << " not found in the Global Dictionary, return NULL\n";
      }

      return NULL;
    }
    else {
      if (debug) {
        //TODO jak to przeniesc???
        cerr << "dict_find: key " << string(key) << " in the Global Dictionary"
             << " has value " << foundIter -> second << "\n";
      }

      return foundIter -> second.c_str();
    }
  }

  void dict_clear(unsigned long id) {
    if (debug)
      cerr << "dict_clear(" << id << ")\n";

    auto dictIter = dicts().find(id);

    if (dictIter != dicts().end()) {
      dictIter -> second.clear();

      if (debug)
        cerr << "dict_clear: dict " << id << " has been cleared\n";
    }
    else if (debug) {
      cerr << "dict_clear: dict " << id << " not found\n";
    }
  }

  void dict_copy(unsigned long src_id, unsigned long dst_id) {
    if (debug)
      cerr << "dict_copy(" << src_id << ", " << dst_id << ")\n";

    auto dst_dict = dicts().find(dst_id), src_dict = dicts().find(src_id);

    if (dst_dict != dicts().end()) {
      // TODO czy 80 to max przeciez tu to jedynie 2 symbole ktore nie wolno osobno przeniesc, a jak przeniesiemy to mniej czytelne
      /*
       * zmienna logiczna ktora słuzy do sprawdzenia warunku przy kopiowaniu do
       * słownika globalnego, dba o nieprzepelnienie słownika globalnego
       */
      bool not_enough_space = (src_id = 0 && (dst_dict -> second.size() +
                               src_dict -> second.size() > MAX_GLOBAL_DICT_SIZE));
      // nie kopiujemy gdy slownik sie nie zmiesci
      if (src_dict != dicts().end() || !not_enough_space) {
        for (auto key_value_pair : src_dict -> second) {
          /*
           * nie uzywamy funkcji dict_insert gdyz, spowoduje to ponowne
           * wyszukanie iteratora, co skutkuje pogorszeniem efektywnosci kodu
           */
          // TODO jak to mam przeniesc ??? czy tak jest ok??
          dst_dict -> second.insert(make_pair<string,string>(
            string(key_value_pair.first), string(key_value_pair.second)));
        }

        if (debug) {
          cerr << "dict_copy: dict " << src_id << " has been copied to "
               << dst_id << "\n";
        }
      }
      else if (debug) {
        cerr << "dict_copy: source dict " << src_id << " not found\n";
      }
    }
    else if (debug) {
      cerr << "dict_copy: destination dict " << dst_id << " not found\n";
    }
  }
}
