/*
 * Simulationsobjekt.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */


#include "Simulationsobjekt.h"

//Start ID Counter
int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt(std::string name)
    : p_iID(++p_iMaxID), // First increase, then add (1, 2, 3...)
      p_sName(name),
      p_dZeit(0.0) // Local Timer
{
    std::cout << "--> Erzeuge Simulationsobjekt: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

Simulationsobjekt::~Simulationsobjekt() {
    std::cout << "<-- Loesche Simulationsobjekt: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream& o) const {
    o << std::setiosflags(std::ios::left)
      << std::setw(4) << p_iID
      << std::setw(15) << p_sName
      << std::resetiosflags(std::ios::left);
}

//assignment operator
Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& other) {
    if (this == &other) return *this;
    this->p_sName = other.p_sName;
    // ID and Zeit cannot copied
    return *this;
}
//comparison operator
bool Simulationsobjekt::operator==(const Simulationsobjekt& other) const {
    return this->p_iID == other.p_iID;
}

//ausgabe operator -> Ausgeben func -> Pkw ausgeben
std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& so) {
    so.vAusgeben(o);
    return o;
}


void Simulationsobjekt::vEinlesen(std::istream& i) {
    if (p_sName == "") {
        i >> p_sName;
    }
}
