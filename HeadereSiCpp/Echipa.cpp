#include "Echipa.h"
#include "Exceptii.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <utility>
#include <algorithm>
#include <iomanip>

Echipa::Echipa(std::string nume, std::unique_ptr<Tactica> tacticaInitiala):
    m_nume(std::move(nume)),
    m_tactica(std::move(tacticaInitiala))
    {
    if (m_nume.empty()) {
        throw EroareDateInvalide("Numele echipei nu poate fi vid.");
    }
}

Echipa::Echipa(const Echipa& alta):
    m_nume(alta.m_nume), m_puncteClasament(alta.m_puncteClasament),
    m_puncteUpgrade(alta.m_puncteUpgrade), m_moral(alta.m_moral),
    m_nivelStadion(alta.m_nivelStadion), m_lot(alta.m_lot)
    {
    if (alta.m_tactica)
    {
        m_tactica = alta.m_tactica->clone();
    }
    }

Echipa& Echipa::operator=(Echipa alta) {
    swap(*this, alta);
    return *this;
}

void swap(Echipa& prima, Echipa& aDoua) noexcept {
    using std::swap;
    swap(prima.m_nume, aDoua.m_nume);
    swap(prima.m_puncteClasament, aDoua.m_puncteClasament);
    swap(prima.m_puncteUpgrade, aDoua.m_puncteUpgrade);
    swap(prima.m_moral, aDoua.m_moral);
    swap(prima.m_nivelStadion, aDoua.m_nivelStadion);
    swap(prima.m_lot, aDoua.m_lot);
    swap(prima.m_tactica, aDoua.m_tactica);
}

void Echipa::adaugaJucator(const Jucator& j) {
    m_lot.push_back(j);
}

void Echipa::schimbaTactica(std::unique_ptr<Tactica> nouaTactica) {
    if (!nouaTactica) {
        throw EroareReguliCompetitie("Tactica furnizata este invalida.");
    }
    m_tactica = std::move(nouaTactica);
}

void Echipa::upgradeStadion() {
    if (m_puncteUpgrade < 50) {
        throw EroareEconomie("Upgrade Stadion", 50);
    }
    m_puncteUpgrade -= 50;
    m_nivelStadion++;
}

void Echipa::adaugaRezultatMeci(int puncte, int bonus) {
    m_puncteClasament += puncte;
    m_puncteUpgrade += bonus;
    if (puncte == 3) { m_moral = std::min(100, m_moral + 5); }
    else if (puncte == 0) { m_moral = std::max(0, m_moral - 5); }
}

double Echipa::calculeazaOvrEchipa() const {
    if (m_lot.empty()) return 0.0;
    double suma = 0;
    for (const auto& j : m_lot) { suma += j.getOVR(); }
    return suma / static_cast<double>(m_lot.size());
}

const Jucator& Echipa::gasesteStarulEchipei() const {
    if (m_lot.empty()) throw std::runtime_error("Echipa nu are jucatori!");
    return *std::ranges::max_element(m_lot.begin(), m_lot.end(), [](const Jucator& a, const Jucator& b) {
        return a.getOVR() < b.getOVR();
    });
}

void Echipa::antreneazaJucator(size_t index) {
    if (index >= m_lot.size()) throw std::out_of_range("Index invalid.");
    m_lot[index].imbunatatesteOVR(1);
}

void Echipa::pregatesteRatingMeci(double& a, double& m, double& d, double& p) const {
    int na = 0, nm = 0, nd = 0;
    a = m = d = p = 0;
    for (const auto& j : m_lot) {
        switch (j.getPozitie()) {
            case PozitieJucator::PORTAR:   p += j.getOVR(); break;
            case PozitieJucator::FUNDAS:   d += j.getOVR(); nd++; break;
            case PozitieJucator::MIJLOCAS: m += j.getOVR(); nm++; break;
            case PozitieJucator::ATACANT:  a += j.getOVR(); na++; break;
        }
    }
    if (na > 0) { a /= na; }
    if (nm > 0) { m /= nm; }
    if (nd > 0) { d /= nd; }
    if (m_tactica) { m_tactica->aplicaEfectTactic(a, m, d); }
    a += (m_moral / 100.0) * 5.0 + m_nivelStadion * 2.0;
    d += m_nivelStadion * 2.0;
}

void Echipa::afiseazaLotDetaliat() const {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "\n{:=^75}\n", fmt::format(" LOT: {} ", m_nume));
    fmt::print("{:<30} {:<15} {:<10} {:<10}\n", "Nume", "Pozitie", "Varsta", "OVR");
    fmt::print("{:-^75}\n", "");
    for (const auto& j : m_lot) {
        std::string pStr;
        switch(j.getPozitie()) {
            case PozitieJucator::PORTAR: pStr = "GK"; break;
            case PozitieJucator::FUNDAS: pStr = "DEF"; break;
            case PozitieJucator::MIJLOCAS: pStr = "MID"; break;
            case PozitieJucator::ATACANT: pStr = "ATT"; break;
        }
        fmt::print("{:<30} {:<15} {:<10} {:<10}\n", j.getNume(), pStr, j.getVarsta(), j.getOVR());
    }
    fmt::print("{:=^75}\n", "");
}

std::ostream& operator<<(std::ostream& os, const Echipa& e) {
    const Jucator& star = e.gasesteStarulEchipei();

    os << "\n" << std::setw(60) << std::setfill('=') << "" << "\n";
    os << "  REZUMAT ECHIPA: " << e.m_nume << "\n";
    os << std::setw(60) << std::setfill('-') << "" << "\n";
    os << "  > OVR ECHIPA:     " << std::fixed << std::setprecision(1) << e.calculeazaOvrEchipa() << "\n";
    os << "  > Starul echipei: " << star.getNume() << " (OVR " << star.getOVR() << ")\n";
    os << "  > Tactica actuala: " << e.m_tactica->getNumeTactica() << "\n";
    os << "  > Stil de joc:    " << e.m_tactica->getDescriereTactica() << "\n";
    os << "  > PUNCTE LIGA:    " << e.m_puncteClasament << "\n";
    os << "  > MORAL: " << e.m_moral << "/100\n";
    os << "  > NIVEL STADION:  " << e.m_nivelStadion << "\n";
    os << std::setw(60) << std::setfill('=') << "" << std::setfill(' ') << "\n";
    return os;
}