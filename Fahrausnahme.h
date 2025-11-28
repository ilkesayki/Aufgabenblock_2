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

// Forward Declaration
class Fahrzeug;
class Weg;

// 1. Ana İstisna Sınıfı (std::exception'dan türetilir)
class Fahrausnahme : public std::exception {
protected:
    Fahrzeug& p_pFahrzeug;
    Weg& p_pWeg;

public:
    Fahrausnahme(Fahrzeug& fzg, Weg& weg) : p_pFahrzeug(fzg), p_pWeg(weg) {}
    virtual ~Fahrausnahme() {} // Sanal destructor

    // Saf sanal fonksiyon: İstisna yakalanınca ne yapılacak?
    virtual void vBearbeiten() const = 0;
};

// 2. Losfahren (Kalkış) İstisnası
class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}
    virtual void vBearbeiten() const override; // Sadece deklarasyon
};

// 3. Streckenende (Yol Sonu) İstisnası
class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}
    virtual void vBearbeiten() const override; // Sadece deklarasyon
};

#endif /* FAHRAUSNAHME_H_ */
