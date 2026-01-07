#include "Tactica.h"
#include <algorithm>

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

void TacticaOfensiva::aplicaEfectTactic(double& atac, double&mijloc, double& aparare, int moral, int) const {
    // daca moralul e mare, atacul e mult mai periculos
    double factorMoral = (moral > 75) ? 1.30 : 1.10;
    atac *= factorMoral;
    aparare *= 0.85;
    mijloc *= 1.00;

    //cu schimbarea asta scade si monotonia mentionata in feedback, trebuie sa fii atent la moral dupa fiecare etapa
    // daca nu alegi tactica corecta, mai mult rau faci decat daca ai lasa pe default
}

void TacticaOfensiva::aplicaEfectPostMeci(int puncte, int& moral, int& upgrade) const {
    if (puncte == 3) {
        moral = std::min(100, moral + 15); // victoriile ofensive dau un boost urias
        upgrade += 5; // spectacolul atrage spectatori deci se primesc mai multe puncte de upgrade pt stadion
    } else if (puncte == 0) {
        moral = std::max(0, moral - 10); // infrangerile ofensive lovesc mai tare moralul echipei
    }
    else if (puncte == 1) {
        moral = std::max(0, moral - 2);
    }
}

std::unique_ptr<Tactica> TacticaOfensiva::clone() const {
    return std::make_unique<TacticaOfensiva>(*this);
}


TacticaDefensiva::TacticaDefensiva()
    : Tactica("Park the Bus", "Aparare pe doua linii, extrem de greu de desfacut.") {}

void TacticaDefensiva::do_afisare(std::ostream& os) const {
    os << " [Efect: Focus pe defensiva]";
}

void TacticaDefensiva::aplicaEfectTactic(double& atac, double&mijloc, double& aparare, int, int stadion) const {
    // un stadion mai mare inseamna o organizare defensiva mai buna ajutata de presiunea fanilor pe adversari
    double bonusStadion = 1.0 + (stadion * 0.07);
    aparare *= bonusStadion;
    atac *= 0.85;
    mijloc *= 1.00;
    //daca uiti sa dai upgrade la stadion, nu primesti niciun bonus la aparare, scade si atacul deci mai mult dauneaza

}

void TacticaDefensiva::aplicaEfectPostMeci(int puncte, int& moral, int& upgrade) const {
    if (puncte == 3) {
        moral = std::min(100, moral + 8);
        upgrade += 4;
    }
    else if (puncte == 1) {
        moral = std::min(100, moral + 4);
        upgrade += 2;
    }
    else if (puncte == 0) {
        moral = std::max(0, moral - 1);
    }
}

std::unique_ptr<Tactica> TacticaDefensiva::clone() const {
    return std::make_unique<TacticaDefensiva>(*this);
}


TacticaEchilibrata::TacticaEchilibrata()
    : Tactica("Echilibrat", "Mentine structura standard si posesia controlata.") {}

void TacticaEchilibrata::do_afisare(std::ostream& os) const {
    os << " [Efect: Controlul jocului la mijlocul terenului]";
}

void TacticaEchilibrata::aplicaEfectTactic(double&atac, double&mijloc, double&aparare, int, int) const {
    aparare *= 0.95;
    atac *= 0.95;
    mijloc *= 1.15;
}
//ramane constant, deci nu risti nimic dar si rewardul e mic

void TacticaEchilibrata::aplicaEfectPostMeci(int puncte, int& moral, int&) const {
    if (puncte == 3) moral = std::min(100, moral + 10);
    else if (puncte == 1) moral = std::max(0, moral + 5);
    else if (puncte == 0) moral = std::max(0, moral - 3);
}

std::unique_ptr<Tactica> TacticaEchilibrata::clone() const {
    return std::make_unique<TacticaEchilibrata>(*this);
}

TacticaContraatac::TacticaContraatac()
    : Tactica("Contraatac", "Aparare solida si tranzitie fulgeratoare.") {}

void TacticaContraatac::do_afisare(std::ostream& os) const {
    os << " [Efect: Eficiență în tranziție]";
}

void TacticaContraatac::aplicaEfectTactic(double& atac, double& mijloc, double& aparare, int moral, int) const {
    if (moral > 50) atac *= 1.25;
    else atac *= 1.10;
    mijloc *= 0.75;
    if (moral>30) aparare *= 1.25;
    else aparare*=1.10;
}
//e riscanta dar si reward ul e super mare

void TacticaContraatac::aplicaEfectPostMeci(int puncte, int& moral, int& upgrade) const {
    if (puncte == 3) {
        upgrade += 15; // victoriile prin contraatac sunt considerate "masterclass"
        moral = std::min(100, moral + 15);
    }
    else if (puncte == 1) {
        moral = std::min(100, moral + 4);
        upgrade += 2;
    }
    else if (puncte == 0) {
        moral = std::max(0, moral - 5);
    }
}


std::unique_ptr<Tactica> TacticaContraatac::clone() const {
    return std::make_unique<TacticaContraatac>(*this);
}