/*
 * Fahrzeug.h
 *
 *  Created on: Nov 3, 2025
 *      Author: ilkesayki
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"
#include "Verhalten.h"
#include "Weg.h"
#include <memory>
#include <limits>

extern double dGlobaleZeit;

class Fahrzeug : public Simulationsobjekt {  //Fahrzeug is now a Simulatiınsobjekt (Inheritance)
protected:
    double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke;
    double p_dGesamtZeit;
    std::unique_ptr<Verhalten> p_pVerhalten; //Polymorphism to hold new Fahren and new Parken
    double p_dAbschnittStrecke;

public:
    Fahrzeug(std::string name = "");
    Fahrzeug(std::string name, double maxGeschwindigkeit);
    virtual ~Fahrzeug();


    Fahrzeug(const Fahrzeug&) = delete;
    Fahrzeug& operator=(const Fahrzeug& other);

    virtual void vSimulieren() override;
    virtual void vAusgeben(std::ostream& o) const override;
    virtual double dGeschwindigkeit() const;

    bool operator<(const Fahrzeug& other) const;

    static void vKopf();

    void vNeueStrecke(Weg& weg); //Fahren Verhalten
    void vNeueStrecke(Weg& weg, double startzeit); //Parken Verhalten
    double getAbschnittStrecke() const { return p_dAbschnittStrecke; }

    virtual void vZeichnen(const Weg& weg) const;

    //virtual so that we can use it both for Fahrrad (return 0.0) and Pkw
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
};
#endif /* FAHRZEUG_H_ */
