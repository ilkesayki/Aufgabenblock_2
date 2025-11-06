#include "Fahrzeug.h"
#include <iostream>
#include <string>
#include <iomanip>

// Global saatin bildirimi
extern double dGlobaleZeit;

// p_iMaxID'nin global tanımı
int Fahrzeug::p_iMaxID = 0;

// Kurucular (Değişiklik yok)
Fahrzeug::Fahrzeug(std::string name)
    : p_iID(++p_iMaxID),
      p_sName(name),
      p_dMaxGeschwindigkeit(0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0),
      p_dZeit(0.0)
{
    std::cout << "--> Erzeuge Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit)
    : p_iID(++p_iMaxID),
      p_sName(name),
      p_dMaxGeschwindigkeit(maxGeschwindigkeit > 0.0 ? maxGeschwindigkeit : 0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0),
      p_dZeit(0.0)
{
    std::cout << "--> Erzeuge Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\" (MaxGeschw. Konstruktor)" << std::endl;
}

// Sanal Yıkıcı (Değişiklik yok)
Fahrzeug::~Fahrzeug() {
    std::cout << "<-- Lösche Fahrzeug: ID=" << p_iID << ", Name=\"" << p_sName << "\"" << std::endl;
}

// Statik Başlık Fonksiyonu (Değişiklik yok)
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

    std::cout << std::setw(4) << std::setfill('-') << ""
              << std::setw(15) << ""
              << std::setw(20) << ""
              << std::setw(15) << ""
              << std::setw(15) << ""
              << std::setw(15) << ""
              << std::setw(10) << ""
              << std::setfill(' ')
              << std::endl;
}

// Sanal Veri Çıktı Fonksiyonu (4.4.1: ostream& parametresi alır)
void Fahrzeug::vAusgeben(std::ostream& o) const { // <-- İMZA GÜNCELLENDİ
    o << std::setiosflags(std::ios::left);

    // ID ve İsim
    o << std::setw(4) << p_iID
      << std::setw(15) << p_sName;

    // Sayısal değerler
    o << std::setiosflags(std::ios::right)
      << std::fixed << std::setprecision(2);

    // Maksimum Hız ve Toplam Mesafe
    o << std::setw(7) << p_dMaxGeschwindigkeit
      << std::setw(20) << p_dGesamtStrecke;
/*
    // Alt sınıfların kendi verilerini yazması için boş sütunlar
    o << std::setw(5) << "" // Tüketim için
      << std::setw(10) << "" // Tank İçeriği için
      << std::setw(10) << ""; // Anlık Hız için
*/
    o << std::resetiosflags(std::ios::left)
      << std::resetiosflags(std::ios::right)
      << std::setprecision(0);
}

// Hız Fonksiyonu (Değişiklik yok)
double Fahrzeug::dGeschwindigkeit() const {
    return p_dMaxGeschwindigkeit;
}

// Simülasyon Fonksiyonu (Değişiklik yok)
void Fahrzeug::vSimulieren() {
    if (p_dZeit >= dGlobaleZeit) {
        return;
    }

    double dZeitIntervall = dGlobaleZeit - p_dZeit;
    double dStreckeIntervall = dGeschwindigkeit() * dZeitIntervall;

    p_dGesamtStrecke += dStreckeIntervall;
    p_dGesamtZeit += dZeitIntervall;
    p_dZeit = dGlobaleZeit;
}

// ----------------------------------------------------------------------
// OPERATÖR AŞIRI YÜKLEME (4.4)
// ----------------------------------------------------------------------

// Atama Operatörü (4.4.5)
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
    if (this == &other) {
        return *this;
    }

    // Stammdaten'i kopyala (sadece isim)
    this->p_sName = other.p_sName;

    // ID bir const olduğu için atama yapılamaz. Diğer simülasyon verileri kopyalanmaz.

    return *this;
}

// Çıktı Operatörü (4.4.2)
std::ostream& operator<<(std::ostream& o, const Fahrzeug& fzg) {
    fzg.vAusgeben(o);
    return o;
}

// Karşılaştırma Operatörü (4.4.4: Toplam mesafeye göre)
bool Fahrzeug::operator<(const Fahrzeug& other) const {
    return p_dGesamtStrecke < other.p_dGesamtStrecke;
}
