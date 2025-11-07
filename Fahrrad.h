/*
 * Fahrrad.h
 *
 *  Created on: Nov 5, 2025
 *      Author: ilkesayki
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
	// Constructor (Calls base class constructor).
    Fahrrad(std::string name, double maxGeschwindigkeit);
    // Derived class destructor. Base class destructor is already virtual.
    virtual ~Fahrrad() {}

    // --- Polymorphic Overrides ---

    // Overridden to calculate the speed based on accumulated distance (speed reduction logic).
    virtual double dGeschwindigkeit() const override;

    // Overridden to output bike data, filling PKW-specific columns with empty space.
    virtual void vAusgeben(std::ostream& o) const override;
};

#endif /* FAHRRAD_H_ */
