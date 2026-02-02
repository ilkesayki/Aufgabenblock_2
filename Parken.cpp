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

extern double dGlobaleZeit; //use it from the main.cpp

Parken::Parken(Weg& weg, double startzeit)
    : Verhalten(weg), p_dStartzeit(startzeit) //Welche Weg und Wann muss starten
{}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {


    if (dGlobaleZeit < p_dStartzeit) { //Still in Park
        return 0.0;
    } else {
        throw Losfahren(aFzg, p_pWeg); //State Change Parken -> Fahren
        return 0.0;
    }
}


