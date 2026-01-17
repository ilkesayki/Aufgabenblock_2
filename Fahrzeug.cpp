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

// Constructor: Base class (Simulationsobjekt) constructor'ını çağırır
Fahrzeug::Fahrzeug(std::string name)
    : Simulationsobjekt(name),
      p_dMaxGeschwindigkeit(0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0),
	  p_dAbschnittStrecke(0.0)

{
    std::cout << "--> Erzeuge Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Constructor: Hız parametreli
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

// Simülasyon Fonksiyonu
void Fahrzeug::vSimulieren() {
    if (p_dZeit >= dGlobaleZeit) return;

    double dZeitIntervall = dGlobaleZeit - p_dZeit;
    double dStrecke = 0.0;

    // --- DÜZELTME BURADA ---
    if (p_pVerhalten) {
        dStrecke = p_pVerhalten->dStrecke(*this, dZeitIntervall);
    } else {
        // Davranış yoksa varsayılan hızla git
        dStrecke = dGeschwindigkeit() * dZeitIntervall;
    }
    // -----------------------

    p_dGesamtStrecke += dStrecke;
    p_dAbschnittStrecke += dStrecke; // Yol yoksa burası da artar, sorun değil
    p_dGesamtZeit += dZeitIntervall;
    p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
    // Varsayılan olarak sürme davranışı atanır
    p_pVerhalten = std::make_unique<Fahren>(weg);
    p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double startzeit) {
    // Park davranışı atanır
    p_pVerhalten = std::make_unique<Parken>(weg, startzeit);
    p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vZeichnen(const Weg& weg) const {
    // Base class için boş, override edilecek.
}

// Yazdırma Fonksiyonu
void Fahrzeug::vAusgeben(std::ostream& o) const {
    // Önce ID ve İsim yazdır (Base class'tan)
    Simulationsobjekt::vAusgeben(o);

    // Sonra Fahrzeug verilerini ekle
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2)
      << std::setw(7) << p_dMaxGeschwindigkeit
      << std::setw(20) << p_dGesamtStrecke
      << std::resetiosflags(std::ios::right);
}

// Hız Fonksiyonu (Eksikti, eklendi)
double Fahrzeug::dGeschwindigkeit() const {
    return p_dMaxGeschwindigkeit;
}

// Karşılaştırma Operatörü (Eksikti, eklendi)
bool Fahrzeug::operator<(const Fahrzeug& other) const {
    return p_dGesamtStrecke < other.p_dGesamtStrecke;
}

// Atama Operatörü (Eksikti, eklendi)
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
    if (this == &other) return *this;

    // Base class'ın atama operatörünü çağır (İsim kopyalamak için)
    Simulationsobjekt::operator=(other);

    // ID kopyalanmaz (const), MaxHız kopyalanabilir ama genelde ID değişmediği için nesne aynı kalır
    // Burada sadece temel bilgileri kopyalıyoruz.

    return *this;
}

// Tablo Başlığı
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
    return 0.0; // Varsayılan araçlar (örn. Bisiklet) benzin almaz.
}
