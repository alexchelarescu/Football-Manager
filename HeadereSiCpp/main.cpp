#include <iostream>
#include <limits>
#include <memory>
#include <fmt/core.h>
#include <fmt/color.h>
#include "Liga.h"
#include "Exceptii.h"
#include "Tactica.h"

void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void afiseazaTutorial() {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "\n{:=^70}\n", " MANUALUL MANAGERULUI: Top Ballers ");

    fmt::print(fg(fmt::color::cyan), "\n1. CONFIGURARE SI SELECTIE\n");
    fmt::print("   - Jocul incarca automat 16 echipe si loturile lor din fisierul json.\n");
    fmt::print("   - Poti prelua orice echipa la inceputul sezonului.\n");

    fmt::print(fg(fmt::color::cyan), "\n2. STATISTICI SI DETALIILE ECHIPEI\n");
    fmt::print("   - Rezumatul afiseaza OVR-ul mediu al lotului.\n");
    fmt::print("   - 'Starul echipei' este jucatorul cu cel mai mare OVR actual.\n");

    fmt::print(fg(fmt::color::cyan), "\n3. SIMULAREA ETAPEI\n");
    fmt::print("   - Rezultatele tuturor meciurilor din etapa sunt afisate imediat dupa simulare.\n");

    fmt::print(fg(fmt::color::cyan), "\n4. ANTRENAMENTE\n");
    fmt::print("   - Dupa etapa, poti alege: 1. Antrenament sau 2. Omitere.\n");
    fmt::print(" - Introducerea oricarei alte taste va declansa un mesaj de 'Optiune invalida'.\n");
    fmt::print(" - Antrenamentul ofera un bonus permanent de +1 OVR unui jucator ales.\n");
    fmt::print(" - Omiterea antrenamentului nu ofera niciun beneficiu, ar fi bine sa iti antrenezi jucatorii mereu.\n");

    fmt::print(fg(fmt::color::cyan), "\n5. STADION SI TACTICA\n");
    fmt::print("   - Stadionul creste sansele acasa; tactica ofera buff/nerf compartimentelor.\n");

    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "\n{:=^70}\n", " SUCCES IN NOUL SEZON, MISTER :) ");
}

int main() {
    try {
        Liga superliga("Incarcare...");
        fmt::print(fg(fmt::color::spring_green), "Top Ballers - Initializare...\n");
        superliga.incarcaDinJSON("league_config.json", "echipe.json");

        size_t nrEchipe = superliga.getNumarEchipe();
        if (nrEchipe == 0) throw EroareDateInvalide("fisierul nu contine echipe.");

        afiseazaTutorial();

        fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "\n* SELECTEAZA ECHIPA  *\n");
        for (size_t i = 0; i < nrEchipe; ++i) {
            fmt::print("{:>2}. {}\n", i + 1, superliga.getEchipaDupaIndex(i).getNume());
        }

        int alegereEchipa = -1;
        while (alegereEchipa < 1 || alegereEchipa > static_cast<int>(nrEchipe)) {
            fmt::print("\nNumar echipa (1-{}): ", nrEchipe);
            if (!(std::cin >> alegereEchipa)) { curataInput(); continue; }
        }

        Echipa& echipaMea = superliga.getEchipaDupaIndex(static_cast<size_t>(alegereEchipa - 1));
        fmt::print(fg(fmt::color::cyan), "\nEsti managerul echipei {}\n", echipaMea.getNume());

        int optiune = -1;
        while (optiune != 0) {
            fmt::print(fmt::emphasis::bold | fg(fmt::color::sky_blue), "\n--- MENIU PRINCIPAL: {} ---\n", echipaMea.getNume());
            fmt::print("1. Statistici | 2. Tactica | 3. Upgrade | 4. Simuleaza Etapa | 5. Clasament | 6. LOT | 7. Tutorial | 0. Iesire\n");
            fmt::print("Alegere: ");

            if (!(std::cin >> optiune)) { curataInput(); continue; }

            switch (optiune) {
                case 1: std::cout << "\n" << echipaMea << "\n"; break;
                case 2: {
                    fmt::print("\n1. Ofensiv | 2. Defensiv | 3. Echilibrat\n");
                    int t; std::cin >> t;
                    if (t == 1) echipaMea.schimbaTactica(std::make_unique<TacticaOfensiva>());
                    else if (t == 2) echipaMea.schimbaTactica(std::make_unique<TacticaDefensiva>());
                    else echipaMea.schimbaTactica(std::make_unique<TacticaEchilibrata>());
                    break;
                }
                case 3:
                    try { echipaMea.upgradeStadion(); fmt::print("Stadion modernizat!\n"); }
                    catch (const std::exception& e) { fmt::print(fg(fmt::color::red), "{}\n", e.what()); }
                    break;

                case 4: {
                    // verific starea sezonului inainte de orice actiune
                    //am avut un bug in care puteam antrena jucatorii la infinit chiar daca se terminase sezonul
                    if (superliga.esteSezonIncheiat()) {
                        fmt::print(fg(fmt::color::orange), "\n[INFO] Sezonul s-a incheiat deja! Nu mai poti simula meciuri sau antrena jucatori.\n");
                        break;
                    }

                    superliga.simuleazaEtapaCompleta();

                    int optAntrenament = -1;
                    bool decizieLuata = false;

                    while (!decizieLuata) {
                        fmt::print(fmt::emphasis::bold | fg(fmt::color::plum), "\n* ANTRENAMENT  *\n");
                        fmt::print("1. Antreneaza jucator (+1 OVR)\n");
                        fmt::print("2. Omite antrenament (Continua)\n");
                        fmt::print("Alegere: ");

                        if (!(std::cin >> optAntrenament)) {
                            curataInput();
                            fmt::print(fg(fmt::color::red), "Eroare: Introdu o cifra valida (1 sau 2).\n");
                            continue;
                        }

                        if (optAntrenament == 1) {
                            const auto& lot = echipaMea.getLot();
                            fmt::print("\nSelecteaza jucatorul pentru antrenament:\n");
                            for (size_t i = 0; i < lot.size(); ++i) {
                                fmt::print("{:>2}. {:<25} (OVR {})\n", i + 1, lot[i].getNume(), lot[i].getOVR());
                            }

                            int indexJ = -1;
                            while (indexJ < 1 || indexJ > static_cast<int>(lot.size())) {
                                fmt::print("Numar jucator (1-{}): ", lot.size());
                                if (!(std::cin >> indexJ)) { curataInput(); continue; }
                            }
                            echipaMea.antreneazaJucator(static_cast<size_t>(indexJ - 1));
                            decizieLuata = true;
                        } else if (optAntrenament == 2) {
                            fmt::print("Antrenament omis.\n");
                            decizieLuata = true;
                        } else {
                            fmt::print(fg(fmt::color::red), "Optiune invalida! Alege 1 sau 2.\n");
                        }
                    }
                    break;
                }

                case 5: superliga.afiseazaClasamentComplet(); break;
                case 6: echipaMea.afiseazaLotDetaliat(); break;
                case 7: afiseazaTutorial(); break;
                case 0: fmt::print("Inchidere program...\n"); break;
                default: fmt::print(fg(fmt::color::red), "Optiune invalida.\n");
            }
        }
    } catch (const std::exception& e) {
        fmt::print(fg(fmt::color::crimson), "\n[EROARE CRITICA] {}\n", e.what());
    }
    return 0;
}