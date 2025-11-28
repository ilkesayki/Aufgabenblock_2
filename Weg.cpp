/*
 * Weg.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */


#include "Weg.h"
#include "Fahrzeug.h" // Burada include ediyoruz çünkü metodlarını kullanacağız
#include "Parken.h"
#include "Fahrausnahme.h"

Weg::Weg(std::string name, double laenge, Tempolimit limit)
    : Simulationsobjekt(name),
      p_dLaenge(laenge),
      p_eTempolimit(limit)
{
}

Weg::~Weg() {}

void Weg::vSimulieren() {
    p_pFahrzeuge.vAktualisieren(); // Listeyi temizle

    for (auto& fzg : p_pFahrzeuge) {
        // GÜVENLİK KONTROLÜ: Araç pAbgabe ile alınmış olabilir
        if (fzg == nullptr) continue;

        try {
            fzg->vSimulieren();
            fzg->vZeichnen(*this);
        }
        catch (const Fahrausnahme& e) {
            e.vBearbeiten();
        }
    }
    p_dZeit = dGlobaleZeit;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit) {
    // Araca yeni yolu ve start zamanını bildir (Park davranışı atanır)
    fzg->vNeueStrecke(*this, startzeit);

    // Park eden araçlar listenin BAŞINA eklenir (Yönerge Bölüm 5.4.4)
    p_pFahrzeuge.push_front(std::move(fzg));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg) {
    // Araca yeni yolu bildir (Sürme davranışı atanır)
    fzg->vNeueStrecke(*this);

    // Süren araçlar listenin SONUNA eklenir
    p_pFahrzeuge.push_back(std::move(fzg));
}

void Weg::vAusgeben(std::ostream& o) const {
    Simulationsobjekt::vAusgeben(o);

    o << ": " << std::setw(8) << std::fixed << std::setprecision(2) << p_dLaenge
      << " ( ";

    for (const auto& fzg : p_pFahrzeuge) {
        // --- GÜVENLİK KONTROLÜ EKLENDİ ---
        if (fzg == nullptr) continue; // Araç yoksa/silindiyse atla
        // ---------------------------------

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
        // --- GÜVENLİK KONTROLÜ EKLENDİ ---
        // Eğer araç transfer edildiyse (boşsa) çizmeye çalışma!
        if (fzg == nullptr) continue;
        // ---------------------------------

        fzg->vZeichnen(*this);
    }
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fzg) {
    // Listeyi tara
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        // GÜVENLİK KONTROLÜ 1: İşaretçi boş mu?
        if (*it == nullptr) continue; // Boşsa atla, yoksa **it yapınca çökeriz!

        // GÜVENLİK KONTROLÜ 2: Aradığımız araç mı?
        if (**it == fzg) {
            // Aracı listeden çek al
            std::unique_ptr<Fahrzeug> temp = std::move(*it);
            // Silme emri ver (Gecikmeli silinir)
            p_pFahrzeuge.erase(it);
            return temp;
        }
    }
    return nullptr; // Bulunamadı
}
