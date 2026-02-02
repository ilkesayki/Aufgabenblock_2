/*
 * Verhalten.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include "Weg.h"

//Forward declaration
class Fahrzeug;

class Verhalten {
protected:
    Weg& p_pWeg; //must always be on a road (Parken und Fahren)
    //can never be NULL

public:
    Verhalten(Weg& weg) : p_pWeg(weg) {}
    virtual ~Verhalten() {}

    //Mesure the distance
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

    Weg& getWeg() const { return p_pWeg; }
};

#endif /* VERHALTEN_H_ */
