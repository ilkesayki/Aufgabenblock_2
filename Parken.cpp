/*
 * Parken.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#include "Parken.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include <iostream>
#include <cmath>

extern double dGlobaleZeit;

Parken::Parken(Weg& weg, double startzeit)
    : Verhalten(weg), p_dStartzeit(startzeit)
{}

// Parken.cpp (Debug hali)
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
    // Debug çıktısı: Her adımda zamanı ve start zamanını görelim
    // std::cout << "DEBUG: Zeit=" << dGlobaleZeit << " Start=" << p_dStartzeit << std::endl;

    if (dGlobaleZeit < p_dStartzeit) {
        return 0.0;
    } else {
        // Buraya girdiğinden emin olalım
        // std::cout << "DEBUG: THROWING LOSFAHREN NOW!" << std::endl;
        throw Losfahren(aFzg, p_pWeg);
        return 0.0;
    }
}


