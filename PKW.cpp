/*
 * PKW.cpp
 *
 *  Created on: Nov 5, 2025
 *      Author: ilkesayki
 */

#include "PKW.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits> // Needed for std::numeric_limits<double>::infinity() in dTanken

extern double dGlobaleZeit;

// Constructor (4.3.2)
PKW::PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen)
    : Fahrzeug(name, maxGeschwindigkeit),
      p_dVerbrauch(verbrauch),
      p_dTankvolumen(tankvolumen),
	  // Initialize tank content to half the capacity.
      p_dTankinhalt(tankvolumen / 2.0)
{
	// Access to p_iID and p_sName is possible because they are 'protected'.
    std::cout << "--> Erzeuge PKW: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Fueling function (dTanken) (4.3.2)
double PKW::dTanken(double dMenge) {
    double dMaxFuellmenge = p_dTankvolumen - p_dTankinhalt;
    double dTatsaechlicheMenge;

    // Check for default value (infinity) to initiate a full tank.
    if (dMenge == std::numeric_limits<double>::infinity()) {
        dTatsaechlicheMenge = dMaxFuellmenge;
    } else {
    	// Fill up either the requested amount or the maximum possible amount.
        dTatsaechlicheMenge = std::min(dMenge, dMaxFuellmenge);
    }

    if (dTatsaechlicheMenge > 0) {
        p_dTankinhalt += dTatsaechlicheMenge;
        return dTatsaechlicheMenge;	// Return the amount actually filled.
    }
    return 0.0;
}

// Simulation function (vSimulieren) (4.3.2)
void PKW::vSimulieren() {
	// Synchronization check (inherited from Fahrzeug).
    if (p_dZeit >= dGlobaleZeit) {
        return;
    }

    double dZeitIntervall = dGlobaleZeit - p_dZeit;
    // CRITICAL: Get current speed (inherited dGeschwindigkeit is max speed for PKW).
    double dStrecke = dGeschwindigkeit() * dZeitIntervall;

    // Calculate fuel consumption required for this distance.
    double dVerbrauchStrecke = dStrecke * p_dVerbrauch / 100.0;

    // Fuel control logic.
    if (p_dTankinhalt > 0.0) {
    	// Calculate maximum distance possible with current fuel.
        double dMaxStreckeMitTank = p_dTankinhalt * 100.0 / p_dVerbrauch;

        // Check if distance exceeds fuel capacity (reserve check).
        if (dStrecke > dMaxStreckeMitTank) {
            dStrecke = dMaxStreckeMitTank;	// Limit distance to remaining fuel.
            dVerbrauchStrecke = p_dTankinhalt;	// Use all remaining fuel.
        }

        // Update state variables (distance and time are inherited).
        p_dGesamtStrecke += dStrecke;
        p_dGesamtZeit += dZeitIntervall;
        p_dZeit = dGlobaleZeit;

        // Apply consumption.
        p_dTankinhalt -= dVerbrauchStrecke;
        if (p_dTankinhalt < 0.0) {
            p_dTankinhalt = 0.0;	// Ensure tank content is non-negative.
        }

    } else {
    	// Vehicle stopped due to empty tank; only synchronize time.
        p_dZeit = dGlobaleZeit;
    }
}


// Output function (vAusgeben) (4.4.1)
void PKW::vAusgeben(std::ostream& o) const {
	// 1. Call base class output (outputs ID, Name, MaxSpeed, TotalDistance).
    Fahrzeug::vAusgeben(o);

    // 2. Add PKW-specific data (continues the table from the position left by the base class).
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    double dGesamtVerbrauch = p_dGesamtStrecke * p_dVerbrauch / 100.0;

    // Fill the remaining columns (Consumption, Tank Content, Current Speed).
    o << std::setw(15) << dGesamtVerbrauch
      << std::setw(15) << p_dTankinhalt
      << std::setw(15) << dGeschwindigkeit();

    o << std::resetiosflags(std::ios::right) << std::setprecision(0);
}
