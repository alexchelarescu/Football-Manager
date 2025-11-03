#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // pentru rand()
#include "Echipa.h"

class Meci {
private:
    Echipa& m_echipaGazda;
    Echipa& m_echipaOaspete;
    int m_scorGazda;
    int m_scorOaspete;
    bool m_simulat;

    // returneaza true daca "roll"-ul de zar este mai mic decat sansa
    static bool calculeazaSansa(double ratingGazda, double ratingOaspete) {
        if (ratingGazda <= 0 && ratingOaspete <= 0) return false; // evit impartirea la zero
        double sansa = ratingGazda / (ratingGazda + ratingOaspete);

        // factor de noroc: un numar intre 0.0 si 1.0
        double roll = static_cast<double>(rand()) / RAND_MAX;

        return roll < sansa;
    }

public:
    Meci(Echipa& gazda, Echipa& oaspete)
        : m_echipaGazda(gazda),
          m_echipaOaspete(oaspete),
          m_scorGazda(0),
          m_scorOaspete(0),
          m_simulat(false) {}


    void simuleaza() {
        if (m_simulat) {
            std::cout << "Acest meci a fost deja simulat.\n";
            return;
        }

        std::cout << "\n *MECI SIMULAT* \n";
        std::cout << m_echipaGazda.getNume() << " (Gazda) vs. " << m_echipaOaspete.getNume() << " (Oaspete)\n";

        // rating-urile de baza
        double atacGazda = m_echipaGazda.getRatingAtac();
        double midGazda = m_echipaGazda.getRatingMijloc();
        double defGazda = m_echipaGazda.getRatingAparare();
        double portarGazda = m_echipaGazda.getRatingPortar();

        double atacOaspete = m_echipaOaspete.getRatingAtac();
        double midOaspete = m_echipaOaspete.getRatingMijloc();
        double defOaspete = m_echipaOaspete.getRatingAparare();
        double portarOaspete = m_echipaOaspete.getRatingPortar();

        // bonusurile de moral si stadion
        double bonusGazda = (m_echipaGazda.getMoral() * 0.05) + m_echipaGazda.getNivelStadion(); // moralul conteaza 5%, stadionul adauga puncte ovr
        double bonusOaspete = (m_echipaOaspete.getMoral() * 0.05);

        atacGazda += bonusGazda;
        midGazda += bonusGazda;
        defGazda += bonusGazda;
        portarGazda += bonusGazda;

        atacOaspete += bonusOaspete;
        midOaspete += bonusOaspete;
        defOaspete += bonusOaspete;
        portarOaspete += bonusOaspete;

        // simulez meciul in 15 segmente (15 faze de gol/meci)
        for (int i = 0; i < 15; ++i) {

            // batalia de la mijloc (cine are posesia in aceasta zona a terenului)
            if (calculeazaSansa(midGazda, midOaspete)) {
                // gazda ataca
                if (calculeazaSansa(atacGazda, defOaspete)) // sansa de a crea o ocazie (atacul gazdei se dueleaza apararea oaspetilor)
                    {
                    // daca atacul trece de aparare se ajunge la 1 vs 1 intre atacant si portar
                    if (calculeazaSansa(atacGazda, portarOaspete)) {
                        m_scorGazda++;
                    }
                }
            } else {
                // oaspetele ataca
                if (calculeazaSansa(atacOaspete, defGazda))
                {
                    if (calculeazaSansa(atacOaspete, portarGazda * 1.2))
                        {
                        m_scorOaspete++;
                    }
                }
            }
        }

        std::cout << "SCOR FINAL: " << m_scorGazda << " - " << m_scorOaspete << "\n";

        // dupa meci actualizez echipele( le dau punctele din clasament si pct de upgrade)
        if (m_scorGazda > m_scorOaspete) {
            m_echipaGazda.adaugaRezultatMeci(3, 5);
            m_echipaOaspete.adaugaRezultatMeci(0, 1);
        } else if (m_scorGazda < m_scorOaspete) {
            m_echipaGazda.adaugaRezultatMeci(0, 1);
            m_echipaOaspete.adaugaRezultatMeci(3, 5);
        } else {
            m_echipaGazda.adaugaRezultatMeci(1, 2);
            m_echipaOaspete.adaugaRezultatMeci(1, 2);
        }

        this->m_simulat = true;
    }

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Meci& m) {
        os << "Meci: " << m.m_echipaGazda.getNume() << " vs " << m.m_echipaOaspete.getNume(); //aici imi trebuie getteri pentru ca sunt atribute din echipa la care nu am acces
        if (m.m_simulat)
            {
            os << " (Scor: " << m.m_scorGazda << " - " << m.m_scorOaspete << ")";
        } else {
            os << " Nejucat... ";
        }
        return os;
    }
};