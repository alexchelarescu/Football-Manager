#include <iostream>
#include <string>
#include "Header/Jucator.h"
#include "Header/Echipa.h"
#include "Header/Meci.h"
#include <iomanip>
#include <ctime>


Echipa creeazaFCSB_25_26() {
    Echipa fcsb("FCSB", 1);

    // Portari
    fcsb.adaugaJucator(Jucator("Stefan Tarnovanu", 25, PozitieJucator::PORTAR, 75));
    fcsb.adaugaJucator(Jucator("Lukas Zima", 31, PozitieJucator::PORTAR, 69));

    // Fundasi
    fcsb.adaugaJucator(Jucator("Siyabonga Ngezana", 28, PozitieJucator::FUNDAS, 72));
    fcsb.adaugaJucator(Jucator("Joyskim Dawa", 29, PozitieJucator::FUNDAS, 70));
    fcsb.adaugaJucator(Jucator("Risto Radunovic", 33, PozitieJucator::FUNDAS, 68));
    fcsb.adaugaJucator(Jucator("David Kiki", 31, PozitieJucator::FUNDAS, 69));
    fcsb.adaugaJucator(Jucator("Alexandru Pantea", 22, PozitieJucator::FUNDAS, 66));

    // Mijlocasi
    fcsb.adaugaJucator(Jucator("Darius Olaru", 27, PozitieJucator::MIJLOCAS, 77));
    fcsb.adaugaJucator(Jucator("Adrian Sut", 26, PozitieJucator::MIJLOCAS, 73));
    fcsb.adaugaJucator(Jucator("Mihai Lixandru", 24, PozitieJucator::MIJLOCAS, 70));
    fcsb.adaugaJucator(Jucator("Baba Alhassan", 25, PozitieJucator::MIJLOCAS, 69));
    fcsb.adaugaJucator(Jucator("Dennis Politic", 25, PozitieJucator::MIJLOCAS, 73));

    // Atacanti
    fcsb.adaugaJucator(Jucator("Florinel Coman", 27, PozitieJucator::ATACANT, 78));
    fcsb.adaugaJucator(Jucator("David Miculescu", 24, PozitieJucator::ATACANT, 70));
    fcsb.adaugaJucator(Jucator("Octavian Popescu", 22, PozitieJucator::ATACANT, 71));

    return fcsb;
}


Echipa creeazaDinamo_25_26() {
    Echipa dinamo("Dinamo Bucuresti", 10);

    // Portari
    dinamo.adaugaJucator(Jucator("Adnan Golubovic", 30, PozitieJucator::PORTAR, 71));
    dinamo.adaugaJucator(Jucator("Dorian Railean", 32, PozitieJucator::PORTAR, 65));

    // Fundasi
    dinamo.adaugaJucator(Jucator("Razvan Patriche", 39, PozitieJucator::FUNDAS, 64));
    dinamo.adaugaJucator(Jucator("Josue Homawoo", 28, PozitieJucator::FUNDAS, 68));
    dinamo.adaugaJucator(Jucator("Costin Amzar", 22, PozitieJucator::FUNDAS, 67));
    dinamo.adaugaJucator(Jucator("Kennedy Boateng", 28, PozitieJucator::FUNDAS, 69));
    dinamo.adaugaJucator(Jucator("Raul Oprut", 27, PozitieJucator::FUNDAS, 66));

    // Mijlocasi
    dinamo.adaugaJucator(Jucator("Domagoj Pavicic", 31, PozitieJucator::MIJLOCAS, 70));
    dinamo.adaugaJucator(Jucator("Eddy Gnahore", 32, PozitieJucator::MIJLOCAS, 69));
    dinamo.adaugaJucator(Jucator("Catalin Cirjan", 22, PozitieJucator::MIJLOCAS, 70));
    dinamo.adaugaJucator(Jucator("Antonio Bordusanu", 21, PozitieJucator::MIJLOCAS, 65));
    dinamo.adaugaJucator(Jucator("Adrian Caragea", 20, PozitieJucator::MIJLOCAS, 64));

    // Atacanti
    dinamo.adaugaJucator(Jucator("Hakim Abdallah", 27, PozitieJucator::ATACANT, 68));
    dinamo.adaugaJucator(Jucator("Astrit Selmani", 28, PozitieJucator::ATACANT, 67));
    dinamo.adaugaJucator(Jucator("Raul Rotund", 20, PozitieJucator::ATACANT, 62));

    return dinamo;
}


int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout <<" *TESTARE* \n\n";


    std::cout << " 1. Creare si Adaugare Jucatori in Echipe " << "\n";
    Echipa fcsb = creeazaFCSB_25_26();
    Echipa dinamo = creeazaDinamo_25_26();
    std::cout << "Echipele FCSB si Dinamo au fost create .\n";

    std::cout <<"\n";
    std::cout << " 2. Stare Initiala Echipe " << "\n";
    std::cout << fcsb << "\n";   // afiseaza sumarul FCSB
    std::cout << dinamo << "\n"; // afiseaza sumarul Dinamo

    // aici testez cum se simuleaza meciul
    std::cout <<"\n";
    std::cout << " 3. Simulare Meci (FCSB e gazda) " <<  "\n";

    Meci derby(fcsb, dinamo); // creez meciul
    derby.simuleaza(); // simulez meciul

    std::cout << "\n Starea echipelor dupa meci: \n";
    std::cout << fcsb << "\n";
    std::cout << dinamo << "\n";

    std::cout <<"\n";
    std::cout << " 4. Simulare Evenimente Sezon (Antrenament post-meci) " <<  "\n";


    // apelul asta va citi primele 4 linii din tastatura.txt
    fcsb.gestioneazaAntrenament();

    std::cout << "\n Starea echipei FCSB dupa antrenament: \n" << fcsb << "\n";

    // testare upgrade stadion (ar trebui sa esueze ca nu am destule puncte upgrade)
    std::cout <<"\n";
    std::cout << " Incercare UPGRADE STADION (Cost Nivel 0 = 0) " << "\n";
    fcsb.upgradeazaStadion();
    std::cout << " Incercare UPGRADE STADION (Cost Nivel 1 = 10) " << "\n";
    fcsb.upgradeazaStadion();

    std::cout <<"\n";
    std::cout << " Incercare REFACE MORALUL (Cost = 5) " << "\n";
    fcsb.refaceMoralul();
    std::cout << fcsb << "\n";

    std::cout << "Puncte upgrade ramase: " << fcsb.getPuncteUpgrade() <<"\n";

    std::cout <<"\n";
    std::cout << " 5. Testare verificaObiectiv() " << "\n";

    int pozitieCurenta = 3;
    std::cout << "Obiectivul echipei este: Locul " << fcsb.getObiectiv() << "\n";
    std::cout << "Pozitia curenta simulata: " << pozitieCurenta <<"\n";
    if (fcsb.verificaObiectiv(pozitieCurenta)) {
        std::cout << "REZULTAT: Obiectiv indeplinit! (Pozitia <= Obiectiv)\n";
    } else {
        std::cout << "REZULTAT: Obiectiv ratat! (Pozitia > Obiectiv)\n";
    }

    std::cout <<"\n\n";

    pozitieCurenta = 1;
    std::cout << "Obiectivul echipei este: Locul " << fcsb.getObiectiv() << "\n";
    std::cout << "Pozitia curenta simulata: " << pozitieCurenta <<"\n";
    if (fcsb.verificaObiectiv(pozitieCurenta)) {
        std::cout << "REZULTAT: Obiectiv indeplinit! (Pozitia <= Obiectiv)\n";
    } else {
        std::cout << "REZULTAT: Obiectiv ratat! (Pozitia > Obiectiv)\n";
    }

    std::cout <<"\n\n";
    std::cout << " 6. TESTARE CERINTA #3 (Regula celor Trei) " << "\n";

    std::cout << "\n> 6.1 Test CONSTRUCTOR DE COPIERE (Echipa copie = fcsb)" << "\n";
    Echipa echipaCopie = fcsb;


    std::cout << "   Antrenam DOAR copia... (va cere input)\n";

    // apelul asta va citi ultimele 4 linii din tastatura.txt
    echipaCopie.gestioneazaAntrenament();

    std::cout << "   Originala: " << fcsb.getNume() << " | OVR: " << fcsb.getOVR() << "\n";
    std::cout << "   Copia:     " << echipaCopie.getNume() << " | OVR: " << echipaCopie.getOVR() << "\n";
    std::cout << "   (Diferenta de OVR demonstreaza o copie corecta)\n";

    std::cout <<"\n";
    std::cout << " 6.2 Test OPERATOR DE ATRIBUIRE (echipaAtribuita = fcsb) " <<"\n";
    Echipa echipaAtribuita("Echipa Initiala", 99); // o echipa complet diferita
    std::cout << "   Inainte : \n " << echipaAtribuita << "\n";

    echipaAtribuita = fcsb; // apeleaza Echipa& operator=(const Echipa& alta)

    std::cout << "   Dupa : \n " << echipaAtribuita << "\n";
    return 0;
}

/*Mentiuni :

    - Momentan ovr-ul e calculat in functie de totalul jucatorilor de pe fiecare pozitie, ceea ce nu e tocmai corect.
O sa modific in momentul in care o sa implementez formatii de joc astfel incat sa calculez ovr-ul din jucatorii care sunt titulari.
    - Simularea meciului duce la rezultate surprinzatoare( FCSB pierde mai mult decat ar trebui in mod normal) deoarece se pleaca de la acelasi
moral, acelasi nivel de stadion iar ovr urile sunt apropiate pt ca nu au existat sesiuni de antrenament. Pe parcursul sezonului input ul
managerului va conta din ce in ce mai mult ca sa faca diferenta in clasament.

*/
