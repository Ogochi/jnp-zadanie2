#ifdef NDEBUG
  const bool debug = false;
#else
  const bool debug = true;
#endif

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
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

void dict_insert(unsigned long id, const char* key, const char* value);

void dict_remove(unsigned long id, const char* key);

const char* dict_find(unsigned long id, const char* key);

void dict_clear(unsigned long id);

void dict_copy(unsigned long src_id, unsigned long dst_id);

int main() {

}
