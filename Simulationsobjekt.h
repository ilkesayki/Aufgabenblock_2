/*
 * Simulationsobjekt.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>
#include <iostream>
#include <iomanip>

class Simulationsobjekt {
private:
    static int p_iMaxID; // Static Variable (number increases with every new vehicle)

protected:
    const int p_iID; //vehicle id's cannot change
    std::string p_sName;
    double p_dZeit; // local time for each vehicle

public:
    Simulationsobjekt(std::string name);
    virtual ~Simulationsobjekt();


    Simulationsobjekt(const Simulationsobjekt&) = delete; //No copying. To avoid confusion.



    // Assignment operator
    Simulationsobjekt& operator=(const Simulationsobjekt& other); //copys only name not the ID

    // Getters
    const std::string& getName() const { return p_sName; }
    int getID() const { return p_iID; }
    double getZeit() const { return p_dZeit; }

    // Pure Virtual Func
    virtual void vSimulieren() = 0; //create objects derived from it (PKW, Fahrrad, Weg, Kreuzung)

    virtual void vAusgeben(std::ostream& o) const;
    virtual void vEinlesen(std::istream& i);

    bool operator==(const Simulationsobjekt& other) const;
};


std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& so);

#endif /* SIMULATIONSOBJEKT_H_ */
