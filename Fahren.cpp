/*
 * Fahren.cpp
 *
 * Created on: Nov 28, 2025
 * Author: ilkesayki
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrausnahme.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Fahren::Fahren(Weg& weg) : Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {




    double dFahrzeugSpeed = aFzg.dGeschwindigkeit();
    double dWegLimit = p_pWeg.getTempolimit();

    // Choose the required speed
    double dRealSpeed = std::min(dFahrzeugSpeed, dWegLimit);

    // Distance = Speed * Time
    double dMoeglicheStrecke = dRealSpeed * dZeitIntervall;


    double dRestStrecke = p_pWeg.getLaenge() - aFzg.getAbschnittStrecke();

    // Epsilon Comparison
    if (std::abs(dRestStrecke) < 1e-6 || dRestStrecke < 0) {
         throw Streckenende(aFzg, p_pWeg);
    }


    if (dMoeglicheStrecke < dRestStrecke) {
        return dMoeglicheStrecke;
    }

    else {

        throw Streckenende(aFzg, p_pWeg);

        return dRestStrecke;
    }
}
