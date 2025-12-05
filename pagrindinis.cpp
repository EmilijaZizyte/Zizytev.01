#include <iostream>
#include <vector>
#include <ctime>
#include <list>
#include "studentas.h"
#include "failai.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));
    std::vector<Studentas> GrupeVector;
    std::list<Studentas> GrupeList;

    while (true) {
        std::cout << "\nPasirinkite:\n";
        std::cout << "1 - Prideti viena studenta\n";
        std::cout << "2 - Rodyti studentu rezultatus\n";
        std::cout << "3 - Baigti programa\n";
        std::cout << "4 - Generuoti testinius failus\n";
        std::cout << "5 - Nuskaityti visus failus\n";
        std::cout << "6 - Testuoti strategijas\n";
        std::cout << "Jusu pasirinkimas: ";

        int pasirinkimas;
        std::cin >> pasirinkimas;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Bandykite dar karta.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (pasirinkimas == 1) {
            std::cout << "\n=== Ivedimas ir issaugojimas ===\n";
            Studentas s = ivesk();

            GrupeVector.push_back(s);
            std::cout << "Studentas '" << s.vard << " " << s.pav
                << "' issaugotas vectoriuje adresu: " << &GrupeVector.back() << "\n";

            GrupeList.push_back(s);
            std::cout << "Studentas '" << s.vard << " " << s.pav
                << "' issaugotas liste adresu: " << &GrupeList.back() << "\n";
        }

        else if (pasirinkimas == 2) {
            rodytiRezultatus(GrupeVector);
        }
        else if (pasirinkimas == 3) {
            std::cout << "Programa baigta.\n";
            break;
        }
        else if (pasirinkimas == 4) {
            generuokFailus();
        }
        else if (pasirinkimas == 5) {
            analizuokVisusFailusMinimaliai();

        }
        else if (pasirinkimas == 6) {
            int strategija;
            std::string failas;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failas;

            std::cout << "Kurios strategijos noretumet: \n1 - ('studentai' konteinerio skaidymas i du)\n2-(panaudojant tik viena nauja konteineri, trinant is bendro studentai konteinerio)\n3-(nustayti kuri strategija greitesne ir vector pritaikyti stl)\n";
            std::cin >> strategija;

            if (strategija == 1) {
                strategija1_skaidymas(failas);
            }
            else if (strategija == 2) {
                Strategija2(failas);
            }
            else if (strategija == 3) {
                Strategija3(failas);
            }
            else {
                std::cout << "Netinkamas pasirinkimas. Bandykite dar karta.\n";
            }


        }
        else {
            std::cout << "Netinkamas pasirinkimas. Bandykite dar karta.\n";
        }
    }

    return 0;
}
