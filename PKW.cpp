#include "PKW.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

extern double dGlobaleZeit;

// Kurucu
PKW::PKW(std::string name, double maxGeschwindigkeit, double verbrauch, double tankvolumen)
    : Fahrzeug(name, maxGeschwindigkeit),
      p_dVerbrauch(verbrauch),
      p_dTankvolumen(tankvolumen),
      p_dTankinhalt(tankvolumen / 2.0)
{
    // p_iID ve p_sName artık protected olduğu için erişim sorunları çözüldü
    std::cout << "--> Erzeuge PKW: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// dTanken Fonksiyonu
double PKW::dTanken(double dMenge) {
    double dMaxFuellmenge = p_dTankvolumen - p_dTankinhalt;
    double dTatsaechlicheMenge;

    if (dMenge == std::numeric_limits<double>::infinity()) {
        dTatsaechlicheMenge = dMaxFuellmenge;
    } else {
        dTatsaechlicheMenge = std::min(dMenge, dMaxFuellmenge);
    }

    if (dTatsaechlicheMenge > 0) {
        // YAZIM YANLIŞI DÜZELTİLDİ: dTatsaechlicheMenge
        p_dTankinhalt += dTatsaechlicheMenge;
        return dTatsaechlicheMenge;
    }
    return 0.0;
}

// vSimulieren Fonksiyonu (İmza Uyuşmazlığı Düzeltildi)
void PKW::vSimulieren() {
    if (p_dZeit >= dGlobaleZeit) {
        return;
    }

    double dZeitIntervall = dGlobaleZeit - p_dZeit;
    double dStrecke = dGeschwindigkeit() * dZeitIntervall;
    double dVerbrauchStrecke = dStrecke * p_dVerbrauch / 100.0;

    // Tank kontrolü
    if (p_dTankinhalt > 0.0) {
        double dMaxStreckeMitTank = p_dTankinhalt * 100.0 / p_dVerbrauch;

        if (dStrecke > dMaxStreckeMitTank) {
            dStrecke = dMaxStreckeMitTank;
            dVerbrauchStrecke = p_dTankinhalt;
        }

        p_dGesamtStrecke += dStrecke;
        p_dGesamtZeit += dZeitIntervall;
        p_dZeit = dGlobaleZeit;

        p_dTankinhalt -= dVerbrauchStrecke;
        if (p_dTankinhalt < 0.0) {
            p_dTankinhalt = 0.0;
        }

    } else {
        p_dZeit = dGlobaleZeit;
    }
}


// vAusgeben Fonksiyonu (İmza Uyuşmazlığı Düzeltildi: ostream& parametresi alır)
void PKW::vAusgeben(std::ostream& o) const {
    // 1. Önce temel sınıf verilerini çıkar
    Fahrzeug::vAusgeben(o);

    // 2. PKW'ye özgü verileri ekle
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    double dGesamtVerbrauch = p_dGesamtStrecke * p_dVerbrauch / 100.0;

    // Tüketim, Tank İçeriği ve Anlık Hız sütunlarını doldur
    o << std::setw(15) << dGesamtVerbrauch
      << std::setw(15) << p_dTankinhalt
      << std::setw(10) << dGeschwindigkeit();

    o << std::resetiosflags(std::ios::right) << std::setprecision(0);
}
