#ifndef OOP_EXCEPTII_H
#define OOP_EXCEPTII_H

#include <string>
#include <stdexcept>

// clasa de baza pentru erorile jocului (deriva din std::runtime_error)
class ManagerEroare : public std::runtime_error {
public:
    explicit ManagerEroare(const std::string& mesaj);
};

//erori de configurare a obiectelor sau parsare fisier
class EroareDateInvalide : public ManagerEroare {
public:
    explicit EroareDateInvalide(const std::string& detaliu);
};

//erori de logica economica (ex: upgrade stadion fara puncte suficiente)
class EroareEconomie : public ManagerEroare {
public:
    explicit EroareEconomie(const std::string& actiune, int necesar);
};

//erori de desfasurare a competitiei (ex: meci invalid)
class EroareReguliCompetitie : public ManagerEroare {
public:
    explicit EroareReguliCompetitie(const std::string& regulaIncalcata);
};

#endif