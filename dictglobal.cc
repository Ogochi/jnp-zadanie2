#include "dictglobal.h"

namespace jnp1 {
  /* Nie ma możliwości aby żaden inny słownik dostał id = 0, ponieważ numeracja
   * odbywa się od 1, a ponadto sprawdzane jest czy licznik nowych identyfikatorów
   * nie "przekręcił" się. */
  static const unsigned long GLOBAL_DICT_ID = 0;

  unsigned long dict_global() {
    return GLOBAL_DICT_ID;
  }
}