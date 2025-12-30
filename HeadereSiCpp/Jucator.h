#ifndef OOP_JUCATOR_H
#define OOP_JUCATOR_H
#include <string>
#include <iostream>
#include "PozitieJucator.h"

class Jucator {
private:
    std::string m_nume;
    int m_varsta;
    PozitieJucator m_pozitie;
    int m_ovr;

public:
    Jucator(std::string nume, int varsta, PozitieJucator pozitie, int ovr);
    ~Jucator() = default;

    void imbunatatesteOVR(int puncte);

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] PozitieJucator getPozitie() const;
    [[nodiscard]] int getOVR() const;
    [[nodiscard]] int getVarsta() const { return m_varsta; }

    friend std::ostream& operator<<(std::ostream& os, const Jucator& j);
};
#endif
