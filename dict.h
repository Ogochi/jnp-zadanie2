#ifndef DICT_H
#define DICT_H

#ifdef __cplusplus
#include <cstddef>
#include <iostream>
#else
#include <stddef.h>
#endif

#ifdef __cplusplus
namespace jnp1 { 
extern "C" { // CZY TU POWINNY BYĆ JAKIEŚ WCIĘCIA?
#endif
  
unsigned long dict_new();
/*
    Tworzy nowy, pusty słownik i zwraca jego identyfikator.
*/
void dict_delete(unsigned long id);
/*
    Jeżeli istnieje słownik o identyfikatorze id, usuwa go, a w przeciwnym
    przypadku nic nie robi.
*/
size_t dict_size(unsigned long id);
/*
    Jeżeli istnieje słownik o identyfikatorze id, zwraca liczbę jej
    elementów, a w przeciwnym przypadku zwraca 0.
*/
void dict_insert(unsigned long id, const char* key, const char* value);
/*
    Jeżeli istnieje słownik o identyfikatorze id oraz key != NULL
    i value != NULL, wstawia wartość value pod kluczem key.
    W przeciwnym przypadku nic nie robi.
    Gwarancje odnośnie kosztów wstawienia mają być takie same jak w przypadku
    kontenera unordered_map (plus koszt odnalezienia słownika o danym
    identyfikatorze).
*/
void dict_remove(unsigned long id, const char* key);
/*
    Jeżeli istnieje słownik o identyfikatorze id i zawiera klucz key, to usuwa
    klucz oraz wartość związaną z tym kluczem, a w przeciwnym przypadku nic nie
    robi.
*/
const char* dict_find(unsigned long id, const char* key);
/*
    Jeżeli istnieje słownik o identyfikatorze id i zawiera wartość pod kluczem
    key, to zwraca wskaźnik do tej wartości, a w przeciwnym zwraca wartość
    ze słownika globalnego. Jeśli w słowniku globalnym nie ma wartości
    pod kluczem key, to zwraca NULL.
*/

void dict_clear(unsigned long id);
/*
    Jeżeli istnieje słownik o identyfikatorze id, usuwa wszystkie jego elementy,
    a w przeciwnym przypadki nic nie robi.
*/
void dict_copy(unsigned long src_id, unsigned long dst_id);
/*
    Jeżeli istnieją słowniki o identyfikatorach src_id oraz dst_id, to kopiuje
    zawartość słownika o identyfikatorze src_id do słownika o identyfikatorze
    dst_id, a w przeciwnym przypadku nic nie robi. 
 DOPISAĆ CO ZE SŁOWNIKIEM GLOBALNYM
*/

#ifdef __cplusplus
} // extern "C"
} // namespace jnp1
#endif

#endif // DICT_H
