#include "dictglobal.h"

// komentarz do create new ze sie nie naklada na globala
static const unsigned long GLOBAL_DICT_ID = 0;

unsigned long dict_global() {
  return GLOBAL_DICT_ID;
}
