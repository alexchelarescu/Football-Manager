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

    /*[[nodiscard]] int getVarsta() const {
        return this->m_varsta;
    }*/

    [[nodiscard]] PozitieJucator getPozitie() const {
        return this->m_pozitie;
    }

    [[nodiscard]] int getOVR() const {
        return this->m_ovr;
    }
    Jucator(std::string nume, int varsta,PozitieJucator pozitie, int ovr): m_nume{std::move(nume)}, m_varsta{varsta}, m_pozitie{pozitie}, m_ovr{ovr}
    {
    if (this->m_ovr > 99) this->m_ovr = 99;
    if (this->m_ovr < 1) this->m_ovr = 1;
    if (this->m_varsta < 16) this->m_varsta = 16;
}
    friend std::ostream& operator<<(std::ostream& os, const Jucator& j);

private:
    [[nodiscard]] std::string getPozitieCaString() const {
        switch (this->m_pozitie) {
            case PozitieJucator::PORTAR:  return "Portar";
            case PozitieJucator::FUNDAS:  return "Fundas";
            case PozitieJucator::MIJLOCAS: return "Mijlocas";
            case PozitieJucator::ATACANT: return "Atacant";
            default:                      return "Necunoscuta";
        }
    }
};