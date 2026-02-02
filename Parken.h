/*
 * Parken.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken : public Verhalten {
private:
    double p_dStartzeit; //When to start!

public:
    Parken(Weg& weg, double startzeit); //Call by Reference &
    virtual ~Parken() {}

    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
    //Distance = Speed × Time (Exception: Streckenende)
};

#endif /* PARKEN_H_ */
