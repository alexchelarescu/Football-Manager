#pragma once
 #include <iostream>
 #include <string>
 #include <utility>
 #include <vector>
 #include "Jucator.h"
 #include <limits>   // necesar pentru validarea inputului (std::numeric_limits)
 #include <iomanip> // pentru std::fixed si std::setprecision

class Echipa {
private:
    std::string m_nume;
    int m_obiectiv; // locul minim in clasament
    int m_puncteClasament{};
    int m_puncteUpgrade{};
    int m_nivelStadion{}; // nivelul stadionului (ex: 0,1, 2, 3...)
    int m_moral{50};        // moralul echipei (0-100)

    std::vector<Jucator> m_portari;
    std::vector<Jucator> m_fundasi;
    std::vector<Jucator> m_mijlocasi;
    std::vector<Jucator> m_atacanti;

 // media OVR pentru o lista specifica de jucatori pentru fiecare pozitie
    static double calculeazaMediePozitie(const std::vector<Jucator>& jucatori)
    {
        if (jucatori.empty()) {
            return 60.0; // o medie de penalizare
        }
        double suma = 0.0;
        for (const Jucator& j : jucatori) {
            suma += j.getOVR();
        }
        return suma / static_cast<double>(jucatori.size());
    }


     // OVR-ul total al echipei
    [[nodiscard]] double calculeazaOVR() const
    {
        double mediePortari = calculeazaMediePozitie(m_portari);
        double medieFundasi = calculeazaMediePozitie(m_fundasi);
        double medieMijlocasi = calculeazaMediePozitie(m_mijlocasi);
        double medieAtacanti = calculeazaMediePozitie(m_atacanti);

        // media mediilor
        return (mediePortari + medieFundasi + medieMijlocasi + medieAtacanti) / 4.0;
    }

    // modifica moralul intr-un mod controlat(adica il mentine intre 0 si 100)
    void modificaMoral(int valoare)
    {
        this->m_moral += valoare;
        if (this->m_moral > 100) {
            this->m_moral = 100;
        } else if (this->m_moral < 0) {
            this->m_moral = 0;
        }
    }

    // helper privat pentru antrenament
    static void antreneazaJucatorSelectat(std::vector<Jucator>& jucatori, const std::string& numePozitie) {
        if (jucatori.empty()) {
            std::cout << " Nu exista jucatori pe pozitia: " << numePozitie << "\n";
            return;
        }

        // afisare lista de jucatori
        std::cout << "\n Alege un jucator pentru " << numePozitie << " (1-" << jucatori.size() << "):\n";
        for (size_t i = 0; i < jucatori.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << jucatori[i] << "\n";
        }

        int indexAles = 0;
        bool inputValid = false;

        // validez input
        while (!inputValid) {
            std::cout << " Selectie: ";
            // verific daca inputul e nr
            if (!(std::cin >> indexAles)) {
                std::cout << "Eroare: Introduceti un numar.\n";
                std::cin.clear(); // reseteaza starea de eroare a std::cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Curata buffer-ul de input (goleste ce a fost scris gresit)
            } else if (indexAles < 1 || indexAles > static_cast<int>(jucatori.size())) {
                // verific daca nr este in intervalul corespunzator jucatorilor pe care ii am in lot
                std::cout << "Eroare: Numarul trebuie sa fie intre 1 si " << jucatori.size() << ".\n";
            } else {
                inputValid = true;
            }
        }

        // pentru a curata buffer-ul dupa o citire reusita si pentru a preveni probleme la urmatorul cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // folosesc (&) pentru a modifica jucatorul original din vector
        Jucator& jucatorAles = jucatori.at(indexAles - 1); // convertesc la index 0-based

        int ovrVechi = jucatorAles.getOVR();
        jucatorAles.imbunatatesteOVR(1); // functia din Jucator care creste ovr-ul prin antrenament

        std::cout << " Dupa antrenament " << jucatorAles.getNume() << " a crescut la " << jucatorAles.getOVR() << " OVR (de la " << ovrVechi << " OVR).\n";
    }

public:
    [[nodiscard]] std::string getNume() const { return this->m_nume; }
    [[nodiscard]] int getPuncteUpgrade() const { return this->m_puncteUpgrade; }
    //[[nodiscard]] int getPuncteClasament() const { return this->m_puncteClasament; }
    [[nodiscard]] int getObiectiv() const { return this->m_obiectiv; }
    [[nodiscard]] int getNivelStadion() const { return this->m_nivelStadion; }
    [[nodiscard]] int getMoral() const { return this->m_moral; }

    //noi getters care sa ma ajute la simularea golurilor din meci
    [[nodiscard]] double getRatingAtac() const {
        return calculeazaMediePozitie(m_atacanti);
    }
    [[nodiscard]] double getRatingMijloc() const {
        return calculeazaMediePozitie(m_mijlocasi);
    }
    [[nodiscard]] double getRatingAparare() const {
        return calculeazaMediePozitie(m_fundasi);
    }
    [[nodiscard]] double getRatingPortar() const {
        return calculeazaMediePozitie(m_portari);
    }

[[nodiscard]] double getOVR() const
{
    return this->calculeazaOVR();
}

void adaugaJucator(const Jucator& jucator)
{
    switch (jucator.getPozitie())
        {
        case PozitieJucator::PORTAR: m_portari.push_back(jucator); break;
        case PozitieJucator::FUNDAS: m_fundasi.push_back(jucator); break;
        case PozitieJucator::MIJLOCAS: m_mijlocasi.push_back(jucator); break;
        case PozitieJucator::ATACANT: m_atacanti.push_back(jucator); break;
    }
}

void adaugaRezultatMeci(int puncteCastigate, int upgradePrimit) {
    this->m_puncteClasament += puncteCastigate;
    this->m_puncteUpgrade += upgradePrimit;

    if (puncteCastigate == 3)
        {
        modificaMoral(10);
        std::cout << " Victorie! Moralul a crescut la " << this->m_moral << ".\n";
    } else if (puncteCastigate == 0)
        {
        modificaMoral(-10);
        std::cout << " Infrangere. Moralul a scazut la " << this->m_moral << ".\n";
    }
    else
        {
        modificaMoral(-2);
        std::cout << " Egal. Moralul a scazut usor la " << this->m_moral << ".\n";
    }
}

void upgradeazaStadion()
{
    int cost = this->m_nivelStadion * 10;

    std::cout << " Costul pentru Nivelul " << (this->m_nivelStadion + 1) << " este " << cost << " puncte. (Ai " << this->m_puncteUpgrade << ")\n";

    if (this->m_puncteUpgrade >= cost)
        {
        this->m_puncteUpgrade -= cost;
        this->m_nivelStadion++;
        std::cout << " Succes! Stadionul are acum Nivelul " << this->m_nivelStadion << ".\n";
        std::cout << " Puncte ramase: " << this->m_puncteUpgrade << ".\n";
    } else
        {
        std::cout << " Puncte insuficiente pentru upgrade!\n";
    }
}

void refaceMoralul()
{
    int cost = 5;
    int moralRefacut = 20;

    std::cout << " Costul pentru (+ " << moralRefacut << " moral) este " << cost << " puncte. (Ai " << this->m_puncteUpgrade << ")\n";

    if (this->m_puncteUpgrade >= cost) {
        this->m_puncteUpgrade -= cost;
        modificaMoral(moralRefacut);
        std::cout << " Succes! Moralul echipei a fost refacut.\n";
        std::cout << " Moral curent: " << this->m_moral << ". Puncte ramase: " << this->m_puncteUpgrade << ".\n";
    } else {
        std::cout << " Puncte insuficiente pentru refacere moral!\n";
    }
}

void gestioneazaAntrenament() {
    std::cout << "\n *SESIUNE DE ANTRENAMENT* \n";
    // apelez helper-ul privat pentru fiecare compartiment
    // vectorii sunt trimisi ca referinta (&), deci pot fi modificati
    antreneazaJucatorSelectat(m_portari, "Portari");
    antreneazaJucatorSelectat(m_fundasi, "Fundasi");
    antreneazaJucatorSelectat(m_mijlocasi, "Mijlocasi");
    antreneazaJucatorSelectat(m_atacanti, "Atacanti");

    // noul OVR al echipei
    std::cout << "\n Noul OVR al echipei este: " << std::fixed << std::setprecision(2) << this->getOVR() << "\n\n";
}

[[nodiscard]] bool verificaObiectiv(int pozitieInClasament) const {
    return pozitieInClasament <= this->m_obiectiv;
}
    Echipa(std::string nume, int obiectiv): m_nume{std::move(nume)}, m_obiectiv{obiectiv} {}

    // Constructor de copiere
    Echipa(const Echipa& alta)
    {
        this->m_nume = alta.m_nume;
        this->m_obiectiv = alta.m_obiectiv;
        this->m_puncteClasament = alta.m_puncteClasament;
        this->m_puncteUpgrade = alta.m_puncteUpgrade;
        this->m_nivelStadion = alta.m_nivelStadion;
        this->m_moral = alta.m_moral;
        this->m_portari = alta.m_portari;
        this->m_fundasi = alta.m_fundasi;
        this->m_mijlocasi = alta.m_mijlocasi;
        this->m_atacanti = alta.m_atacanti;
    }

    // Operator= de copiere
    Echipa& operator=(const Echipa& alta)
    {
        if (this == &alta)
        {
            return *this;
        }
        this->m_nume = alta.m_nume;
        this->m_obiectiv = alta.m_obiectiv;
        this->m_puncteClasament = alta.m_puncteClasament;
        this->m_puncteUpgrade = alta.m_puncteUpgrade;
        this->m_nivelStadion = alta.m_nivelStadion;
        this->m_moral = alta.m_moral;
        this->m_portari = alta.m_portari;
        this->m_fundasi = alta.m_fundasi;
        this->m_mijlocasi = alta.m_mijlocasi;
        this->m_atacanti = alta.m_atacanti;
        return *this;
    }
    ~Echipa() = default;
        // Gol, deoarece std::vector si std::string isi gestioneaza memoria (am gasit in recapitularea c++ ;D )


    //  op<< acum contine si sumarul si lotul
    friend std::ostream& operator<<(std::ostream& os, const Echipa& e)
    {
        //nu folosesc getters pt ca am acces direct la atribute(functie friend)
        os << std::fixed << std::setprecision(2);
        os << "Echipa: " << e.m_nume << "\n"
           << "  OVR: " << e.calculeazaOVR()
           << " | Obiectiv: Loc " << e.m_obiectiv << "\n"
           << "  Puncte: " << e.m_puncteClasament
           << " | Puncte Upgrade: " << e.m_puncteUpgrade << "\n"
           << "  Moral: " << e.m_moral << "/100 "
           << " | Nivel Stadion: " << e.m_nivelStadion;

        // partea de lot (compunerea apelurilor)
        // logica mutata din afiseazaLot care a fost stearsa
        os << "\n\n LOTUL ECHIPEI: " << e.m_nume << " (OVR: " << e.calculeazaOVR() << ") \n";

        os << "\n PORTARI (" << e.m_portari.size() << ") \n";
        for (const Jucator& j : e.m_portari) { os << "  " << j << "\n"; }

        os << "\n FUNDASI (" << e.m_fundasi.size() << ") \n";
        for (const Jucator& j : e.m_fundasi) { os << "  " << j << "\n"; }

        os << "\n MIJLOCASI (" << e.m_mijlocasi.size() << ") \n";
        for (const Jucator& j : e.m_mijlocasi) { os << "  " << j << "\n"; }

        os << "\n ATACANTI (" << e.m_atacanti.size() << ") \n";
        for (const Jucator& j : e.m_atacanti) { os << "  " << j << "\n"; }
        os << "\n\n";

        return os;
    }
};