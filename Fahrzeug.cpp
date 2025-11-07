/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 3, 2025
 *      Author: ilkesayki
 */

#include "Fahrzeug.h"
#include <iostream>
#include <string>
#include <iomanip>

// External declaration of the global simulation time.
extern double dGlobaleZeit;

// Global static counter definition. This ensures p_iMaxID is initialized once.
int Fahrzeug::p_iMaxID = 0;

// Default/Name Constructor (4.2.3)
Fahrzeug::Fahrzeug(std::string name)
// Initialization List: CRITICAL for const p_iID assignment (RAII).
    : p_iID(++p_iMaxID),
      p_sName(name),
      p_dMaxGeschwindigkeit(0.0), // Initialize all simulation data to zero.
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0),
      p_dZeit(0.0)
{
	// Output upon creation (Debugging/Observation).
    std::cout << "--> Erzeuge Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Speed Constructor (4.2.5)
Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit)
    : p_iID(++p_iMaxID),
      p_sName(name),
	  // Ternary operator ensures speed is non-negative (Input validation).
      p_dMaxGeschwindigkeit(maxGeschwindigkeit > 0.0 ? maxGeschwindigkeit : 0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0),
      p_dZeit(0.0)
{
    std::cout << "--> Erzeuge Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\" (MaxGeschw. Konstruktor)" << std::endl;
}

// Virtual Destructor (4.3.1)
Fahrzeug::~Fahrzeug() {
    std::cout << "<-- Lösche Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Static Header Function (4.2.6)
void Fahrzeug::vKopf() {
	// Sets up required formatting (width, alignment) for the output table.
    std::cout << std::resetiosflags(std::ios::right)
              << std::resetiosflags(std::ios::left);

    // Outputs the column titles.
    std::cout << std::setw(4) << std::left << "ID"
              << std::setw(15) << "Name"
              << std::setw(20) << "MaxGeschwindigkeit"
              << std::setw(15) << "Gesamtstrecke"
              << std::setw(15) << "Verbrauch(L)"
              << std::setw(15) << "Tankinhalt(L)"
              << std::setw(10) << "Akt.Geschw."
              << std::endl;

    // Outputs a separator line.
    std::cout << std::setw(4) << std::setfill('-') << ""
              << std::setw(15) << ""
              << std::setw(20) << ""
              << std::setw(15) << ""
              << std::setw(15) << ""
              << std::setw(15) << ""
              << std::setw(10) << ""
              << std::setfill(' ')
              << std::endl;
}

// Virtual Output Function (4.4.1)
void Fahrzeug::vAusgeben(std::ostream& o) const { // <-- Takes ostream& for operator<<
    o << std::setiosflags(std::ios::left);

    // ID and Name (Left alignment)
    o << std::setw(4) << p_iID
      << std::setw(15) << p_sName;

    // Set numeric formatting (Right alignment, fixed precision)
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    // Max Speed and Total Distance (Common Data)
    o << std::setw(7) << p_dMaxGeschwindigkeit // Adjusted width to 20 for better alignment (matches vKopf)
      << std::setw(20) << p_dGesamtStrecke;	// Alt classes start their output immediately after this point
/*
    //Blankspaces
    o << std::setw(5) << "" // Tüketim için
      << std::setw(10) << "" // Tank İçeriği için
      << std::setw(10) << ""; // Anlık Hız için
*/
    // Resets formatting flags.
    o << std::resetiosflags(std::ios::left)
      << std::resetiosflags(std::ios::right)
      << std::setprecision(0);
}

// Speed Function (4.3.3)
double Fahrzeug::dGeschwindigkeit() const {
	// Default implementation: returns the constant max speed.
	// Overridden in Fahrrad for dynamic speed calculation.
    return p_dMaxGeschwindigkeit;
}

// Simulation Step Function (4.2.8)
void Fahrzeug::vSimulieren() {
	// CRITICAL: Checks if the vehicle was already processed in the current global timestep.
    if (p_dZeit >= dGlobaleZeit) {
        return;
    }

    double dZeitIntervall = dGlobaleZeit - p_dZeit;

    // Calls dGeschwindigkeit() (Polymorphism: will call Fahrrad's specific speed if needed).
    double dStreckeIntervall = dGeschwindigkeit() * dZeitIntervall;

    // Updates simulation state variables.
    p_dGesamtStrecke += dStreckeIntervall;
    p_dGesamtZeit += dZeitIntervall;
    p_dZeit = dGlobaleZeit; // Synchronization: Vehicle's last processed time equals global time.
}

// ----------------------------------------------------------------------
// OPERATÖR AŞIRI YÜKLEME (4.4)
// ----------------------------------------------------------------------

// Assignment Operator (4.4.5)
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
    if (this == &other) {
        return *this;
    }

    // Only copies 'Stammdaten' (Name). ID (p_iID) is const and cannot be assigned.
    this->p_sName = other.p_sName;

    // Simulation data (distance, time, speed) is intentionally NOT copied.
    return *this;
}

// Output Operator (4.4.2)
std::ostream& operator<<(std::ostream& o, const Fahrzeug& fzg) {
	// CRITICAL: Uses the virtual vAusgeben() method to achieve Polymorphism.
    fzg.vAusgeben(o);
    return o;
}

// Comparison Operator (4.4.4)
bool Fahrzeug::operator<(const Fahrzeug& other) const {
	// Compares based on the total distance traveled (p_dGesamtStrecke).
    return p_dGesamtStrecke < other.p_dGesamtStrecke;
}
