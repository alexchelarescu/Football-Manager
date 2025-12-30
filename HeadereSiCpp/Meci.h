#ifndef OOP_MECI_H
#define OOP_MECI_H

#include "Echipa.h"

//aici gestionez simularea unei partide si actualizarea starii echipelor

class Meci {
private:
    Echipa& m_gazda;
    Echipa& m_oaspete;
    int m_scorGazda;
    int m_scorOaspete;
    bool m_simulat;

    static bool calculeazaSansa(double ratingA, double ratingB);

public:
    //constructorul primeste referinte pentru a valida unicitatea adversarilor
    Meci(Echipa& gazda, Echipa& oaspete);

    ~Meci() = default;

    void simuleaza();

    [[nodiscard]] std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Meci& m);
};

#endif