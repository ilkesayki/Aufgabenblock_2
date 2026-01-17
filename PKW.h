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

    PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen = 55.0);

    // derived class destructor!!! avoid memory leak
    virtual ~PKW() {}

    // Fueling method dMenge = infinity
    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;


    //overridden for fuel consumption and stopping logic when empty
    virtual void vSimulieren() override;

    //overridden to add fuel data to the output
    virtual void vAusgeben(std::ostream& o) const override;

    //getter
    double getTankinhalt() const { return p_dTankinhalt; }

    virtual void vZeichnen(const Weg& weg) const override;
};

#endif /* PKW_H_ */
