#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>
using namespace std;

struct Studentas {
    std::string vard;
    std::string pav;
    std::vector<int> paz;
    int egzas{};
    double rezVid{};
    double rezMed{};
};


Studentas ivesk();
double mediana(const std::vector<int>& v);
void skaiciuokRezultatus(Studentas& s);

void pridetiStudenta(vector<Studentas>& Grupe);
void rodytiRezultatus(const vector<Studentas>& Grupe);
