clear;
g++ -std=c++14 -O3 -march=native -msse2 -lm -D__NO_INLINE__ -Wall -Werror=pedantic main.cpp vec4.cpp  -o exec.exe;		
./exec.exe;

