/*
 * Fahrrad.cpp
 *
 *  Created on: Nov 5, 2025
 *      Author: ilkesayki
 */

#include "Fahrrad.h"
#include "SimuClient.h"
#include "Weg.h"
#include <iostream>
#include <cmath> // std::pow
#include <algorithm> // std::max
#include <iomanip> //for output formatting


Fahrrad::Fahrrad(std::string name, double maxGeschwindigkeit)

    : Fahrzeug(name, maxGeschwindigkeit)
{
	//can access to ID and Name cuz they are in protected
    std::cout << "--> Erzeuge Fahrrad: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

//speed calculation function (dGeschwindigkeit)
double Fahrrad::dGeschwindigkeit() const {

    int iAbnahmeSchritte = static_cast<int>(p_dGesamtStrecke / 20.0); //gives n


    double dAbnahmeFaktor = std::pow(0.9, iAbnahmeSchritte); //0.9^n

    //currentspeed * 0.9^n = newspeed
    double dAktuelleGeschw = p_dMaxGeschwindigkeit * dAbnahmeFaktor;

    //ensures the speed never falls below 12.0.
    return std::max(dAktuelleGeschw, 12.0);
}

void Fahrrad::vZeichnen(const Weg& weg) const {
    // bZeichneFahrrad(Simülasyon ismi, Yol ismi, Göreceli Konum, Hız)
    double dRelPos = p_dAbschnittStrecke / weg.getLaenge();
    bZeichneFahrrad(p_sName, weg.getName(), dRelPos, dGeschwindigkeit());
}

//output function (vAusgeben)
void Fahrrad::vAusgeben(std::ostream& o) const {
	////base class outputs (ID, Name, MaxSpeed, TotalDistance)
    Fahrzeug::vAusgeben(o);

    //adds Fahrrad-specific data
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    //empty cuz we dont have those values
    o << std::setw(15) << "" // Empty
      << std::setw(15) << "" // Empty
      << std::setw(15) << dGeschwindigkeit();

    o << std::resetiosflags(std::ios::right) << std::setprecision(0);
}
