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
    double p_dStartzeit; // Ne zaman hareket edecek?

public:
    Parken(Weg& weg, double startzeit);
    virtual ~Parken() {}

    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif /* PARKEN_H_ */
