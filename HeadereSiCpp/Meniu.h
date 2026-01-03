#ifndef OOP_MENIU_H
#define OOP_MENIU_H

#include "Liga.h"
#include <memory>

class Meniu {
private:
    Liga m_superliga;
    Echipa* m_echipaMea;

    static void curataInput();

    static void afiseazaTutorial();
    void selecteazaEchipa();
    bool proceseazaOptiune(int optiune);

public:
    Meniu();
    void run();
};

#endif