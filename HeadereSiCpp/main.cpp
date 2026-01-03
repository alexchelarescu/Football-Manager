#include <iostream>
#include "Meniu.h"
#include "Exceptii.h"

int main() {
    try {
        Meniu joc;
        joc.run();
    } catch (const ManagerEroare& e) {
        std::cerr << "\n[EROARE JOC] " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n[EROARE CRITICA] " << e.what() << "\n";
        return 1;
    }
    return 0;
}