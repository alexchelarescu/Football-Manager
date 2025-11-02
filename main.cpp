#include <iostream>
#include <string>
#include "Header/Jucator.h"
#include "Header/Echipa.h"
#include <iomanip>

int main() {

    std::cout <<"TESTARE PROVIZORIE (Jucator + Echipa)\n\n";
    std::cout << " 1. Creare Jucatori " << "\n";
    Jucator p1("A. Tatarusanu", 35, PozitieJucator::PORTAR, 78);
    Jucator f1("V. Chiriches", 32, PozitieJucator::FUNDAS, 75);
    Jucator f2("S. Radu", 34, PozitieJucator::FUNDAS, 76);
    Jucator m1("N. Stanciu", 28, PozitieJucator::MIJLOCAS, 80);
    Jucator m2("R. Marin", 25, PozitieJucator::MIJLOCAS, 77);
    Jucator a1("G. Puscas", 26, PozitieJucator::ATACANT, 74);

    std::cout << p1 << "\n";
    std::cout << m1 << "\n";
    std::cout << "\n";



    std::cout << " 2. Creare Echipa " << "\n";
    Echipa echipaMea("Baller FC", 4);

    std::cout << " 3. Adaugare Jucatori in Echipa " << "\n";
    echipaMea.adaugaJucator(p1);
    echipaMea.adaugaJucator(f1);
    echipaMea.adaugaJucator(f2);
    echipaMea.adaugaJucator(m1);
    echipaMea.adaugaJucator(m2);
    echipaMea.adaugaJucator(a1);

    std::cout <<"\n";
    std::cout << " 4. Stare Initiala Echipa " << "\n";
    std::cout << echipaMea << "\n";


    std::cout <<"\n";
    std::cout << " Testare afiseazaLot() " << "\n";;
    echipaMea.afiseazaLot();

    std::cout <<"\n";
    std::cout << " 5. Simulare Evenimente Sezon " <<  "\n";

    std::cout <<"\n";
    std::cout << " Simulam o VICTOIRE (3 puncte, +5 upgrade) " << "\n";
    echipaMea.adaugaRezultatMeci(3, 5);

    echipaMea.gestioneazaAntrenament();

    std::cout << "\nStarea echipei dupa antrenament:\n" << echipaMea << "\n";

    std::cout <<"\n";
    std::cout << " Simulam o INFRANGERE (0 puncte, +1 upgrade) " << "\n";
    echipaMea.adaugaRezultatMeci(0, 1);

    std::cout << "\nStarea echipei dupa al doilea antrenament:\n" << echipaMea << "\n";


    // testare upgrade stadion (ar trebui sa esueze ca nu am destule puncte upgrade)
    std::cout <<"\n";
    std::cout << " Incercare UPGRADE STADION (Cost Nivel 2 = 10) " << "\n";
    echipaMea.upgradeazaStadion();

    std::cout <<"\n";
    std::cout << " Incercare REFACE MORALUL (Cost = 5) " << "\n";
    echipaMea.refaceMoralul(); // Are 6 puncte si costul e 5, deci va reusi.
    std::cout << echipaMea << "\n"; // Ar trebui sa avem 1 punct upgrade ramas

    std::cout << "Puncte upgrade ramase: " << echipaMea.getPuncteUpgrade() <<"\n";

    std::cout <<"\n";
    std::cout << " 6. Testare verificaObiectiv() " << "\n";
    int pozitieCurenta = 3;
    std::cout << "Obiectivul echipei este: Locul " << echipaMea.getObiectiv() << "\n";
    std::cout << "Pozitia curenta simulata: " << pozitieCurenta <<"\n";
    if (echipaMea.verificaObiectiv(pozitieCurenta)) {
        std::cout << "REZULTAT: Obiectiv indeplinit! (Pozitia <= Obiectiv)\n";
    } else {
        std::cout << "REZULTAT: Obiectiv ratat! (Pozitia > Obiectiv)\n";
    }

    std::cout <<"\n\n";
    std::cout << " 7. TESTARE CERINTA #3 (Regula celor Trei) " << "\n";

    std::cout << "\n> 7.1 Test CONSTRUCTOR DE COPIERE (Echipa copie = echipaMea)" << "\n";
    Echipa echipaCopie = echipaMea;


    std::cout << "   Antrenam DOAR copia... (va cere input)\n";
    echipaCopie.gestioneazaAntrenament();

    std::cout << "   Originala: " << echipaMea.getNume() << " | OVR: " << echipaMea.getOVR() << "\n";
    std::cout << "   Copia:     " << echipaCopie.getNume() << " | OVR: " << echipaCopie.getOVR() << "\n";
    std::cout << "   (Diferenta de OVR demonstreaza o copie corecta)\n";

    std::cout <<"\n";
    std::cout << " 7.2 Test OPERATOR DE ATRIBUIRE (echipaAtribuita = echipaMea) " <<"\n";
    Echipa echipaAtribuita("Echipa Initiala", 99); // O echipa complet diferita
    std::cout << "   Inainte : " << echipaAtribuita << "\n";

    echipaAtribuita = echipaMea; // Apeleaza Echipa& operator=(const Echipa& alta)

    std::cout << "   Dupa : " << echipaAtribuita << "\n";
    return 0;
}