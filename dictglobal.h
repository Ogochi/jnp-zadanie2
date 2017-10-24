#ifndef DICTGLOBAL_H
#define DICTGLOBAL_H

unsigned long dict_global();
/*
    Zwraca identyfikator globalnego słownika, którego nie można usunąć.
*/

const int MAX_GLOBAL_DICT_SIZE = 42;
/*
    Stała określa maksymalny rozmiar globalnego słownika.
    Do globalnego słownika można wstawiać kolejne klucze z wartościami tylko,
    gdy jego rozmiar po wstawieniu nie będzie przekraczał maksymalnego
    rozmiaru.
*/

#endif
