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
    std::cout << echipaMea << "\n"; // Ar trebui sa vedem moral crescut, puncte adaugate

    std::cout <<"\n";
    std::cout << " Simulam o INFRANGERE (0 puncte, +1 upgrade) " << "\n";
    echipaMea.adaugaRezultatMeci(0, 1);
    // Acum avem 5+1 = 6 puncte upgrade. Moralul ar trebui să scadă.
    std::cout << echipaMea << "\n";

    // Testare 'upgradeazaStadion' (ar trebui să esueze)
    std::cout <<"\n";
    std::cout << " Incercare UPGRADE STADION (Cost Nivel 2 = 10) " << "\n";
    echipaMea.upgradeazaStadion(); // Avem 6 puncte, costul e 10. Va esua.

    std::cout <<"\n";
    std::cout << " Incercare REFACE MORALUL (Cost = 5) " << "\n";
    echipaMea.refaceMoralul(); // Avem 6 puncte, costul e 5. Va reuși.
    std::cout << echipaMea << "\n"; // Ar trebui să avem 1 punct upgrade rămas

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

    echipaCopie.adaugaRezultatMeci(3, 100); // Adăugăm 100 puncte upgrade Copiei

    std::cout << "   Originala: " << echipaMea.getNume() << " | Puncte UPG: " << echipaMea.getPuncteUpgrade() << "\n";
    std::cout << "   Copia:     " << echipaCopie.getNume() << " | Puncte UPG: " << echipaCopie.getPuncteUpgrade() << "\n";
    std::cout << "   (Diferenta de puncte demonstreaza o copie corecta\n";

    std::cout <<"\n";
    std::cout << " 7.2 Test OPERATOR DE ATRIBUIRE (echipaAtribuita = echipaMea) " <<"\n";
    Echipa echipaAtribuita("Echipa Initiala", 99); // O echipă complet diferită
    std::cout << "   Inainte : " << echipaAtribuita << "\n";

    echipaAtribuita = echipaMea; // Apelează Echipa& operator=(const Echipa& alta)

    std::cout << "   Dupa : " << echipaAtribuita << "\n";
    return 0;
}
