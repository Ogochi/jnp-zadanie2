#ifdef NDEBUG
  const bool debug = false;
#else
  const bool debug = true;
#endif

static const unsigned long GLOBAL_DICT_ID = 0;

unsigned long dict_global() {
  return GLOBAL_DICT_ID;
}
