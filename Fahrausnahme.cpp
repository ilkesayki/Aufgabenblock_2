/*
 * Fahrausnahme.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <iostream>
#include <memory>

// Losfahren: Park eden aracı al, süren araç olarak geri koy
void Losfahren::vBearbeiten() const {
    std::cout << "AUSNAHME: Fahrzeug \"" << p_pFahrzeug.getName()
              << "\" faehrt auf Weg \"" << p_pWeg.getName() << "\" los!" << std::endl;

    std::unique_ptr<Fahrzeug> fzg = p_pWeg.pAbgabe(p_pFahrzeug);

    // GÜVENLİK KONTROLÜ: Araç gerçekten alındı mı?
    if (fzg != nullptr) {
        p_pWeg.vAnnahme(std::move(fzg));
    } else {
        // Hata durumunda ekrana bilgi verelim (Debug için)
        std::cerr << "HATA: Losfahren islenirken arac listede bulunamadi!" << std::endl;
    }
}

// Streckenende: Aracı yoldan tamamen sil
void Streckenende::vBearbeiten() const {
    std::cout << "AUSNAHME: Fahrzeug \"" << p_pFahrzeug.getName()
              << "\" am Ende von Weg \"" << p_pWeg.getName() << "\" angekommen!" << std::endl;

    // Aracı yoldan çekip al (pAbgabe).
    // Geri koymadığımız için araç (unique_ptr) hafızadan silinir.
    p_pWeg.pAbgabe(p_pFahrzeug);
}

