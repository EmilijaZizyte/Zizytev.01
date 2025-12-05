#pragma once
#include "studentas.h"
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <functional>

struct Rezultatai {
    double readTime = 0;
    double splitTime = 0;
    double writeTime = 0;
    double memMB = 0;


    double readTimeVector = 0;
    double splitTimeVector = 0;
    double writeTimeVector = 0;
    double memMBVector = 0;


    double readTimeList = 0;
    double splitTimeList = 0;
    double writeTimeList = 0;
    double memMBList = 0;
};


void generuokFailus();
void analizuokVisusFailusMinimaliai();
void testuokStrategijas();


Rezultatai strategija1_skaidymas(const std::string& failas);
Rezultatai Strategija2(const std::string& failas);
Rezultatai strategija1_STL_skaidymas(const std::string& failas);
void Strategija3(const std::string& failas);
Rezultatai strategija2_STL_vectoriui(const std::string& failas);
