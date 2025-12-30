#include "Liga.h"
#include "Meci.h"
#include "Exceptii.h"
#include "Tactica.h"
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <fmt/color.h>

using json = nlohmann::json;

Liga::Liga(std::string nume) : m_numeLiga(std::move(nume)) {}

void Liga::incarcaDinJSON(const std::string& caleConfig, const std::string& caleEchipe) {
    // citire configuratie globala pt liga
    std::ifstream fC(caleConfig);
    if (!fC.is_open()) throw EroareDateInvalide("league_config.json lipseste.");
    json jC; fC >> jC;
    m_numeLiga = jC.value("league_name", "Superliga");

    //aici citesc datele despre echipe
    std::ifstream fE(caleEchipe);
    if (!fE.is_open()) throw EroareDateInvalide("echipe.json lipseste.");
    json jE; fE >> jE;

    for (const auto& item : jE) {
        Echipa echipa(item["nume"], std::make_unique<TacticaEchilibrata>());
        for (const auto& j : item["jucatori"]) {
            echipa.adaugaJucator(Jucator(j["nume"], j["varsta"], stringToPozitie(j["pozitie"]), j["ovr"]));
        }
        m_echipe.push_back(std::move(echipa)) ;
    }
    genereazaCalendar();
}

void Liga::genereazaCalendar()  {
    int n = static_cast<int>(m_echipe.size());
    if (n < 2) return;
    std::vector<int> indici(n);
    for (int i = 0; i < n; ++i) indici[i] = i;

    for (int etapa = 0; etapa < n - 1; ++etapa) {
        std::vector<ProgramMeci> meciuriEtapa;
        for (int i = 0; i < n / 2; ++i) meciuriEtapa.push_back({indici[i], indici[n-1-i]});
        m_calendar.push_back(meciuriEtapa);
        std::rotate(indici.begin() + 1, indici.end() - 1, indici.end());
    }
    // am adaugat returul sezonului prin inversarea gazdelor
    size_t nrTur = m_calendar.size();
    for (size_t i = 0; i < nrTur; ++i) {
        std::vector<ProgramMeci> retur;
        for (const auto& m : m_calendar[i]) retur.push_back({m.indexOaspete, m.indexGazda});
        m_calendar.push_back(retur);
    }
}

void Liga::simuleazaEtapaCompleta() {
    if (m_etapaCurenta >= static_cast<int>(m_calendar.size())) {
        fmt::print(fg(fmt::color::orange), "\n[INFO] Sezon incheiat!\n");
        return;
    }

    fmt::print(fmt::emphasis::bold | fg(fmt::color::white), "\n*  REZULTATE ETAPA {}  *\n", m_etapaCurenta + 1);

    const auto& meciuri = m_calendar[m_etapaCurenta];
    for (size_t i = 0; i < meciuri.size(); ++i) {
        Meci m(m_echipe[meciuri[i].indexGazda], m_echipe[meciuri[i].indexOaspete]);
        m.simuleaza();
        fmt::print("  # {:<2} | {}\n", i + 1, m.toString());
    }
    fmt::print(fg(fmt::color::spring_green), "\nToate meciurile au fost procesate!\n");
    m_etapaCurenta++;
}
bool Liga::esteSezonIncheiat() const {
    return m_etapaCurenta >= static_cast<int>(m_calendar.size());
}

void Liga::afiseazaClasamentComplet() const {
    std::vector<Echipa> clasament = m_echipe;
    std::ranges::sort(clasament, [](const Echipa& a, const Echipa& b) {
        if (a.getPuncteClasament() != b.getPuncteClasament()) return a.getPuncteClasament() > b.getPuncteClasament();
        return a.getMoral() > b.getMoral();
    });

    fmt::print("\n{:<25} {:<10} {:<10}\n", "Echipa", "Puncte", "Stadion");
    fmt::print("{:-^50}\n", "");
    for (const auto& e : clasament) {
        fmt::print("{:<25} {:<10} Lvl {:<10}\n", e.getNume(), e.getPuncteClasament(), e.getNivelStadion());
    }
}

Echipa& Liga::getEchipaDupaIndex(size_t index) { return m_echipe.at(index); }
size_t Liga::getNumarEchipe() const { return m_echipe.size(); }