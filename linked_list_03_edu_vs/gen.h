#pragma once

#include <stdio.h>

#include <conio.h>
#include <ctime>
#include <string.h>
#include "stdlib.h"
#include <conio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <math.h>
// #include <Windows.h>

using namespace std;


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define TIME_TICK_INTERVAL 1000

// This didn't work:
// #define rdtsc __asm __emit 0fh __asm __emit 031h

#define WIN32_APP
#define RND_MAX 65536


int getRndNumber(int iMinP=0, int iMaxP=101)
{
    int _tmp_rand_value = 0;
    int _retValue = 0;

    _tmp_rand_value = rand();
    _retValue = ( iMinP + int( (iMaxP - iMinP + 1) * _tmp_rand_value /(RAND_MAX + 1.0) ) );
    std::cout << _retValue << "\n";
    return _retValue;
}


