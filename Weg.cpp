/*
 * Weg.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */


#include "Weg.h"
#include "Fahrzeug.h"
#include "Parken.h"
#include "Fahrausnahme.h"
#include <limits>

Weg::Weg(std::string name, double laenge, Tempolimit limit)
    : Simulationsobjekt(name),
      p_dLaenge(laenge),
      p_eTempolimit(limit)
{
}

Weg::~Weg() {}

void Weg::vSimulieren() {
    p_pFahrzeuge.vAktualisieren(); //update list

    for (auto& fzg : p_pFahrzeuge) {
        if (fzg == nullptr) continue; //Security check

        try {
            fzg->vSimulieren();
            fzg->vZeichnen(*this);
        }
        catch (const Fahrausnahme& e) {
            e.vBearbeiten(); //Prevent error and fix
        }
    }
    p_dZeit = dGlobaleZeit;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit) {
    fzg->vNeueStrecke(*this, startzeit); //Parken cuz with starttime
    p_pFahrzeuge.push_front(std::move(fzg));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg) {
    fzg->vNeueStrecke(*this); // Fahren
    p_pFahrzeuge.push_back(std::move(fzg)); //ownership moved
}

void Weg::vAusgeben(std::ostream& o) const {
    Simulationsobjekt::vAusgeben(o);

    o << ": " << std::setw(8) << std::fixed << std::setprecision(2) << p_dLaenge
      << " ( ";

    for (const auto& fzg : p_pFahrzeuge) {
        if (fzg == nullptr) continue;
        o << fzg->getName() << " ";
    }
    o << ")";
}

void Weg::vKopf() {
    std::cout << std::setw(4) << "ID"
              << std::setw(15) << "Name"
              << std::setw(10) << "Laenge"
              << "Fahrzeuge" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

double Weg::getTempolimit() const {
    return static_cast<double>(p_eTempolimit);
}

void Weg::vZeichnen() const {
    for (const auto& fzg : p_pFahrzeuge) {
        if (fzg == nullptr) continue;
        fzg->vZeichnen(*this); //print one by one
    }
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fzg) {

    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) { //it -> iterator

        if (*it == nullptr) continue; //*it -> unique_ptr<Fahrzeug>

        if (**it == fzg) {	//**it -> Fahrzeug

            std::unique_ptr<Fahrzeug> temp = std::move(*it);
            p_pFahrzeuge.erase(it);
            return temp; // give his new owner (z.B. Krezung)
        }
    }
    return nullptr;
}
