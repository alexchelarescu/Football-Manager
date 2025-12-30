#include "Exceptii.h"
#include <string>


ManagerEroare::ManagerEroare(const std::string& mesaj)
    : std::runtime_error("Eroare Manager: " + mesaj) {}

EroareDateInvalide::EroareDateInvalide(const std::string& detaliu)
    : ManagerEroare("Configuratie/Fisier invalida - " + detaliu) {}

EroareEconomie::EroareEconomie(const std::string& actiune, int necesar)
    : ManagerEroare("Resurse insuficiente pentru " + actiune + ". Necesar: " + std::to_string(necesar)) {}

EroareReguliCompetitie::EroareReguliCompetitie(const std::string& regulaIncalcata)
    : ManagerEroare("Regula de joc incalcata: " + regulaIncalcata) {}