#ifndef OOP_MENIU_H
#define OOP_MENIU_H
#include "Liga.h"

class Meniu {
private:
    void curataInput();
    void afiseazaTutorial();

public:
    Meniu() = default;
    void run();
};

#endif