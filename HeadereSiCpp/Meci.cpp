#include "Meci.h"
#include "Exceptii.h"
#include <random>
#include <fmt/core.h>

Meci::Meci(Echipa& gazda, Echipa& oaspete):
    m_gazda(gazda),
    m_oaspete(oaspete),
    m_scorGazda(0),
    m_scorOaspete(0),
    m_simulat(false)
    {
    if (&m_gazda == &m_oaspete)
        {
        throw EroareReguliCompetitie("O echipa nu poate juca impotriva ei insasi");
        }
    }

bool Meci::calculeazaSansa(double ratingA, double ratingB) {
    if (ratingA <= 0 && ratingB <= 0) return false;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    //am gandit sansa sa fie raportul dintre forta proprie si forta totala
    double sansa = ratingA / (ratingA + ratingB);
    return dis(gen) < sansa;
}

void Meci::simuleaza() {
    if (m_simulat) return;

    double atacG, midG, defG, portarG;
    double atacO, midO, defO, portarO;

    m_gazda.pregatesteRatingMeci(atacG, midG, defG, portarG);
    m_oaspete.pregatesteRatingMeci(atacO, midO, defO, portarO);

    //avantajul terenului propriu influentat de stadion
    atacG += (m_gazda.getNivelStadion() * 2.0) + 3.0;
    defG += (m_gazda.getNivelStadion() * 2.0) + 3.0;

    // simulam meciul in 10 segmente de joc (faze de poarta)
    for (int i = 0; i < 10; ++i) {
        // batalia de la mijloc (cine are posesia in aceasta zona a terenului)
        if (calculeazaSansa(midG, midO))// sansa de a crea o ocazie (atacul gazdei se dueleaza apararea oaspetilor)
            {
            // gazda are posesia si ataca
            if (calculeazaSansa(atacG, defO*1.20))// daca atacul trece de aparare se ajunge la 1 vs 1 intre atacant si portar
                {
                m_scorGazda++;
            }
        } else {
            // oaspetele are posesia si ataca
            if (calculeazaSansa(atacO, defG*1.20)) {
                m_scorOaspete++;
            }
        }
    }
    if (m_scorGazda > m_scorOaspete) {
        m_gazda.adaugaRezultatMeci(3, 10);  // pt victorie: +3 pct, +10 puncte upgrade/moral
        m_oaspete.adaugaRezultatMeci(0, -5); // pt infrangere: 0 pct, -5 moral
    } else if (m_scorGazda < m_scorOaspete) {
        m_oaspete.adaugaRezultatMeci(3, 10);
        m_gazda.adaugaRezultatMeci(0, -5);
    } else {
        m_gazda.adaugaRezultatMeci(1, 2);   //pt egal: +1 pct, +2 puncte upgrade
        m_oaspete.adaugaRezultatMeci(1, 2);
    }

    m_simulat = true;
}
std::string Meci::toString() const {

    return fmt::format("{:<20} {:>2} - {:<2} {:>20}",
                       m_gazda.getNume(),
                       m_scorGazda,
                       m_scorOaspete,
                       m_oaspete.getNume());
}

    std::ostream& operator<<(std::ostream& os, const Meci& m) {
        os  << m.m_gazda.getNume()
            << " [" << m.m_scorGazda
            << " - "
            << m.m_scorOaspete << "] "
            << m.m_oaspete.getNume();
        return os;
    }
