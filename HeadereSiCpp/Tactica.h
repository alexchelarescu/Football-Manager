#ifndef OOP_TACTICA_H
#define OOP_TACTICA_H

#include <string>
#include <memory>
#include <iostream>

//clasa de baza din care o sa plece derivatele
class Tactica {
protected:
    std::string m_nume;
    std::string m_descriere;

    // Metoda virtuala pentru afisare (part din pattern-ul NVI)
    virtual void do_afisare(std::ostream& os) const = 0;

public:
    Tactica(std::string nume, std::string descriere);
    virtual ~Tactica() = default;

    // Interfata Non-Virtuala (NVI) pentru afisare
    void afiseaza(std::ostream& os) const;

    //aici am metode Virtuale Pure (am crescut complexitatea din derivate)
    virtual void aplicaEfectTactic(double& atac, double& mijloc, double& aparare, int moral, int nivelStadion) const = 0;

    // fiecare tactica gestioneaza diferit evoluția moralului si a resurselor( poate acum se justifica derivatele)
    virtual void aplicaEfectPostMeci(int puncteObtinute, int& moral, int& puncteUpgrade) const = 0;

    [[nodiscard]] virtual std::unique_ptr<Tactica> clone() const = 0;
};

// classele derivate
class TacticaOfensiva : public Tactica {
protected:
    void do_afisare(std::ostream& os) const override;
public:
    TacticaOfensiva();
    void aplicaEfectTactic(double& atac, double& mijloc, double& aparare, int moral, int nivelStadion) const override;
    void aplicaEfectPostMeci(int puncteObtinute, int& moral, int& puncteUpgrade) const override;
    [[nodiscard]] std::unique_ptr<Tactica> clone() const override;
};

class TacticaDefensiva : public Tactica {
protected:
    void do_afisare(std::ostream& os) const override;
public:
    TacticaDefensiva();
    void aplicaEfectTactic(double& atac, double& mijloc, double& aparare, int moral, int nivelStadion) const override;
    void aplicaEfectPostMeci(int puncteObtinute, int& moral, int& puncteUpgrade) const override;
    [[nodiscard]] std::unique_ptr<Tactica> clone() const override;
};

class TacticaEchilibrata : public Tactica {
protected:
    void do_afisare(std::ostream& os) const override;
public:
    TacticaEchilibrata();
    void aplicaEfectTactic(double& atac, double& mijloc, double& aparare, int moral, int nivelStadion) const override;
    void aplicaEfectPostMeci(int puncteObtinute, int& moral, int& puncteUpgrade) const override;
    [[nodiscard]] std::unique_ptr<Tactica> clone() const override;
};

//asta e patra derivata adaugata pentru a indeplini cerinta cu commit ul separat
class TacticaContraatac : public Tactica {
protected:
    void do_afisare(std::ostream& os) const override;
public:
    TacticaContraatac();
    void aplicaEfectTactic(double& atac, double& mijloc, double& aparare, int moral, int nivelStadion) const override;
    void aplicaEfectPostMeci(int puncteObtinute, int& moral, int& puncteUpgrade) const override;
    [[nodiscard]] std::unique_ptr<Tactica> clone() const override;
};

#endif