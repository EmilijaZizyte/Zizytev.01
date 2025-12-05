#include "studentas.h"
#pragma execution_character_set("utf-8")
#include <ctime>
#include <list>

Studentas ivesk() {
    Studentas Laik;
    std::string input;
    int metode;

    // Paklausiam vartotojo, ranka ar generuoti
    std::cout << "Ar norite ivesti studenta ranka (1) ar generuoti atsitiktinai (2)? ";
    std::cin >> metode;
    std::cin.ignore(10000, '\n');

    if (metode == 2) { // atsitiktinis studentas
        int vardSkaicius = std::rand() % 100;
        int pavSkaicius = std::rand() % 100;
        Laik.vard = "vardas" + std::to_string(vardSkaicius);
        Laik.pav = "pavarde" + std::to_string(pavSkaicius);
        for (int i = 0; i < 5; i++) Laik.paz.push_back(std::rand() % 11);
        Laik.egzas = std::rand() % 11;

        std::cout << "Sugeneruotas studentas: " << Laik.vard << " " << Laik.pav << "\n";
    }
    else { // rankinė įvestis
        while (true) {
            std::cout << "Iveskite varda: ";
            std::cin >> Laik.vard;
            bool valid = std::all_of(Laik.vard.begin(), Laik.vard.end(), ::isalpha);
            if (valid) break;
            std::cout << "Vardas gali tureti tik raides. Bandykite dar karta.\n";
        }

        while (true) {
            std::cout << "Iveskite pavarde: ";
            std::cin >> Laik.pav;
            bool valid = std::all_of(Laik.pav.begin(), Laik.pav.end(), ::isalpha);
            if (valid) break;
            std::cout << "Pavarde gali tureti tik raides. Bandykite dar karta.\n";
        }

        std::cout << "Iveskite namu darbu pazymius (vienas per eilute).\n"
            << "Baigti tuscia eilute (spauskite Enter):\n";

        std::cin.ignore();
        while (true) {
            getline(std::cin, input);
            if (input.empty()) break;

            std::stringstream ss(input);
            int m;
            std::string extra;

            if (ss >> m && !(ss >> extra) && m >= 0 && m <= 10)
                Laik.paz.push_back(m);
            else
                std::cout << "Bloga ivestis! Iveskite skaiciu 0–10 arba tuscia eilute pabaigai.\n";
        }

        while (true) {
            std::cout << "Iveskite egzamino rezultata : ";
            std::cin >> Laik.egzas;
            if (!std::cin.fail() && Laik.egzas >= 0 && Laik.egzas <= 10) break;

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Egzamino rezultatas turi buti tarp 0 ir 10! Bandykite dar karta.\n";
        }
    }

    return Laik;
}

double mediana(const std::vector<int>& v) {
    std::vector<int> t = v;
    sort(t.begin(), t.end());
    int n = static_cast<int>(t.size());
    if (n == 0) return 0;
    return n % 2 ? t[n / 2] : (t[n / 2 - 1] + t[n / 2]) / 2.0;
}

void skaiciuokRezultatus(Studentas& s) {
    if (s.paz.empty()) {
        s.rezVid = s.rezMed = 0;
        return;
    }

    double suma = 0;
    for (int p : s.paz) suma += p;
    double vid = suma / s.paz.size();

    s.rezVid = 0.4 * vid + 0.6 * s.egzas;
    s.rezMed = 0.4 * mediana(s.paz) + 0.6 * s.egzas;
}

// --- pridetiStudenta vectoriui ---
void pridetiStudenta(std::vector<Studentas>& Grupe) {
    Studentas Laik = ivesk();
    skaiciuokRezultatus(Laik);
    Grupe.push_back(Laik);

    std::cout << "Studentas pridetas sekmingai! Adresas vektoriuje: "
        << &Grupe.back() << "\n";
}

// --- pridetiStudenta listui ---
void pridetiStudenta(std::list<Studentas>& Grupe) {
    Studentas Laik = ivesk();
    skaiciuokRezultatus(Laik);
    Grupe.push_back(Laik);

    std::cout << "Studentas pridetas sekmingai! Adresas liste: "
        << &Grupe.back() << "\n";
    
}

void rodytiRezultatus(const std::vector<Studentas>& Grupe) {
    if (Grupe.empty()) {
        std::cout << "Sarasas tuscias.\n";
        return;
    }

    std::cout << std::left << std::setw(15) << "Vardas"
        << std::left << std::setw(15) << "Pavarde"
        << std::right << std::setw(15) << "Galutinis(Vid.)"
        << std::right << std::setw(15) << "Galutinis(Med.)" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& s : Grupe) {
        std::cout << std::left << std::setw(15) << s.vard
            << std::left << std::setw(15) << s.pav
            << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezVid
            << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezMed << "\n";
    }
}
