#include "Tactica.h"

Tactica::Tactica(std::string nume, std::string descriere):
    m_nume(std::move(nume)),
    m_descriere(std::move(descriere)) {}

void Tactica::afiseaza(std::ostream& os) const {
    os << "Tactica: " << m_nume << ".  " << m_descriere;
    do_afisare(os);
}

TacticaOfensiva::TacticaOfensiva()
    : Tactica("Ofensiv", "Toate liniile imping spre careul advers.") {}

void TacticaOfensiva::do_afisare(std::ostream& os) const {
    os << " [Efect: Focus pe atac]";
}

void TacticaOfensiva::aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const {
    atac *= 1.15;    // +15% Atac
    aparare *= 0.90; // -10% Aparare
    mijloc *= 1.00;
}

std::unique_ptr<Tactica> TacticaOfensiva::clone() const {
    return std::make_unique<TacticaOfensiva>(*this);
}

TacticaDefensiva::TacticaDefensiva()
    : Tactica("Park the Bus", "Aparare pe doua linii, extrem de greu de desfacut.") {}

void TacticaDefensiva::do_afisare(std::ostream& os) const {
    os << " [Efect: Focus pe defensiva]";
}

void TacticaDefensiva::aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const {
    aparare *= 1.20; // +20% Aparare
    atac *= 0.85;    // -15% Atac
    mijloc *= 1.00;
}

std::unique_ptr<Tactica> TacticaDefensiva::clone() const {
    return std::make_unique<TacticaDefensiva>(*this);
}

TacticaEchilibrata::TacticaEchilibrata()
    : Tactica("Echilibrat", "Mentine structura standard si posesia controlata.") {}

void TacticaEchilibrata::do_afisare(std::ostream& os) const {
    os << " [Efect: Controlul jocului]";
}

void TacticaEchilibrata::aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const {
    // nu modifica valorile de baza, e un fel de tactica default
    aparare *= 1.00;
    atac *= 1.00;
    mijloc *= 1.00;
}

std::unique_ptr<Tactica> TacticaEchilibrata::clone() const {
    return std::make_unique<TacticaEchilibrata>(*this);
}


TacticaContraatac::TacticaContraatac()
    : Tactica("Contraatac", "Aparare solida si tranzitie fulgeratoare spre poarta adversa.") {}

void TacticaContraatac::do_afisare(std::ostream& os) const {
    os << " [Efect: Bonus tranzitie]";
}

void TacticaContraatac::aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const {
    aparare *= 1.15; // +15% Aparare
    atac *= 1.10;    // +15% Atac (pe contraatac)
    mijloc *= 0.80;  // -20% Mijloc (se sare peste constructie)
}

std::unique_ptr<Tactica> TacticaContraatac::clone() const {
    return std::make_unique<TacticaContraatac>(*this);
}