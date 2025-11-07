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
    double p_dVerbrauch;	// Fuel consumption rate.
    double p_dTankvolumen;	// Max tank capacity.
    double p_dTankinhalt;	// Current fuel content.

public:
    // Constructor (Initializes base and fuel properties).
    PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen = 55.0);

    // Derived class destructor.
    virtual ~PKW() {}

    // Fueling method (Fills the tank, default fills completely).
    double dTanken(double dMenge = std::numeric_limits<double>::infinity());

    // --- Polymorphic Overrides ---
    // Overridden to include fuel consumption and stopping logic.
    virtual void vSimulieren() override;

    // Overridden to add fuel data to the output.
    virtual void vAusgeben(std::ostream& o) const override;

    // Getter
    double getTankinhalt() const { return p_dTankinhalt; }
};

#endif /* PKW_H_ */
