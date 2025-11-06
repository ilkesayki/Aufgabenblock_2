#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
    Fahrrad(std::string name, double maxGeschwindigkeit);
    virtual ~Fahrrad() {}

    // Yalnızca doğru imzayı override et
    virtual double dGeschwindigkeit() const override;
    virtual void vAusgeben(std::ostream& o) const override; // İMZA DÜZELTİLDİ
};

#endif /* FAHRRAD_H_ */
