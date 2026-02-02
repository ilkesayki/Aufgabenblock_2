/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 3, 2025
 *      Author: ilkesayki
 */


#include "Fahrzeug.h"
#include "Fahren.h"
#include "Parken.h"
#include <iostream>
#include <iomanip>

extern double dGlobaleZeit;


Fahrzeug::Fahrzeug(std::string name)
    : Simulationsobjekt(name),
      p_dMaxGeschwindigkeit(0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0),
	  p_dAbschnittStrecke(0.0)

{
    std::cout << "--> Erzeuge Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Constructor: Speed
Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit)
    : Simulationsobjekt(name),
      p_dMaxGeschwindigkeit(maxGeschwindigkeit > 0 ? maxGeschwindigkeit : 0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0),
	  p_dAbschnittStrecke(0.0)
{
    std::cout << "--> Erzeuge Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\" (MaxGeschw.)" << std::endl;
}

Fahrzeug::~Fahrzeug() {
    std::cout << "<-- Loesche Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}


void Fahrzeug::vSimulieren() {
    if (p_dZeit >= dGlobaleZeit) return; //Every Vehicle hold their own time

    double dZeitIntervall = dGlobaleZeit - p_dZeit;
    double dStrecke = 0.0;

    if (p_pVerhalten) { //New
        dStrecke = p_pVerhalten->dStrecke(*this, dZeitIntervall);
    } else { //Old
        dStrecke = dGeschwindigkeit() * dZeitIntervall;
    }
    // -----------------------

    p_dGesamtStrecke += dStrecke;
    p_dAbschnittStrecke += dStrecke;
    p_dGesamtZeit += dZeitIntervall;
    p_dZeit = dGlobaleZeit;
}

//Fahren
void Fahrzeug::vNeueStrecke(Weg& weg) {
    p_pVerhalten = std::make_unique<Fahren>(weg);
    p_dAbschnittStrecke = 0.0;
}

//Parken
void Fahrzeug::vNeueStrecke(Weg& weg, double startzeit) {
    p_pVerhalten = std::make_unique<Parken>(weg, startzeit);
    p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vZeichnen(const Weg& weg) const { //will override

}

void Fahrzeug::vAusgeben(std::ostream& o) const {
    // ID and Name
    Simulationsobjekt::vAusgeben(o);

    // Add specific unterklassen Daten
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2)
      << std::setw(7) << p_dMaxGeschwindigkeit
      << std::setw(20) << p_dGesamtStrecke
      << std::resetiosflags(std::ios::right);
}


double Fahrzeug::dGeschwindigkeit() const {
    return p_dMaxGeschwindigkeit;
}


bool Fahrzeug::operator<(const Fahrzeug& other) const {
    return p_dGesamtStrecke < other.p_dGesamtStrecke;
}


Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
    if (this == &other) return *this;


    Simulationsobjekt::operator=(other);

    return *this;
}


void Fahrzeug::vKopf() {
    std::cout << std::resetiosflags(std::ios::right)
              << std::resetiosflags(std::ios::left);

    std::cout << std::setw(4) << std::left << "ID"
              << std::setw(15) << "Name"
              << std::setw(20) << "MaxGeschwindigkeit"
              << std::setw(15) << "Gesamtstrecke"
              << std::setw(15) << "Verbrauch(L)"
              << std::setw(15) << "Tankinhalt(L)"
              << std::setw(10) << "Akt.Geschw."
              << std::endl;

    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
}

double Fahrzeug::dTanken(double dMenge) {
    return 0.0; //default for Fahrrad
}
