/*
 * Fahrzeug.h
 *
 *  Created on: Nov 3, 2025
 *      Author: ilkesayki
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <iostream>
#include <string>
#include <iomanip>

// Global time declaration (Needed for synchronization across the system).
extern double dGlobaleZeit;

class Fahrzeug {
private:
    static int p_iMaxID; // Static counter for unique ID generation.

protected: // <--- ID and Name moved to protected
    // Stammdaten (Core Data) and members requiring subclass access.
    const int p_iID;	// Unique, constant ID.
    std::string p_sName; // Vehicle Name.

    // Simulation Parameters
    double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke;	// Total distance (km).
    double p_dGesamtZeit;		// Total time (h).
    double p_dZeit;				// Last processed time (for synchronization).

public:
    // Constructors
    Fahrzeug(std::string name = "");
    Fahrzeug(std::string name, double maxGeschwindigkeit);

    // Virtual Destructor (CRITICAL for correct polymorphic memory cleanup).
    virtual ~Fahrzeug();

    // --- Rule of Three/Five Implementation ---
    Fahrzeug(const Fahrzeug&) = delete;			// Copy Constructor DELETED (Enforce single ownership/Smart Pointers).
    Fahrzeug& operator=(const Fahrzeug& other);	// Assignment operator defined (Copies only Name/Stammdaten).

    // Public Getters (Required due to p_iID/p_sName being protected).
    int getID() const { return p_iID; }
    const std::string& getName() const { return p_sName; }

    // Comparison Operator (Based on p_dGesamtStrecke).
    bool operator<(const Fahrzeug& other) const;

    // --- Virtual Methods (Polymorphism) ---
    virtual double dGeschwindigkeit() const;
    virtual void vAusgeben(std::ostream& o) const; // YENİ İMZA
    virtual void vSimulieren();

    // Static Header output function.
    static void vKopf();
};

// Non-member Output Operator (CRITICAL for polymorphic output).
std::ostream& operator<<(std::ostream& o, const Fahrzeug& fzg);

#endif /* FAHRZEUG_H_ */
