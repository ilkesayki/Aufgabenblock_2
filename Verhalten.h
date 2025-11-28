/*
 * Verhalten.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include "Weg.h"

// Forward declaration
class Fahrzeug;

class Verhalten {
protected:
    Weg& p_pWeg; // Davranışın bağlı olduğu yol

public:
    Verhalten(Weg& weg) : p_pWeg(weg) {}
    virtual ~Verhalten() {}

    // Saf sanal fonksiyon: Gidilebilecek mesafeyi hesaplar
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

    Weg& getWeg() const { return p_pWeg; }
};

#endif /* VERHALTEN_H_ */
