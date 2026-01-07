#ifndef OOP_ECHIPA_H
#define OOP_ECHIPA_H

#include <vector>
#include <string>
#include <memory>
#include "Jucator.h"
#include "Tactica.h"

class Echipa {
private:
    static int m_nrEchipe;
    std::string m_nume;
    int m_puncteClasament{0}, m_puncteUpgrade{20}, m_moral{50}, m_nivelStadion{0};
    std::unique_ptr<Tactica> m_tactica;
    std::vector<Jucator> m_lot;
    int m_locObiectiv;

public:
    Echipa(const Echipa& alta);
    Echipa(Echipa&& alta) noexcept;
    Echipa& operator=(const Echipa& alta);
    Echipa& operator=(Echipa&& alta) noexcept;
    ~Echipa();


    friend void swap(Echipa& prima, Echipa& aDoua) noexcept;

    static int getNrEchipe();

    void adaugaJucator(const Jucator& j);
    void schimbaTactica(std::unique_ptr<Tactica> nouaTactica);
    void upgradeStadion();
    void adaugaRezultatMeci(int puncte, int bonus);
    void pregatesteRatingMeci(double& a, double& m, double& d, double& p) const;
    void afiseazaLotDetaliat() const;
    void antreneazaJucator(size_t index);
    void antreneazaJucatorInteractiv();
    Echipa(std::string nume, std::unique_ptr<Tactica> tacticaInitiala, int obiectiv);
    void oferaFeedbackConducere(int pozitieCurenta) const;

    //[[nodiscard]] int getObiectiv() const { return m_locObiectiv; }
    [[nodiscard]] double calculeazaOvrEchipa() const;
    [[nodiscard]] const Jucator& gasesteStarulEchipei() const;

    [[nodiscard]] const Tactica* getTacticaPtr() const { return m_tactica.get(); }
    [[nodiscard]] const std::string& getNume() const { return m_nume; }
    [[nodiscard]] int getPuncteClasament() const { return m_puncteClasament; }
    [[nodiscard]] int getMoral() const { return m_moral; }
    [[nodiscard]] int getNivelStadion() const { return m_nivelStadion; }

    friend std::ostream& operator<<(std::ostream& os, const Echipa& e);
};
#endif