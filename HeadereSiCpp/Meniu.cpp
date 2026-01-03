#include "Meniu.h"
#include "Exceptii.h"
#include "Tactica.h"
#include <iostream>
#include <limits>
#include <fmt/core.h>
#include <fmt/color.h>

Meniu::Meniu() : m_superliga("Incarcare..."), m_echipaMea(nullptr) {}

void Meniu::curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Meniu::afiseazaTutorial() {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "\n{:=^70}\n", " MANUALUL MANAGERULUI: Top Ballers ");
    fmt::print(fg(fmt::color::cyan), "\n1. CONFIGURARE SI SELECTIE\n");
    fmt::print("   - Jocul incarca automat 16 echipe si loturile lor din fisierul json.\n");
    fmt::print(fg(fmt::color::cyan), "\n2. STATISTICI SI DETALIILE ECHIPEI\n");
    fmt::print("   - Rezumatul afiseaza OVR-ul mediu al lotului.\n");
    fmt::print(fg(fmt::color::cyan), "\n3. SIMULAREA ETAPEI\n");
    fmt::print("   - Rezultatele tuturor meciurilor din etapa sunt afisate imediat dupa simulare.\n");
    fmt::print(fg(fmt::color::cyan), "\n4. ANTRENAMENTE\n");
    fmt::print("   - Dupa etapa, poti alege: 1. Antrenament sau 2. Omitere.\n");
    fmt::print(fg(fmt::color::cyan), "\n5. STADION SI TACTICA\n");
    fmt::print("   - Stadionul creste sansele acasa; tactica ofera buff/nerf compartimentelor.\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "\n{:=^70}\n", " SUCCES IN NOUL SEZON, MISTER :) ");
}

void Meniu::selecteazaEchipa() {
    size_t nrEchipe = m_superliga.getNumarEchipe();
    if (nrEchipe == 0) throw EroareDateInvalide("fisierul nu contine echipe.");

    m_superliga.afiseazaListaEchipe();

    int alegereEchipa = -1;
    while (alegereEchipa < 1 || alegereEchipa > static_cast<int>(nrEchipe)) {
        fmt::print("\nNumar echipa (1-{}): ", nrEchipe);
        if (!(std::cin >> alegereEchipa)) { curataInput(); continue; }
    }

    m_echipaMea = &m_superliga.getEchipaDupaIndex(static_cast<size_t>(alegereEchipa - 1));
    fmt::print(fg(fmt::color::cyan), "\nEsti managerul echipei {}\n", m_echipaMea->getNume());
}

bool Meniu::proceseazaOptiune(int optiune) {
    switch (optiune) {
        case 1: std::cout << "\n" << *m_echipaMea << "\n"; break;
        case 2: {
            fmt::print("\n1. Ofensiv | 2. Defensiv | 3. Echilibrat | 4. Contraatac\n");
            int t; std::cin >> t;
            if (t == 1) m_echipaMea->schimbaTactica(std::make_unique<TacticaOfensiva>());
            else if (t == 2) m_echipaMea->schimbaTactica(std::make_unique<TacticaDefensiva>());
            else if (t == 3) m_echipaMea->schimbaTactica(std::make_unique<TacticaEchilibrata>());
            else if (t == 4) m_echipaMea->schimbaTactica(std::make_unique<TacticaContraatac>());
            break;
        }
        case 3:
            try { m_echipaMea->upgradeStadion(); fmt::print("Stadion modernizat!\n"); }
            catch (const ManagerEroare& e) { fmt::print(fg(fmt::color::red), "{}\n", e.what()); }
            break;
        case 4: {
            if (m_superliga.esteSezonIncheiat()) {
                fmt::print(fg(fmt::color::orange), "\n[INFO] Sezonul s-a incheiat deja!\n");
                break;
            }
            m_superliga.simuleazaEtapaCompleta();
            int optAntrenament = -1;
            fmt::print(fmt::emphasis::bold | fg(fmt::color::plum), "\n* ANTRENAMENT  *\n");
            fmt::print("1. Antreneaza jucator (+1 OVR)\n2. Omite antrenament (Continua)\nAlegere: ");
            if (!(std::cin >> optAntrenament)) curataInput();
            else if (optAntrenament == 1) m_echipaMea->antreneazaJucatorInteractiv();
            break;
        }
        case 5: m_superliga.afiseazaClasamentComplet(); break;
        case 6: m_echipaMea->afiseazaLotDetaliat(); break;
        case 7: afiseazaTutorial(); break;
        case 0: return false;
        default: fmt::print(fg(fmt::color::red), "Optiune invalida.\n");
    }
    return true;
}

void Meniu::run() {
    fmt::print(fg(fmt::color::spring_green), "Top Ballers - Initializare...\n");
    m_superliga.incarcaDinJSON("league_config.json", "echipe.json");

    fmt::print(fg(fmt::color::cyan), "\nSistemul a detectat {} echipe incarcate cu succes.\n", Echipa::getNrEchipe());

    afiseazaTutorial();
    selecteazaEchipa();

    int optiune = -1;
    while (true) {
        fmt::print(fmt::emphasis::bold | fg(fmt::color::sky_blue), "\n--- MENIU PRINCIPAL: {} ---\n", m_echipaMea->getNume());
        fmt::print("1. Statistici | 2. Tactica | 3. Upgrade | 4. Simuleaza Etapa | 5. Clasament | 6. LOT | 7. Tutorial | 0. Iesire\nAlegere: ");
        if (!(std::cin >> optiune)) { curataInput(); continue; }
        if (!proceseazaOptiune(optiune)) break;
    }
}