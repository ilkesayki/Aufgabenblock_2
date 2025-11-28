/*
 * PKW.cpp
 *
 *  Created on: Nov 5, 2025
 *      Author: ilkesayki
 */

#include "PKW.h"
#include "SimuClient.h"
#include "Weg.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>

extern double dGlobaleZeit;

PKW::PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen)
    : Fahrzeug(name, maxGeschwindigkeit),
      p_dVerbrauch(verbrauch),
      p_dTankvolumen(tankvolumen),
      p_dTankinhalt(tankvolumen / 2.0)
{
	//can access to ID and Name cuz they are in protected
    std::cout << "--> Erzeuge PKW: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Fueling function (dTanken)
double PKW::dTanken(double dMenge) {
    double dMaxFuellmenge = p_dTankvolumen - p_dTankinhalt;
    double dTatsaechlicheMenge;


    if (dMenge == std::numeric_limits<double>::infinity()) {
        dTatsaechlicheMenge = dMaxFuellmenge;
    } else {
    	//fill up either requested or maximum amount.
        dTatsaechlicheMenge = std::min(dMenge, dMaxFuellmenge);
    }

    if (dTatsaechlicheMenge > 0) {
        p_dTankinhalt += dTatsaechlicheMenge;
        return dTatsaechlicheMenge;	//return the amount
    }
    return 0.0;
}

// Simulation function (vSimulieren)
void PKW::vSimulieren() {
    if (p_dZeit >= dGlobaleZeit) return;

    double dZeitIntervall = dGlobaleZeit - p_dZeit;
    double dStrecke = 0.0;

    // --- DÜZELTME BURADA ---
    // Eğer davranış atanmışsa (Yoldaysa)
    if (p_pVerhalten) {
        dStrecke = p_pVerhalten->dStrecke(*this, dZeitIntervall);
    }
    // Eğer davranış YOKSA (vAufgabe_2 gibi yolsuz sürüşler için)
    else {
        dStrecke = dGeschwindigkeit() * dZeitIntervall;
    }
    // -----------------------

    // Yakıt Hesabı
    double dVerbrauchStrecke = dStrecke * p_dVerbrauch / 100.0;

    if (p_dTankinhalt > 0.0) {
        if (p_dTankinhalt < dVerbrauchStrecke) {
            dStrecke = p_dTankinhalt * 100.0 / p_dVerbrauch;
            p_dTankinhalt = 0.0;
        } else {
            p_dTankinhalt -= dVerbrauchStrecke;
        }
    } else {
        dStrecke = 0.0;
    }

    p_dGesamtStrecke += dStrecke;
    p_dAbschnittStrecke += dStrecke;
    p_dGesamtZeit += dZeitIntervall;
    p_dZeit = dGlobaleZeit;
}

void PKW::vZeichnen(const Weg& weg) const {
    // bZeichnePKW(Simülasyon ismi, Yol ismi, Göreceli Konum, Hız, Yakıt)
    double dRelPos = p_dAbschnittStrecke / weg.getLaenge();
    bZeichnePKW(p_sName, weg.getName(), dRelPos, dGeschwindigkeit(), p_dTankinhalt);
}

// Output function (vAusgeben)
void PKW::vAusgeben(std::ostream& o) const {
	//base class outputs (ID, Name, MaxSpeed, TotalDistance)
    Fahrzeug::vAusgeben(o);

    //adds PKW-specific data
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    double dGesamtVerbrauch = p_dGesamtStrecke * p_dVerbrauch / 100.0;


    o << std::setw(15) << dGesamtVerbrauch
      << std::setw(15) << p_dTankinhalt
      << std::setw(15) << dGeschwindigkeit();

    o << std::resetiosflags(std::ios::right) << std::setprecision(0);
}
