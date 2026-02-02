/*
 * Kreuzung.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <list>
#include <memory>
#include <string>

// Forward declaration
class Weg;
class Fahrzeug;

class Kreuzung : public Simulationsobjekt {
private:
    std::list<std::shared_ptr<Weg>> p_pWege; // List of Straßen connected to Krezung
    double p_dTankstelle;

public:
    Kreuzung(std::string name, double tankstelle = 0.0);
    virtual ~Kreuzung();

    // Connects two Krezungen with eachother
    static void vVerbinde(std::shared_ptr<Kreuzung> k1, std::shared_ptr<Kreuzung> k2,
                          std::string nameHin, std::string nameRueck,
                          double laenge, bool bUeberholverbot = true,
                          Tempolimit limit = Tempolimit::Autobahn);


    void vTanken(Fahrzeug& fzg);


    void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit);


    virtual void vSimulieren() override;

    //Select random straße
    std::shared_ptr<Weg> pZufaelligerWeg(std::weak_ptr<Weg> ankunftsweg);


    double getTankstelle() const { return p_dTankstelle; }
};

#endif /* KREUZUNG_H_ */
