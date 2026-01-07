#ifndef OOP_LIGA_H
#define OOP_LIGA_H

#include <vector>
#include <string>
#include "Echipa.h"

class ProgramMeci {
private:
    int m_indexGazda;
    int m_indexOaspete;
public:
    ProgramMeci(int gazda, int oaspete) : m_indexGazda(gazda), m_indexOaspete(oaspete) {}
    [[nodiscard]] int getIndexGazda() const { return m_indexGazda; }
    [[nodiscard]] int getIndexOaspete() const { return m_indexOaspete; }
};

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

    void afiseazaListaEchipe() const;
    [[nodiscard]] int getLocInClasament(const std::string& numeEchipa) const;
    [[nodiscard]] Echipa& getEchipaDupaIndex(size_t index);
    [[nodiscard]] size_t getNumarEchipe() const;
    [[nodiscard]] bool esteSezonIncheiat() const;
};
#endif