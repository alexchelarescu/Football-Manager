#ifndef OOP_TACTICA_H
#define OOP_TACTICA_H

#include <string>
#include <memory>

//clasa de baza din care o sa plece derivatele
class Tactica {
protected:
    std::string m_nume;
    std::string m_descriere;

public:
    Tactica(std::string nume, std::string descriere);
    virtual ~Tactica() = default;

    //aici am metode Virtuale Pure
    virtual void aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Tactica> clone() const = 0;

    [[nodiscard]] std::string getNumeTactica() const { return m_nume; }
    [[nodiscard]] std::string getDescriereTactica() const { return m_descriere; }
};

// classele derivate
class TacticaOfensiva : public Tactica {
public:
    TacticaOfensiva();
    void aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const override;
    [[nodiscard]] std::unique_ptr<Tactica> clone() const override;
};

class TacticaDefensiva : public Tactica {
public:
    TacticaDefensiva();
    void aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const override;
    [[nodiscard]] std::unique_ptr<Tactica> clone() const override;
};

class TacticaEchilibrata : public Tactica {
public:
    TacticaEchilibrata();
    void aplicaEfectTactic(double& atac, double& mijloc, double& aparare) const override;
    [[nodiscard]] std::unique_ptr<Tactica> clone() const override;
};

#endif