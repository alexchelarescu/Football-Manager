#ifndef OOP_POZITIEJUCATOR_H
#define OOP_POZITIEJUCATOR_H

#include <string>
#include "Exceptii.h"

enum class PozitieJucator {
    PORTAR,
    FUNDAS,
    MIJLOCAS,
    ATACANT
};


inline PozitieJucator stringToPozitie(const std::string& str) {
    if (str == "GK") return PozitieJucator::PORTAR;
    if (str == "DEF") return PozitieJucator::FUNDAS;
    if (str == "MID") return PozitieJucator::MIJLOCAS;
    if (str == "ATT") return PozitieJucator::ATACANT;

    // aruncam o exceptie specifica daca datele din fisier sunt corupte
    throw EroareDateInvalide("Pozitie necunoscuta in fisierul de date: " + str);
}
#endif
