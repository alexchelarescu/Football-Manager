#include "Tactica.h"

Tactica::Tactica(std::string nume, std::string descriere):
    m_nume(std::move(nume)),
    m_descriere(std::move(descriere)) {}

TacticaOfensiva::TacticaOfensiva()
    : Tactica("Ofensiv", "Toate liniile imping spre careul advers.") {}

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

void TacticaEchilibrata::aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const {
    // nu modifica valorile de baza, e un fel de tactica default
    aparare *= 1.00;
    atac *= 1.00;
    mijloc *= 1.00;
}

std::unique_ptr<Tactica> TacticaEchilibrata::clone() const {
    return std::make_unique<TacticaEchilibrata>(*this);
}