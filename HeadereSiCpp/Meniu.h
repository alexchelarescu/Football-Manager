#ifndef OOP_MENIU_H
#define OOP_MENIU_H
#include "Liga.h"

class Meniu {
private:
    static void curataInput();

    static void afiseazaTutorial();

public:
    Meniu() = default;

    static void run();
};

#endif