/*
 * PKW.h
 *
 *  Created on: Nov 5, 2025
 *      Author: ilkesayki
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"
#include <limits>
#include <iostream>

class PKW : public Fahrzeug {
private:
    double p_dVerbrauch;
    double p_dTankvolumen;
    double p_dTankinhalt;

public:
    // Kurucu
    PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen = 55.0);

    virtual ~PKW() {}

    // Tank fonksiyonu
    double dTanken(double dMenge = std::numeric_limits<double>::infinity());

    // Sanal metotları override etme (4.4.1'e uygun olarak ostream imzası)
    virtual void vSimulieren() override;
    virtual void vAusgeben(std::ostream& o) const override;

    // Getter (Gereklilik 4.3.2)
    double getTankinhalt() const { return p_dTankinhalt; }
};

#endif /* PKW_H_ */
