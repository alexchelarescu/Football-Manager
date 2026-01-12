#include "Echipa.h"
#include "Exceptii.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <limits> //asta e necesar pentru curatarea inputului in functia interactiva

int Echipa::m_nrEchipe = 0;

int Echipa::getNrEchipe() {
    return m_nrEchipe;
}

Echipa::Echipa(std::string nume, std::unique_ptr<Tactica> tacticaInitiala, int obiectiv):
    m_nume(std::move(nume)),
    m_tactica(std::move(tacticaInitiala)),
    m_locObiectiv(obiectiv)
    {
    if (m_nume.empty()) {
        throw EroareDateInvalide("Numele echipei nu poate fi vid.");
    }
    m_nrEchipe++;
}

Echipa::Echipa(const Echipa& alta):
    m_nume(alta.m_nume), m_puncteClasament(alta.m_puncteClasament),
    m_puncteUpgrade(alta.m_puncteUpgrade), m_moral(alta.m_moral),
    m_nivelStadion(alta.m_nivelStadion), m_lot(alta.m_lot),
    m_locObiectiv(alta.m_locObiectiv)
    {
    if (alta.m_tactica)
    {
        m_tactica = alta.m_tactica->clone();
    }
    m_nrEchipe++;
}


Echipa::Echipa(Echipa&& alta) noexcept :
    m_nume(std::move(alta.m_nume)),
    m_puncteClasament(alta.m_puncteClasament),
    m_puncteUpgrade(alta.m_puncteUpgrade),
    m_moral(alta.m_moral),
    m_nivelStadion(alta.m_nivelStadion),
    m_tactica(std::move(alta.m_tactica)),
    m_lot(std::move(alta.m_lot)),
    m_locObiectiv(alta.m_locObiectiv)
{
    m_nrEchipe++;
}

Echipa::~Echipa() {
    m_nrEchipe--;
}

void swap(Echipa& prima, Echipa& aDoua) noexcept{
using std::swap;
    swap(prima.m_nume, aDoua.m_nume);
    swap(prima.m_puncteClasament, aDoua.m_puncteClasament);
    swap(prima.m_puncteUpgrade, aDoua.m_puncteUpgrade);
    swap(prima.m_moral, aDoua.m_moral);
    swap(prima.m_nivelStadion, aDoua.m_nivelStadion);
    swap(prima.m_lot, aDoua.m_lot);
    swap(prima.m_tactica, aDoua.m_tactica);
    swap(prima.m_locObiectiv, aDoua.m_locObiectiv);
    }

Echipa& Echipa::operator=(const Echipa& alta) {
    if (this != &alta) {
        Echipa temp(alta);
        using std::swap;
        swap(*this, temp);
    }
    return *this;
}


Echipa& Echipa::operator=(Echipa&& alta) noexcept {
    if (this != &alta) {
        swap(*this, alta);
    }
    return *this;
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
    if (m_tactica) {
        m_tactica->aplicaEfectPostMeci(puncte, m_moral, m_puncteUpgrade);
    }
}

double Echipa::calculeazaOvrEchipa() const {
    if (m_lot.empty()) return 0.0;
    double suma = 0;
    for (const auto& j : m_lot) { suma += j.getOVR(); }
    return suma / static_cast<double>(m_lot.size());
}

const Jucator& Echipa::gasesteStarulEchipei() const {
    if (m_lot.empty()) throw EroareDateInvalide("Echipa " + m_nume + " nu are jucatori!");
    return *std::ranges::max_element(m_lot.begin(), m_lot.end(), [](const Jucator& a, const Jucator& b) {
        return a.getOVR() < b.getOVR();
    });
}

void Echipa::antreneazaJucator(size_t index) {
    if (index >= m_lot.size()) throw EroareDateInvalide("Index invalid.");

    //aici transform indexul in iterator
    auto it = std::next(m_lot.begin(), static_cast<std::vector<Jucator>::difference_type>(index));
    it->imbunatatesteOVR(1);
}//am ales varianta asta pentru abstractizare, asa cum s-a mentionat ca e cazul sa folosim la lab
 //astfel codul devine independent de tipul containerului


// functie pentru antrenament interactiv
void Echipa::antreneazaJucatorInteractiv() {
    fmt::print("\nSelecteaza jucatorul pentru antrenament:\n");
    for (size_t i = 0; i < m_lot.size(); ++i) {
        fmt::print("{:>2}. {:<25} (OVR {})\n", i + 1, m_lot[i].getNume(), m_lot[i].getOVR());
    }

    int indexJ = -1;
    while (indexJ < 1 || indexJ > static_cast<int>(m_lot.size())) {
        fmt::print("Numar jucator (1-{}): ", m_lot.size());
        if (!(std::cin >> indexJ)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    antreneazaJucator(static_cast<size_t>(indexJ - 1));
    fmt::print("{} a fost antrenat. Noul lui ovr este {}\n", m_lot[static_cast<size_t>(indexJ - 1)].getNume(), m_lot[static_cast<size_t>(indexJ - 1)].getOVR());
}


void Echipa::oferaFeedbackConducere(int pozitieCurenta) const {
    fmt::print(fmt::emphasis::bold, "\n>>> RAPORT CONDUCERE - {} <<<\n", m_nume);
    fmt::print("Obiectiv sezon: Locul {}\n", m_locObiectiv);
    fmt::print("Loc actual:     Locul {}\n", pozitieCurenta);

    if (pozitieCurenta <= m_locObiectiv) {
        fmt::print(fg(fmt::color::green), "Mesaj: Esti un geniu tactic bai baiatule! Sampania e la rece si sefu' a uitat deja ca ne-a taiat primele luna trecuta.\n"
            "       Suntem pe cai mari, nimic nu ne poate opri!!\n");
    } else if (pozitieCurenta - m_locObiectiv == 1|| pozitieCurenta - m_locObiectiv == 2) {
        fmt::print(fg(fmt::color::yellow), "Mesaj: Sefu' zice ca e 'ok', dar stii cum e el...\n"
            "       Ai grija,daca nu castigam etapa viitoare, s-ar putea sa inceapa sa dea declaratii la televizor despre 'schimbari necesare',mers la biserica si alea ale lui...\n");
    } else {
        fmt::print(fg(fmt::color::red), "Mesaj: Aoleu, Mister! E groasa! Seful a inceput sa caute pe Google 'cum se reziliaza un contract fara despagubiri'.\n"
            "       Daca nu castigi etapa viitoare, s-ar putea sa iti gasesti lucrurile intr-o sacosa la poarta stadionului!\n");
    }
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

    if (m_tactica) {
        m_tactica->aplicaEfectTactic(a, m, d, m_moral, m_nivelStadion);
    }
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
    os << "\n" << std::setw(60) << std::setfill('=') << "" << "\n";
    os << "  REZUMAT ECHIPA: " << e.m_nume << "\n";
    os << std::setw(60) << std::setfill('-') << "" << "\n";
    os << "  > OVR ECHIPA:     " << std::fixed << std::setprecision(1) << e.calculeazaOvrEchipa() << "\n";


    if (e.m_lot.empty()) {
        os << "  > Starul echipei: N/A\n";
    } else {
        const Jucator& star = e.gasesteStarulEchipei();
        os << "  > Starul echipei: " << star.getNume() << " (OVR " << star.getOVR() << ")\n";
    }

    //apel afisare virtuala prin NVI
    os << "  > ";
    if (e.m_tactica) e.m_tactica->afiseaza(os);
    os << "\n";

    os << "  > PUNCTE LIGA:    " << e.m_puncteClasament << "\n";
    os << "  > PUNCTE UPGRADE: " << e.m_puncteUpgrade << "\n";
    os << "  > MORAL: " << e.m_moral << "/100\n";
    os << "  > NIVEL STADION:  " << e.m_nivelStadion << "\n";
    os << "  > OBIECTIV SEZON: Locul " << e.m_locObiectiv << "\n";
    os << std::setw(60) << std::setfill('=') << "" << std::setfill(' ') << "\n";
    return os;
}