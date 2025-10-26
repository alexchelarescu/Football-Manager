#pragma once
 #include <iostream>
 #include <string>
 #include <utility>
 #include <vector>
 #include "Jucator.h"
 #include <iomanip>

class Echipa {
private:
    std::string m_nume;
    int m_obiectiv; // Locul minim în clasament
    int m_puncteClasament{};
    int m_puncteUpgrade{};
    int m_nivelStadion{}; // Nivelul stadionului (ex: 1, 2, 3...)
    int m_moral{};        // Moralul echipei (0-100)

    std::vector<Jucator> m_portari;
    std::vector<Jucator> m_fundasi;
    std::vector<Jucator> m_mijlocasi;
    std::vector<Jucator> m_atacanti;

 //Calculează media OVR pentru o lista specifica de jucatori pentru fiecare pozitie.
    [[nodiscard]] double calculeazaMediePozitie(const std::vector<Jucator>& jucatori) const
    {
        if (jucatori.empty()) {
            return 60.0; // O medie de penalizare
        }
        double suma = 0.0;
        for (const Jucator& j : jucatori) {
            suma += j.getOVR();
        }
        return suma / static_cast<double>(jucatori.size());
    }


     //Calculează OVR-ul total al echipei.
    [[nodiscard]] double calculeazaOVR() const
    {
        double mediePortari = calculeazaMediePozitie(m_portari);
        double medieFundasi = calculeazaMediePozitie(m_fundasi);
        double medieMijlocasi = calculeazaMediePozitie(m_mijlocasi);
        double medieAtacanti = calculeazaMediePozitie(m_atacanti);

        // Media mediilor
        return (mediePortari + medieFundasi + medieMijlocasi + medieAtacanti) / 4.0;
    }

    //modifica moralul intr-un mod controlat(adica il mentine intre 0 si 100)
    void modificaMoral(int valoare)
    {
        this->m_moral += valoare;
        if (this->m_moral > 100) {
            this->m_moral = 100;
        } else if (this->m_moral < 0) {
            this->m_moral = 0;
        }
    }

public:
    [[nodiscard]] std::string getNume() const { return this->m_nume; }
    [[nodiscard]] int getPuncteUpgrade() const { return this->m_puncteUpgrade; }
    [[nodiscard]] int getPuncteClasament() const { return this->m_puncteClasament; }
    [[nodiscard]] int getObiectiv() const { return this->m_obiectiv; }
    [[nodiscard]] int getNivelStadion() const { return this->m_nivelStadion; }
    [[nodiscard]] int getMoral() const { return this->m_moral; }

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

void afiseazaLot() const
{
    // Folosim std::fixed și std::setprecision pentru a formata OVR-ul
    std::cout << " LOTUL ECHIPEI: " << this->m_nume << " (OVR: " << std::fixed << std::setprecision(2) << this->getOVR() << ") \n";

    std::cout << "\n PORTARI (" << m_portari.size() << ") \n";
    for (const Jucator& j : m_portari) { std::cout << "  " << j << "\n"; }

    std::cout << "\n FUNDASI (" << m_fundasi.size() << ") \n";
    for (const Jucator& j : m_fundasi) { std::cout << "  " << j << "\n"; }

    std::cout << "\n MIJLOCASI (" << m_mijlocasi.size() << ") \n";
    for (const Jucator& j : m_mijlocasi) { std::cout << "  " << j << "\n"; }

    std::cout << "\n ATACANTI (" << m_atacanti.size() << ") \n";
    for (const Jucator& j : m_atacanti) { std::cout << "  " << j << "\n"; }
    std::cout << "\n\n";
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
        // Gol, deoarece std::vector si std::string isi gestionează memoria (am gasit in recapitularea c++ ;D )

    friend std::ostream& operator<<(std::ostream& os, const Echipa& e)
    {
        // Setăm formatarea OVR-ului
        os << std::fixed << std::setprecision(2);
        os << "Echipa: " << e.getNume()
           << " OVR: " << e.getOVR()
           << " Obiectiv: Loc " << e.getObiectiv()
           << " Puncte: " << e.getPuncteClasament() << "\n"
           << " Moral: " << e.getMoral() << "/100"
           << " Nivel Stadion : " << e.getNivelStadion()
           << " Puncte Upgrade: " << e.getPuncteUpgrade();

        return os;
    }
};