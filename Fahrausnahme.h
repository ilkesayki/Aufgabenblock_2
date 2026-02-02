/*
 * Fahrausnahme.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include <string>
#include <iostream>


class Fahrzeug;
class Weg;


class Fahrausnahme : public std::exception {
protected:
    Fahrzeug& p_pFahrzeug;
    Weg& p_pWeg;

public:
    Fahrausnahme(Fahrzeug& fzg, Weg& weg) : p_pFahrzeug(fzg), p_pWeg(weg) {}
    virtual ~Fahrausnahme() {}


    virtual void vBearbeiten() const = 0; //Error catcher calls
};

//Exceptions
class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}
    virtual void vBearbeiten() const override;
};

//Exceptions
class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}
    virtual void vBearbeiten() const override;
};

#endif /* FAHRAUSNAHME_H_ */
