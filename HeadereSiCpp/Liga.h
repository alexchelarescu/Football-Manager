#ifndef OOP_LIGA_H
#define OOP_LIGA_H

#include <vector>
#include <string>
#include "Echipa.h"

struct ProgramMeci {
    int indexGazda;
    int indexOaspete;
};//sper ca am voie cu struct, pe git s-a precizat fara atribute publice in clase, nu s-a mentionat nimic de struct ;)

class Liga {
private:
    std::string m_numeLiga;
    std::vector<Echipa> m_echipe;
    std::vector<std::vector<ProgramMeci>> m_calendar;
    int m_etapaCurenta = 0;

    void genereazaCalendar();

public:
    explicit Liga(std::string nume);

    void incarcaDinJSON(const std::string& caleConfig, const std::string& caleEchipe);

    void simuleazaEtapaCompleta();
    void afiseazaClasamentComplet() const;


    [[nodiscard]] Echipa& getEchipaDupaIndex(size_t index);
    [[nodiscard]] size_t getNumarEchipe() const;
    [[nodiscard]] bool esteSezonIncheiat() const;
};
#endif