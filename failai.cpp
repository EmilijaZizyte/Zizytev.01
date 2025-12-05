#define _CRT_SECURE_NO_WARNINGS
#include "studentas.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include "failai.h"
#include <numeric> // accumulate


void skaiciuokRezultatusFailui(Studentas& s) {
    skaiciuokRezultatus(s);
}





// ================= STRATEGIJA 1 su skaidymu =================
Rezultatai strategija1_skaidymas(const std::string& failas) {
    Rezultatai rez{};
    std::string base = failas.substr(0, failas.find(".txt"));
    std::string eilute;
    int lineCounter = 0;

    // ================= VECTOR =================
    std::ifstream open_f(failas);
    if (!open_f.is_open()) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return rez;
    }

    auto tReadStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> visiStudentaiV;
    visiStudentaiV.reserve(10'000'000);

    // Skaitome failą
    while (std::getline(open_f, eilute)) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eilute); // kiekvienai eilutei naujas objektas
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) {
            int x;
            ss >> x;
            s.paz.push_back(x);
        }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiV.push_back(s);
    }


    auto tReadEndV = std::chrono::high_resolution_clock::now();
    rez.readTimeVector = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    // Skirstymas į "kietiakai" ir "vargsiukai" rankiniu ciklu
    auto tSplitStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> kietiakaiV, vargsiukaiV;
    kietiakaiV.reserve(visiStudentaiV.size());
    vargsiukaiV.reserve(visiStudentaiV.size());

    for (size_t i = 0; i < visiStudentaiV.size(); i++) {
        const Studentas& s = visiStudentaiV[i];
        if (s.rezVid >= 5 && s.rezMed >= 5) kietiakaiV.push_back(s);
        else vargsiukaiV.push_back(s);
    }
    auto tSplitEndV = std::chrono::high_resolution_clock::now();
    rez.splitTimeVector = std::chrono::duration<double>(tSplitEndV - tSplitStartV).count();

    // Rašymas į failus
    auto tWriteStartV = std::chrono::high_resolution_clock::now();
    std::ofstream outKietV(base + "_kietiakai_vector_1strategija.txt");
    std::ofstream outVargV(base + "_vargsiukai_vector_1strategija.txt");

    for (size_t i = 0; i < kietiakaiV.size(); i++)
        outKietV << std::left << std::setw(15) << kietiakaiV[i].vard
        << std::setw(15) << kietiakaiV[i].pav
        << std::setw(10) << kietiakaiV[i].rezVid
        << std::setw(10) << kietiakaiV[i].rezMed << "\n";

    for (size_t i = 0; i < vargsiukaiV.size(); i++)
        outVargV << std::left << std::setw(15) << vargsiukaiV[i].vard
        << std::setw(15) << vargsiukaiV[i].pav
        << std::setw(10) << vargsiukaiV[i].rezVid
        << std::setw(10) << vargsiukaiV[i].rezMed << "\n";

    outKietV.close();
    outVargV.close();
    auto tWriteEndV = std::chrono::high_resolution_clock::now();
    rez.writeTimeVector = std::chrono::duration<double>(tWriteEndV - tWriteStartV).count();

    rez.memMBVector = (sizeof(Studentas) * visiStudentaiV.size() +
        sizeof(Studentas) * (kietiakaiV.size() + vargsiukaiV.size())) / (1024.0 * 1024.0);

    std::cout << "\n=== VECTOR STRATEGIJA 1 ===\n";
    std::cout << "  Studentu viso: " << visiStudentaiV.size() << "\n";
    std::cout << "  Kietiakai:     " << kietiakaiV.size() << "\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiV.size() << "\n";
    std::cout << "  Nuskaitymas:   " << rez.readTimeVector << " s\n";
    std::cout << "  Skaidymas:     " << rez.splitTimeVector << " s\n";
    std::cout << "  Rasymas:       " << rez.writeTimeVector << " s\n";
    std::cout << "  Bendra atmintis (vector): " << std::fixed << std::setprecision(2) << rez.memMBVector << " MB\n";

    // ================= LIST =================
    std::ifstream open_f2(failas); // naujas ifstream list daliai
    if (!open_f2.is_open()) {
        std::cout << "Nepavyko atidaryti failo (list versijai)!\n";
        return rez;
    }

    std::list<Studentas> visiStudentaiL;
    lineCounter = 0;
    auto tReadStartL = std::chrono::high_resolution_clock::now();

    while (std::getline(open_f2, eilute)) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eilute);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) {
            int x;
            ss >> x;
            s.paz.push_back(x);
        }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiL.push_back(s);
    }

    auto tReadEndL = std::chrono::high_resolution_clock::now();
    rez.readTimeList = std::chrono::duration<double>(tReadEndL - tReadStartL).count();

    // Skirstymas rankiniu ciklu
    auto tSplitStartL = std::chrono::high_resolution_clock::now();
    std::list<Studentas> kietiakaiL, vargsiukaiL;
    for (auto it = visiStudentaiL.begin(); it != visiStudentaiL.end(); ++it) {
        if (it->rezVid >= 5 && it->rezMed >= 5) kietiakaiL.push_back(*it);
        else vargsiukaiL.push_back(*it);
    }
    auto tSplitEndL = std::chrono::high_resolution_clock::now();
    rez.splitTimeList = std::chrono::duration<double>(tSplitEndL - tSplitStartL).count();

    // Rašymas į failus
    auto tWriteStartL = std::chrono::high_resolution_clock::now();
    std::ofstream outKietL(base + "_kietiakai_list_1strategija.txt");
    std::ofstream outVargL(base + "_vargsiukai_list_1strategija.txt");

    for (auto it = kietiakaiL.begin(); it != kietiakaiL.end(); ++it)
        outKietL << std::left << std::setw(15) << it->vard
        << std::setw(15) << it->pav
        << std::setw(10) << it->rezVid
        << std::setw(10) << it->rezMed << "\n";

    for (auto it = vargsiukaiL.begin(); it != vargsiukaiL.end(); ++it)
        outVargL << std::left << std::setw(15) << it->vard
        << std::setw(15) << it->pav
        << std::setw(10) << it->rezVid
        << std::setw(10) << it->rezMed << "\n";

    outKietL.close();
    outVargL.close();
    auto tWriteEndL = std::chrono::high_resolution_clock::now();
    rez.writeTimeList = std::chrono::duration<double>(tWriteEndL - tWriteStartL).count();

    rez.memMBList = ((sizeof(Studentas) + 2 * sizeof(void*)) * visiStudentaiL.size() +
        (sizeof(Studentas) + 2 * sizeof(void*)) * (kietiakaiL.size() + vargsiukaiL.size())) / (1024.0 * 1024.0);

    std::cout << "\n=== LIST STRATEGIJA 1 ===\n";
    std::cout << "  Studentu viso: " << visiStudentaiL.size() << "\n";
    std::cout << "  Kietiakai:     " << kietiakaiL.size() << "\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiL.size() << "\n";
    std::cout << "  Nuskaitymas:   " << rez.readTimeList << " s\n";
    std::cout << "  Skaidymas:     " << rez.splitTimeList << " s\n";
    std::cout << "  Rasymas:       " << rez.writeTimeList << " s\n";
    std::cout << "  Bendra atmintis (list): " << std::fixed << std::setprecision(2) << rez.memMBList << " MB\n";

    return rez;
}


Rezultatai Strategija2(const std::string& failas) {
    Rezultatai rez{};
    std::string base = failas.substr(0, failas.find(".txt"));
    std::string eilute;
    int lineCounter = 0;

    // ================= VECTOR =================
    std::ifstream open_f(failas);
    if (!open_f.is_open()) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return rez;
    }

    auto tReadStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> visiStudentaiV;
    visiStudentaiV.reserve(10'000'000);

    // Skaitome failą
    while (std::getline(open_f, eilute)) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eilute); // kiekvienai eilutei naujas objektas
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) {
            int x;
            ss >> x;
            s.paz.push_back(x);
        }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiV.push_back(s);
    }


    auto tReadEndV = std::chrono::high_resolution_clock::now();
    rez.readTimeVector = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    auto tSplitStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> vargsiukaiV;
    for (auto it = visiStudentaiV.begin(); it != visiStudentaiV.end();) {
        if (it->rezVid < 5 || it->rezMed < 5) {
            vargsiukaiV.push_back(*it);
            it = visiStudentaiV.erase(it);
        }
        else ++it;
    }
    auto tSplitEndV = std::chrono::high_resolution_clock::now();
    rez.splitTimeVector = std::chrono::duration<double>(tSplitEndV - tSplitStartV).count();

    auto tWriteStartV = std::chrono::high_resolution_clock::now();
    std::ofstream outKietV(base + "_kietiakai_vector_2strategija.txt");
    std::ofstream outVargV(base + "_vargsiukai_vector_2strategija.txt");
    for (auto& s : visiStudentaiV)
        outKietV << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";
    for (auto& s : vargsiukaiV)
        outVargV << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";
    outKietV.close();
    outVargV.close();
    auto tWriteEndV = std::chrono::high_resolution_clock::now();
    rez.writeTimeVector = std::chrono::duration<double>(tWriteEndV - tWriteStartV).count();

    // ================= ATMINTIES SKAICIAVIMAS VECTOR =================
    size_t totalBytesV = 0;
    for (auto& s : visiStudentaiV) totalBytesV += sizeof(Studentas) + s.paz.capacity() * sizeof(int);
    for (auto& s : vargsiukaiV) totalBytesV += sizeof(Studentas) + s.paz.capacity() * sizeof(int);
    rez.memMBVector = totalBytesV / (1024.0 * 1024.0);

    // ================= LIST =================
    std::ifstream open_f2(failas); // naujas ifstream list daliai
    if (!open_f2.is_open()) {
        std::cout << "Nepavyko atidaryti failo (list versijai)!\n";
        return rez;
    }

    std::list<Studentas> visiStudentaiL;
    lineCounter = 0;
    auto tReadStartL = std::chrono::high_resolution_clock::now();

    while (std::getline(open_f2, eilute)) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eilute);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) {
            int x;
            ss >> x;
            s.paz.push_back(x);
        }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiL.push_back(s);
    }

	auto tReadEndL = std::chrono::high_resolution_clock::now(); //high_resolution_clock reiskia didziausia tiksluma, now() - dabartinis laikas
	rez.readTimeList = std::chrono::duration<double>(tReadEndL - tReadStartL).count(); //duration - skirtumas tarp dvieju laiko tasku

    auto tSplitStartL = std::chrono::high_resolution_clock::now();
    std::list<Studentas> vargsiukaiL;
    for (auto it = visiStudentaiL.begin(); it != visiStudentaiL.end();) {
		if (it->rezVid < 5 || it->rezMed < 5) { // -> nurodo i nario reiksme per iteratoriu, t.y. it yra iteratorius i Studentas objekta
            vargsiukaiL.push_back(*it);
            it = visiStudentaiL.erase(it);
        }
        else ++it;
    }
    auto tSplitEndL = std::chrono::high_resolution_clock::now();
    rez.splitTimeList = std::chrono::duration<double>(tSplitEndL - tSplitStartL).count();
     
	auto tWriteStartL = std::chrono::high_resolution_clock::now(); //auto - automatinis kintamojo tipas
    std::ofstream outKietL(base + "_kietiakai_list_2strategija.txt");
    std::ofstream outVargL(base + "_vargsiukai_list_2strategija.txt");
    for (auto& s : visiStudentaiL)
        outKietL << std::left << std::setw(15) << s.vard
		<< std::setw(15) << s.pav //stewd - nustato lauko plotį
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";
    for (auto& s : vargsiukaiL)
        outVargL << std::left << std::setw(15) << s.vard
        << std::setw(15) << s.pav
        << std::setw(10) << s.rezVid
        << std::setw(10) << s.rezMed << "\n";
    outKietL.close();
    outVargL.close();
    auto tWriteEndL = std::chrono::high_resolution_clock::now();
    rez.writeTimeList = std::chrono::duration<double>(tWriteEndL - tWriteStartL).count();

    // ================= ATMINTIES SKAICIAVIMAS LIST =================
    size_t totalBytesL = 0;
	for (auto& s : visiStudentaiL) totalBytesL += sizeof(Studentas) + 2 * sizeof(void*) + s.paz.capacity() * sizeof(int); //void* - rodykle i bet koki tipa
    for (auto& s : vargsiukaiL) totalBytesL += sizeof(Studentas) + 2 * sizeof(void*) + s.paz.capacity() * sizeof(int); //sizeof(void*) - dvi rodykles (i sekanti ir i pries tai buvusi saraso elementa)
    rez.memMBList = totalBytesL / (1024.0 * 1024.0);

    // ================= SPAUSDINIMAS =================
    std::cout << "\n=== Strategija 2 rezultatai VECTORIUI ===\n";
    std::cout << "Skaitymo laikas: " << rez.readTimeVector << " s\n";
    std::cout << "Skaidymo laikas: " << rez.splitTimeVector << " s\n";
    std::cout << "Irasymo laikas: " << rez.writeTimeVector << " s\n";
    std::cout << "Naudota atmintis: " << rez.memMBVector << " MB\n";

    std::cout << "\n=== Strategija 2 rezultatai LISTUI ===\n";
    std::cout << "Skaitymo laikas: " << rez.readTimeList << " s\n";
    std::cout << "Skaidymo laikas: " << rez.splitTimeList << " s\n";
    std::cout << "Irasymo laikas: " << rez.writeTimeList << " s\n";
    std::cout << "Naudota atmintis: " << rez.memMBList << " MB\n";

    return rez;
}







Rezultatai strategija1_STL_vectoriui(const std::string& failas) {
    Rezultatai rez{};
    std::string base = failas.substr(0, failas.find(".txt"));
    std::string eilute;
    int lineCounter = 0;

    // ================= VECTOR =================
    std::ifstream open_f(failas);
    if (!open_f.is_open()) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return rez;
    }

    auto tReadStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> visiStudentaiV;
    visiStudentaiV.reserve(10'000'000);

    // Skaitome failą
    while (std::getline(open_f, eilute)) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eilute); // kiekvienai eilutei naujas objektas
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) {
            int x;
            ss >> x;
            s.paz.push_back(x);
        }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiV.push_back(s);
    }


    auto tReadEndV = std::chrono::high_resolution_clock::now();
    rez.readTimeVector = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    // ================== SKAIDYMAS RANKINIU BŪDU ==================
    auto tSplitStartV = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> kietiakaiV, vargsiukaiV;
    kietiakaiV.reserve(visiStudentaiV.size());
    vargsiukaiV.reserve(visiStudentaiV.size());

    for (size_t i = 0; i < visiStudentaiV.size(); i++) {
        const Studentas& s = visiStudentaiV[i];
        if (s.rezVid >= 5 && s.rezMed >= 5)
            kietiakaiV.push_back(s);
        else
            vargsiukaiV.push_back(s);
    }

    auto tSplitEndV = std::chrono::high_resolution_clock::now();
    rez.splitTimeVector = std::chrono::duration<double>(tSplitEndV - tSplitStartV).count();

    // ================== PAPILDOMAS SKAIDYMAS NAUDOJANT std::partition ==================
    auto tPartStartV = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> copy = visiStudentaiV;
    auto itPart = std::partition(copy.begin(), copy.end(),
        [](const Studentas& s) {
            return s.rezVid >= 5 && s.rezMed >= 5;
        });

    std::vector<Studentas> kietiakaiPart(copy.begin(), itPart);
    std::vector<Studentas> vargsiukaiPart(itPart, copy.end());

    auto tPartEndV = std::chrono::high_resolution_clock::now();
    double partitionTime = std::chrono::duration<double>(tPartEndV - tPartStartV).count();



    // ================== RAŠYMAS Į FAILUS ==================
    auto tWriteStartV = std::chrono::high_resolution_clock::now();

    std::ofstream outKietV(base + "_kietiakai_vector_1strategija.txt");
    std::ofstream outVargV(base + "_vargsiukai_vector_1strategija.txt");

    for (size_t i = 0; i < kietiakaiV.size(); i++)
        outKietV << std::left << std::setw(15) << kietiakaiV[i].vard
        << std::setw(15) << kietiakaiV[i].pav
        << std::setw(10) << kietiakaiV[i].rezVid
        << std::setw(10) << kietiakaiV[i].rezMed << "\n";

    for (size_t i = 0; i < vargsiukaiV.size(); i++)
        outVargV << std::left << std::setw(15) << vargsiukaiV[i].vard
        << std::setw(15) << vargsiukaiV[i].pav
        << std::setw(10) << vargsiukaiV[i].rezVid
        << std::setw(10) << vargsiukaiV[i].rezMed << "\n";

    outKietV.close();
    outVargV.close();

    auto tWriteEndV = std::chrono::high_resolution_clock::now();
    rez.writeTimeVector = std::chrono::duration<double>(tWriteEndV - tWriteStartV).count();

    rez.memMBVector = (sizeof(Studentas) * visiStudentaiV.size() +
        sizeof(Studentas) * (kietiakaiV.size() + vargsiukaiV.size())) / (1024.0 * 1024.0);

    std::cout << "\n=== VECTOR STRATEGIJA 1 ===\n";
    std::cout << "  Studentu viso: " << visiStudentaiV.size() << "\n";
    std::cout << "  Kietiakai:     " << kietiakaiV.size() << "\n";
    std::cout << "  Vargsiukai:    " << vargsiukaiV.size() << "\n";
    std::cout << "  Nuskaitymas:   " << rez.readTimeVector << " s\n";
    std::cout << "  Skaidymas:     " << rez.splitTimeVector << " s\n";
    std::cout << "  Rasymas:       " << rez.writeTimeVector << " s\n";
    std::cout << "  Bendra atmintis (vector): "
        << std::fixed << std::setprecision(2) << rez.memMBVector << " MB\n";



 return rez;
}






Rezultatai strategija2_STL_vectoriui(const std::string& failas) {
    Rezultatai rez{};
    std::string base = failas.substr(0, failas.find(".txt"));
    std::string eilute;
    int lineCounter = 0;

    // ================= VECTOR =================
    std::ifstream open_f(failas);
    if (!open_f.is_open()) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return rez;
    }

    auto tReadStartV = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> visiStudentaiV;
    visiStudentaiV.reserve(10'000'000);

    // Skaitome failą
    while (std::getline(open_f, eilute)) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        std::stringstream ss(eilute); // kiekvienai eilutei naujas objektas
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) {
            int x;
            ss >> x;
            s.paz.push_back(x);
        }
        ss >> s.egzas;
        skaiciuokRezultatus(s);
        visiStudentaiV.push_back(s);
    }


    auto tReadEndV = std::chrono::high_resolution_clock::now();
    rez.readTimeVector = std::chrono::duration<double>(tReadEndV - tReadStartV).count();

    // ================= Skaidymas / trynimas į kitą failą =================
    auto tSplitStart = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> vargsiukaiV;
    vargsiukaiV.reserve(visiStudentaiV.size());

    std::remove_copy_if(
        visiStudentaiV.begin(), visiStudentaiV.end(),
        std::back_inserter(vargsiukaiV),
        [](const Studentas& s) { return s.rezVid >= 5 && s.rezMed >= 5; }
    );

    visiStudentaiV.erase(
        std::remove_if(
            visiStudentaiV.begin(), visiStudentaiV.end(),
            [](const Studentas& s) { return s.rezVid < 5 || s.rezMed < 5; }
        ),
        visiStudentaiV.end()
    );

    auto tSplitEnd = std::chrono::high_resolution_clock::now();
    rez.splitTime = std::chrono::duration<double>(tSplitEnd - tSplitStart).count();

    // ================= Rašymas į failus =================
    auto tWriteStart = std::chrono::high_resolution_clock::now();

    std::ofstream outKietV(base + "_kietiakai_vector_2strategija_STL.txt");
    std::ofstream outVargV(base + "_vargsiukai_vector_2strategija_STL.txt");

    auto writeStudent = [](std::ofstream& out, const Studentas& s) {
        out << std::left << std::setw(15) << s.vard
            << std::setw(15) << s.pav
            << std::setw(10) << s.rezVid
            << std::setw(10) << s.rezMed << "\n";
        };

    std::for_each(visiStudentaiV.begin(), visiStudentaiV.end(), [&](const Studentas& s) { writeStudent(outKietV, s); });
    std::for_each(vargsiukaiV.begin(), vargsiukaiV.end(), [&](const Studentas& s) { writeStudent(outVargV, s); });

    outKietV.close();
    outVargV.close();

    auto tWriteEnd = std::chrono::high_resolution_clock::now();
    rez.writeTime = std::chrono::duration<double>(tWriteEnd - tWriteStart).count();

    // ================= Atmintis =================
    rez.memMB = (sizeof(Studentas) * (visiStudentaiV.size() + vargsiukaiV.size())) / (1024.0 * 1024.0);

    // ================= Tik reikalingų rezultatų spausdinimas =================
    std::cout << "\n=== VECTOR STRATEGIJA 2 SU STL ===\n";
    std::cout << "  Nuskaitymas: " << rez.readTime << " s\n";
    std::cout << "  Skaidymas/Trinimas: " << rez.splitTime << " s\n";
    std::cout << "  Failu rasymas: " << rez.writeTime << " s\n";
    std::cout << "  Atmintis: " << std::fixed << std::setprecision(2) << rez.memMB << " MB\n";

    return rez; // Grąžiname užpildytą struktūrą
}






// ================= STRATEGIJA 3 =================
void Strategija3(const std::string& failas) {
    Rezultatai r1 = strategija1_skaidymas(failas);
    Rezultatai r2 = Strategija2(failas);

    double totalTimeR1_V = r1.readTimeVector + r1.splitTimeVector + r1.writeTimeVector;
    double totalTimeR2_V = r2.readTimeVector + r2.splitTimeVector + r2.writeTimeVector;
    double totalTimeR1_L = r1.readTimeList + r1.splitTimeList + r1.writeTimeList;
    double totalTimeR2_L = r2.readTimeList + r2.splitTimeList + r2.writeTimeList;

    if (totalTimeR1_V < totalTimeR2_V) {
        std::cout << "\n===========================\n";
        strategija1_STL_vectoriui(failas);

        if (totalTimeR2_L < totalTimeR1_L) {
            std::cout << "\n=== Strategija 2 rezultatai LISTUI ===\n";
            std::cout << "Skaitymo laikas: " << r2.readTimeList << " s\n";
            std::cout << "Skaidymo laikas: " << r2.splitTimeList << " s\n";
            std::cout << "Irasymo laikas: " << r2.writeTimeList << " s\n";
            std::cout << "Naudota atmintis: " << r2.memMBList << " MB\n";
        }
        else {
            std::cout << "\n=== Strategija 1 rezultatai LISTUI ===\n";
            std::cout << "Skaitymo laikas: " << r1.readTimeList << " s\n";
            std::cout << "Skaidymo laikas: " << r1.splitTimeList << " s\n";
            std::cout << "Irasymo laikas: " << r1.writeTimeList << " s\n";
            std::cout << "Naudota atmintis: " << r1.memMBList << " MB\n";
        }

    }
    else {
        std::cout << "\n===========================\n";
        strategija2_STL_vectoriui(failas);

        if (totalTimeR2_L < totalTimeR1_L) {
            std::cout << "\n=== Strategija 2 rezultatai LISTUI ===\n";
            std::cout << "Skaitymo laikas: " << r2.readTimeList << " s\n";
            std::cout << "Skaidymo laikas: " << r2.splitTimeList << " s\n";
            std::cout << "Irasymo laikas: " << r2.writeTimeList << " s\n";
            std::cout << "Naudota atmintis: " << r2.memMBList << " MB\n";
        }
        else {
            std::cout << "\n=== Strategija 1 rezultatai LISTUI ===\n";
            std::cout << "Skaitymo laikas: " << r1.readTimeList << " s\n";
            std::cout << "Skaidymo laikas: " << r1.splitTimeList << " s\n";
            std::cout << "Irasymo laikas: " << r1.writeTimeList << " s\n";
            std::cout << "Naudota atmintis: " << r1.memMBList << " MB\n";
        }
    }
}









void analizuokVisusFailusMinimaliai() {
    int rezPasirinkimas;
    std::cout << "\nKokius rezultatus spausdinti i failus?\n"
        << "1 - Tik vidurki\n2 - Tik mediana\n3 - Abu\nPasirinkimas: ";
    std::cin >> rezPasirinkimas;

    int rikiavimas;
    std::cout << "Pagal ka rikiuoti galutinius rezultatus?\n"
        << "1 - Vardas (A-Z)\n"
        << "2 - Pavarde (A-Z)\n"
        << "3 - Vidurkis didejimo tvarka\n"
        << "4 - Vidurkis mazejimo tvarka\n"
        << "5 - Mediana didejimo tvarka\n"
        << "6 - Mediana mazejimo tvarka\n"
        << "Pasirinkimas: ";
    std::cin >> rikiavimas;

    // --- Vartotojas įveda failą ---
    std::string failas;
    std::cout << "\nIveskite failo pavadinima: ";
    std::cin >> failas;

    std::cout << "\n=== Apdorojamas failas: " << failas << " ===\n";

    FILE* open_f = fopen(failas.c_str(), "r");
    if (!open_f) {
        std::cout << "Nepavyko atidaryti failo!\n";
        return;
    }

    std::string base = failas.substr(0, failas.find(".txt"));

    std::vector<Studentas> visiStudentai;
    visiStudentai.reserve(10'000'000);
    std::list<Studentas> visiStudentaiL;

    char eil_r[500];
    int lineCounter = 0;

    double readTimeV = 0, calcTimeV = 0, writeTimeV = 0;

    // --- Vector skaitymas ir apdorojimas ---
    while (fgets(eil_r, sizeof(eil_r), open_f) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        auto t1 = std::chrono::high_resolution_clock::now();
        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        auto t2 = std::chrono::high_resolution_clock::now();
        readTimeV += std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        skaiciuokRezultatus(s);
        auto t4 = std::chrono::high_resolution_clock::now();
        calcTimeV += std::chrono::duration<double>(t4 - t3).count();

        visiStudentai.push_back(s);
    }
    fclose(open_f);

    std::cout << "Vector: Nuskaityta " << visiStudentai.size() << " studentu\n";

    // --- Skirstymas į protingus ir kvailius ---
    std::vector<Studentas> protingiV, kvailiV;
    protingiV.reserve(visiStudentai.size());
    kvailiV.reserve(visiStudentai.size());

    for (auto& s : visiStudentai) {
        if (s.rezVid >= 5 && s.rezMed >= 5) protingiV.push_back(s);
        else kvailiV.push_back(s);
    }

    auto rikiuokV = [&](std::vector<Studentas>& v) {
        switch (rikiavimas) {
        case 1: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.vard < b.vard; }); break;
        case 2: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.pav < b.pav; }); break;
        case 3: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezVid < b.rezVid; }); break;
        case 4: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezVid > b.rezVid; }); break;
        case 5: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezMed < b.rezMed; }); break;
        case 6: std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return a.rezMed > b.rezMed; }); break;
        }
        };
    rikiuokV(protingiV);
    rikiuokV(kvailiV);


    std::string proNameVector = base + "_protinguliai_vector.txt";
    std::string kvaNameVector = base + "_kvailiukai_vector.txt";
    std::ofstream outProV(proNameVector), outKvaV(kvaNameVector);

    auto writeV = [&](std::ofstream& out, const std::vector<Studentas>& v, const std::string& fname) {
        double writeTime = 0;
        for (auto& s : v) {
            auto t1 = std::chrono::high_resolution_clock::now();
            out << std::left << std::setw(15) << s.vard
                << std::setw(15) << s.pav;
            if (rezPasirinkimas == 1) out << std::setw(15) << s.rezVid;
            else if (rezPasirinkimas == 2) out << std::setw(15) << s.rezMed;
            else out << std::setw(15) << s.rezVid << std::setw(15) << s.rezMed;
            out << "\n";
            auto t2 = std::chrono::high_resolution_clock::now();
            writeTime += std::chrono::duration<double>(t2 - t1).count();
        }
        std::cout << "Failas irasytas: " << fname << " (rasymo laikas: " << writeTime << " s)\n";
        return writeTime;
        };

    writeTimeV += writeV(outProV, protingiV, proNameVector);
    writeTimeV += writeV(outKvaV, kvailiV, kvaNameVector);
    outProV.close(); outKvaV.close();

    std::cout << "Vector rezultatai:\n";
    std::cout << "  Skaitymas: " << readTimeV << " s\n";
    std::cout << "  Skaiciavimas: " << calcTimeV << " s\n";
    std::cout << "  Rasymas: " << writeTimeV << " s\n";


    FILE* open_f2 = fopen(failas.c_str(), "r");
    if (!open_f2) {
        std::cout << "Nepavyko atidaryti failo antram skaitymui (list)!\n";
        return;
    }

    double readTimeL = 0, calcTimeL = 0, writeTimeL = 0;
    lineCounter = 0;

    while (fgets(eil_r, sizeof(eil_r), open_f2) != nullptr) {
        lineCounter++;
        if (lineCounter <= 2) continue;

        auto t1 = std::chrono::high_resolution_clock::now();
        std::stringstream ss(eil_r);
        Studentas s;
        ss >> s.vard >> s.pav;
        for (int i = 0; i < 5; i++) { int x; ss >> x; s.paz.push_back(x); }
        ss >> s.egzas;
        auto t2 = std::chrono::high_resolution_clock::now();
        readTimeL += std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        skaiciuokRezultatus(s);
        auto t4 = std::chrono::high_resolution_clock::now();
        calcTimeL += std::chrono::duration<double>(t4 - t3).count();

        visiStudentaiL.push_back(s);
    }
    fclose(open_f2);

    std::list<Studentas> protingiL, kvailiL;
    for (auto& s : visiStudentaiL) {
        if (s.rezVid >= 5 && s.rezMed >= 5) protingiL.push_back(s);
        else kvailiL.push_back(s);
    }

    auto rikiuokL = [&](std::list<Studentas>& l) {
        switch (rikiavimas) {
        case 1: l.sort([](auto& a, auto& b) {return a.vard < b.vard; }); break;
        case 2: l.sort([](auto& a, auto& b) {return a.pav < b.pav; }); break;
        case 3: l.sort([](auto& a, auto& b) {return a.rezVid < b.rezVid; }); break;
        case 4: l.sort([](auto& a, auto& b) {return a.rezVid > b.rezVid; }); break;
        case 5: l.sort([](auto& a, auto& b) {return a.rezMed < b.rezMed; }); break;
        case 6: l.sort([](auto& a, auto& b) {return a.rezMed > b.rezMed; }); break;
        }
        };
    rikiuokL(protingiL);
    rikiuokL(kvailiL);

    std::string proNameList = base + "_protinguliai_list.txt";
    std::string kvaNameList = base + "_kvailiukai_list.txt";
    std::ofstream outProL(proNameList), outKvaL(kvaNameList);

    auto writeL = [&](std::ofstream& out, const std::list<Studentas>& l, const std::string& fname) {
        double writeTime = 0;
        for (auto& s : l) {
            auto t1 = std::chrono::high_resolution_clock::now();
            out << std::left << std::setw(15) << s.vard
                << std::setw(15) << s.pav;
            if (rezPasirinkimas == 1) out << std::setw(15) << s.rezVid;
            else if (rezPasirinkimas == 2) out << std::setw(15) << s.rezMed;
            else out << std::setw(15) << s.rezVid << std::setw(15) << s.rezMed;
            out << "\n";
            auto t2 = std::chrono::high_resolution_clock::now();
            writeTime += std::chrono::duration<double>(t2 - t1).count();
        }
        std::cout << "Failas irasytas: " << fname << " (rasymo laikas: " << writeTime << " s)\n";
        return writeTime;
        };

    writeTimeL += writeL(outProL, protingiL, proNameList);
    writeTimeL += writeL(outKvaL, kvailiL, kvaNameList);
    outProL.close(); outKvaL.close();

    std::cout << "List rezultatai:\n";
    std::cout << "  Skaitymas: " << readTimeL << " s\n";
    std::cout << "  Skaiciavimas: " << calcTimeL << " s\n";
    std::cout << "  Rasymas: " << writeTimeL << " s\n";
}



void generuokFailus() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string failoVardas;
    int kiek;
    std::cout << "Iveskite failo pavadinima: ";
    std::cin >> failoVardas;
    std::cout << "Kiek studentu generuoti? ";
    std::cin >> kiek;

    std::ofstream out(failoVardas);
    if (!out) {
        std::cout << "Nepavyko sukurti failo!\n";
        return;
    }

    // Header
    out << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << "ND1 ND2 ND3 ND4 ND5 Egzaminas\n";

    for (int i = 0; i < kiek; ++i) {
        std::string vard = "vardas" + std::to_string(rand() % 1000);
        std::string pav = "pavarde" + std::to_string(rand() % 1000);

        out << std::left << std::setw(15) << vard
            << std::setw(15) << pav;

        for (int j = 0; j < 5; ++j) out << rand() % 11 << " "; // ND
        out << rand() % 11 << "\n"; // Egzaminas
    }

    out.close();
    std::cout << "Failas '" << failoVardas << "' sugeneruotas su " << kiek << " studentu.\n";
}
