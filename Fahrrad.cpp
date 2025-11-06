#include "Fahrrad.h"
#include <iostream>
#include <cmath> // std::pow için
#include <algorithm> // std::max için
#include <iomanip> // Çıktı formatı için

// Kurucu
Fahrrad::Fahrrad(std::string name, double maxGeschwindigkeit)
    : Fahrzeug(name, maxGeschwindigkeit)
{
    std::cout << "--> Erzeuge Fahrrad: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// dGeschwindigkeit() Fonksiyonu (Hız azalması)
double Fahrrad::dGeschwindigkeit() const {
    int iAbnahmeSchritte = static_cast<int>(p_dGesamtStrecke / 20.0);
    double dAbnahmeFaktor = std::pow(0.9, iAbnahmeSchritte);
    double dAktuelleGeschw = p_dMaxGeschwindigkeit * dAbnahmeFaktor;

    // Minimum hız kontrolü: 12 km/saat
    return std::max(dAktuelleGeschw, 12.0);
}

// vAusgeben() Fonksiyonu (4.4.1: ostream& parametresi alır ve override)
void Fahrrad::vAusgeben(std::ostream& o) const {
    // Önce temel sınıf verilerini çıkar (ID, Name, MaxGeschw, Gesamtstrecke)
    Fahrzeug::vAusgeben(o);

    // Bisiklet için PKW'ye ait sütunları doldurmak için boşluk bırak
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    // Tüketim, Tank İçeriği ve Anlık Hız sütunlarını doldur
    o << std::setw(15) << "" // Tüketim (Yok)
      << std::setw(15) << "" // Tank İçeriği (Yok)
      << std::setw(10) << dGeschwindigkeit(); // Anlık Hız

    o << std::resetiosflags(std::ios::right) << std::setprecision(0);
}
