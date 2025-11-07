#include "Fahrrad.h"
#include <iostream>
#include <cmath> // std::pow
#include <algorithm> // std::max
#include <iomanip> // For output formatting

// Constructor
Fahrrad::Fahrrad(std::string name, double maxGeschwindigkeit)
	// Calls base class constructor via initialization list.
    : Fahrzeug(name, maxGeschwindigkeit)
{
	// Access to inherited 'protected' members p_iID and p_sName.
    std::cout << "--> Erzeuge Fahrrad: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Speed calculation function (dGeschwindigkeit) (4.3.3)
double Fahrrad::dGeschwindigkeit() const {
	// Calculate the number of 20km segments completed (floor value).
    int iAbnahmeSchritte = static_cast<int>(p_dGesamtStrecke / 20.0);

    // Calculate the cumulative reduction factor (0.9 raised to the power of steps).
    // This is mathematically equivalent to reducing the max speed by 10% 'n' times.
    double dAbnahmeFaktor = std::pow(0.9, iAbnahmeSchritte);

    // Calculate the speed after reduction, based on the initial max speed.
    double dAktuelleGeschw = p_dMaxGeschwindigkeit * dAbnahmeFaktor;

    // CRITICAL: Enforce the minimum speed limit (12 km/h).
    // std::max ensures the speed never falls below 12.0.
    return std::max(dAktuelleGeschw, 12.0);
}

// Output function (vAusgeben) (4.4.1 override)
void Fahrrad::vAusgeben(std::ostream& o) const {
	// 1. Call base class output (outputs ID, Name, MaxSpeed, TotalDistance).
    Fahrzeug::vAusgeben(o);

    // 2. Add Bicycle-specific data, filling the columns left by the base class.
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    // Fill the PKW-specific columns with empty strings to maintain table alignment.
    o << std::setw(15) << "" // Consumption (Yok)
      << std::setw(15) << "" // Tank Content (Yok)
	  // Output the actual current speed (Width 15, to match vKopf)
      << std::setw(15) << dGeschwindigkeit(); // Aktuelle Geschw.

    o << std::resetiosflags(std::ios::right) << std::setprecision(0);
}
