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

static unordered_map<unsigned long, DICT > dicts ( {{0, DICT ()}} );
static unsigned long id_for_new_dict = 1;

unsigned long dict_new() {
  DICT new_dict;

  dicts.insert({id_for_new_dict, new_dict});
}

void dict_delete(unsigned long id) {
  if (dicts.find(id) != dicts.end() && id != 0)
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
  dictIter->second.insert(std::make_pair<string,string>(key, value));
}

void dict_remove(unsigned long id, const char* key) {
  /*
    Jeżeli istnieje słownik o identyfikatorze id i zawiera klucz key, to usuwa
    klucz oraz wartość związaną z tym kluczem, a w przeciwnym przypadku nic nie
    robi.
*/
  auto dictIter = dicts.find(id);
  if (dictIter != dicts.end() && 
      dictIter->second.find(key) != dictIter->second.end()) {
    dictIter->second.erase(key);
  }
}

const char* dict_find(unsigned long id, const char* key) {
  auto dictIter = dicts.find(id);
  string s_key(key);
  
  // Nie istnieje słownik lub klucz nie istnieje w podanym słowniku.
  if (dictIter == dicts.end() || 
      dictIter->second.find(key) == dictIter->second.end()) {
    auto globalIter = dicts.find(dict_global());
    auto foundIter = globalIter->second.find(s_key);
    if (foundIter == globalIter->second.end()) 
      return NULL;
    else 
      return foundIter->second.c_str();
  } 
  else {
    return dictIter->second.find(key)->second.c_str();
  }
}

void dict_clear(unsigned long id) {
  auto dictIter = dicts.find(id);
  if (dictIter != dicts.end())
    dictIter->second.clear();
}

void dict_copy(unsigned long src_id, unsigned long dst_id) {
  DICT dict_to_copy = dicts[src_id];
  string key_copy, value_copy;
  for (auto key_value_pair : dict_to_copy) {
    key_copy =  key_value_pair.first.copy();
    value_copy = key_value_pair.second.copy();
    dict_insert(dict_to_copy, key_copy, value_copy);
  }
  /*
  M:nie wiem czy kopiujemy kluczy czy nie
  czy mamy dac nacisk na leniwy kod jak ten ponizej czy bardziej na taki 
  zrozumialy jak u gory

  alternatywnie
  for (auto key_value_pair : dict_to_copy) {
    dict_insert(dict_to_kopy, key_value_pair.first, key_value_pair.second)
  }
  ------- 
  B:ja myślę że krótsza wersja jest lepsza, tak naprawdę nie traci na czytelności
  a wydaje się być zgrabniejsza. Myślę że kopiujemy klucze i wartości, taki jest
  chyba sens kopiowania mapy żeby dostać dwie niezależne mapy. 
  */
}

// co zrobić z powtarzającymi się sprawdzeniami czy dict istnieje
// Marian: pamiętaj żeby wcięcia robić dwoma spacjami
