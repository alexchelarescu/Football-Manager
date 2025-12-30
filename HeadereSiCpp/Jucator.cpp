#include "Jucator.h"
#include "Exceptii.h"
#include <utility>    // l-am folosit pentru std::move

Jucator::Jucator(std::string nume, int varsta, PozitieJucator pozitie, int ovr):
    m_nume(std::move(nume)),
    m_varsta(varsta),
    m_pozitie(pozitie),
    m_ovr(ovr)
    {
    if (m_nume.empty())
        {
        throw EroareDateInvalide("Numele jucatorului nu poate fi vid");
        }

    if (this->m_ovr > 99) this->m_ovr = 99;
    if (this->m_ovr < 1) this->m_ovr = 1;
    if (this->m_varsta < 16) this->m_varsta = 16;
}

void Jucator::imbunatatesteOVR(int puncte) {
    this->m_ovr += puncte;
    if (this->m_ovr > 99) {
        this->m_ovr = 99; // ovr maxim blocat la 99
    }
}

const std::string& Jucator::getNume() const {
    return m_nume;
}

PozitieJucator Jucator::getPozitie() const {
    return m_pozitie;
}

int Jucator::getOVR() const {
    return m_ovr;
}

std::ostream& operator<<(std::ostream& os, const Jucator& j) {
    os << "[";
    switch (j.m_pozitie) {
        case PozitieJucator::PORTAR:   os << "GK"; break;
        case PozitieJucator::FUNDAS:   os << "DEF"; break;
        case PozitieJucator::MIJLOCAS: os << "MID"; break;
        case PozitieJucator::ATACANT:  os << "ATT"; break;
    }
    os << "] " << j.m_nume << " | OVR: " << j.m_ovr << " | Varsta: " << j.m_varsta;
    return os;
}