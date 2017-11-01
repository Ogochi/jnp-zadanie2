#ifndef DICTGLOBAL_H
#define DICTGLOBAL_H

#ifdef __cplusplus
#include <cstddef>
#include <iostream>
#else
#include <stddef.h>
#endif

#ifdef __cplusplus
namespace jnp1 {
extern "C" {
#endif

unsigned long dict_global();
/*
    Zwraca identyfikator globalnego słownika, którego nie można usunąć.
*/

const size_t MAX_GLOBAL_DICT_SIZE = 42;
/*
    Stała określa maksymalny rozmiar globalnego słownika.
    Do globalnego słownika można wstawiać kolejne klucze z wartościami tylko,
    gdy jego rozmiar po wstawieniu nie będzie przekraczał maksymalnego
    rozmiaru.
*/

#ifdef __cplusplus
} // extern "C"
} // namespace jnp1
#endif

#endif // DICTGLOBAL_H
