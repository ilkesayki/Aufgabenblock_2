#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <iostream>
#include <string>
#include <iomanip>

extern double dGlobaleZeit;

class Fahrzeug {
private:
    static int p_iMaxID;

protected: // <--- ID ve Name buraya taşındı!
    const int p_iID;
    std::string p_sName;

    // Simülasyon Değişkenleri
    double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke;
    double p_dGesamtZeit;
    double p_dZeit;

public:
    // Kurucular
    Fahrzeug(std::string name = "");
    Fahrzeug(std::string name, double maxGeschwindigkeit);

    virtual ~Fahrzeug();

    // Kopyalamayı yasakla, Atamayı bildir
    Fahrzeug(const Fahrzeug&) = delete;
    Fahrzeug& operator=(const Fahrzeug& other);

    int getID() const { return p_iID; }
    const std::string& getName() const { return p_sName; }

    // Operatörler
    bool operator<(const Fahrzeug& other) const;

    // Sanal Metotlar
    virtual double dGeschwindigkeit() const;
    virtual void vAusgeben(std::ostream& o) const; // YENİ İMZA
    virtual void vSimulieren();

    static void vKopf();
};

std::ostream& operator<<(std::ostream& o, const Fahrzeug& fzg);

#endif /* FAHRZEUG_H_ */
