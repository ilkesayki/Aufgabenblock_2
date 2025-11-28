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

    Fahrrad(std::string name, double maxGeschwindigkeit);
    // derived class destructor/ cuz base class destructor is already virtual
    virtual ~Fahrrad() {}

    //overridden to calculate the speed (speed reduction)
    virtual double dGeschwindigkeit() const override;

    //overridden to output bike data, filling PKW-specific columns with empty space.
    virtual void vAusgeben(std::ostream& o) const override;

    virtual void vZeichnen(const Weg& weg) const override;
};

#endif /* FAHRRAD_H_ */
