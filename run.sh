g++ -c -Wall -Wextra -O2 -std=c++17 dict.cc -o dict.o
g++ -c -Wall -Wextra -O2 -std=c++17 dictglobal.cc -o dictglobal.o
gcc -c -Wall -Wextra -O2 dict_test1.c -o dict_test1.o
g++ dict.o dictglobal.o dict_test1.o -o dict_test1
#g++ -c -Wall -Wextra -O2 -std=c++17 dict_test2a.cc -o dict_test2a.o
#g++ -c -Wall -Wextra -O2 -std=c++17 dict_test2b.cc -o dict_test2b.o
