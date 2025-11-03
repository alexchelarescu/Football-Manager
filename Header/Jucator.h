#pragma once

#include <iostream>
#include <string>
#include <utility>
#include "PozitieJucator.h"


class Jucator {
private:
    std::string m_nume;
    int m_varsta;
    PozitieJucator m_pozitie;
    int m_ovr;

public:
    //Getters
    [[nodiscard]] std::string getNume() const {
        return this->m_nume;
    }

    [[nodiscard]] PozitieJucator getPozitie() const {
        return this->m_pozitie;
    }

    [[nodiscard]] int getOVR() const {
        return this->m_ovr;
    }

    //Functie pentru a creste OVR-ul prin antrenament dupa meci
    void imbunatatesteOVR(int puncte) {
        this->m_ovr += puncte;
        if (this->m_ovr > 99) {
            this->m_ovr = 99; // Plafonare la 99
        }
    }

    Jucator(std::string nume, int varsta,PozitieJucator pozitie, int ovr): m_nume{std::move(nume)}, m_varsta{varsta}, m_pozitie{pozitie}, m_ovr{ovr}
    {
        if (this->m_ovr > 99) this->m_ovr = 99;
        if (this->m_ovr < 1) this->m_ovr = 1;
        if (this->m_varsta < 16) this->m_varsta = 16;
    }

    friend std::ostream& operator<<(std::ostream& os, const Jucator& j)
    {
        os << "[";
        switch (j.m_pozitie) // nici aici nu am nev de getters pt ca am acces direct
        {
            case PozitieJucator::PORTAR:  os << "Portar"; break;
            case PozitieJucator::FUNDAS:  os << "Fundas"; break;
            case PozitieJucator::MIJLOCAS: os << "Mijlocas"; break;
            case PozitieJucator::ATACANT: os << "Atacant"; break;
            default:                      os << "Necunoscuta"; break;
        }
        os << "] ";

        os << j.m_nume<< " (OVR: " << j.m_ovr << ")" << " - Varsta: " << j.m_varsta;
        return os;
    }
};