/*
 * Fahrausnahme.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"
#include <iostream>

// Global zaman değişkenini burada bildiriyoruz (Dosyanın başında)
extern double dGlobaleZeit;

// Losfahren: Park eden aracı al, süren araç olarak geri koy
void Losfahren::vBearbeiten() const {
    std::cout << "AUSNAHME: Fahrzeug \"" << p_pFahrzeug.getName()
              << "\" faehrt auf Weg \"" << p_pWeg.getName() << "\" los!" << std::endl;

    // Aracı yoldan çek
    std::unique_ptr<Fahrzeug> fzg = p_pWeg.pAbgabe(p_pFahrzeug);

    // Geri koy (Fahren moduna geçer)
    if (fzg != nullptr) {
        p_pWeg.vAnnahme(std::move(fzg));
    }
}

// Streckenende: Aracı KAVŞAĞA devret
void Streckenende::vBearbeiten() const {
    // 1. Aracı mevcut yoldan çek
    std::unique_ptr<Fahrzeug> fzg = p_pWeg.pAbgabe(p_pFahrzeug);

    // Güvenlik: Araç bulunamadıysa çık
    if (fzg == nullptr) return;

    // 2. Yolun gittiği kavşağı bul
    auto zielKreuzung = p_pWeg.getZielkreuzung(); // shared_ptr döner

    // 3. Kavşak geçerli mi?
    if (zielKreuzung != nullptr) {
        // a) Depoyu fulle
        zielKreuzung->vTanken(*fzg);

        // b) Yeni yol seç
        // p_pWeg.getRueckweg() bize geldiğimiz yolu verir.
        // Bunu parametre olarak veriyoruz ki geri dönmeyelim.
        auto neuerWeg = zielKreuzung->pZufaelligerWeg(p_pWeg.getRueckweg());

        // c) Yeni yol bulundu mu?
        if (neuerWeg != nullptr) {

            // Çıktı formatı (Yönergeye uygun)
            std::cout << "ZEIT     : " << dGlobaleZeit << std::endl
                      << "KREUZUNG : " << zielKreuzung->getName() << " " << zielKreuzung->getTankstelle() << "L" << std::endl
                      << "WECHSEL  : " << p_pWeg.getName() << " -> " << neuerWeg->getName() << std::endl
                      << "FAHRZEUG : " << fzg->getName() << std::endl;

            // d) Aracı yeni yola koy
            neuerWeg->vAnnahme(std::move(fzg));
            return;
        }
    }

    // Eğer kavşak yoksa veya yol bulunamazsa araç silinir (Eski davranış)
    std::cout << "AUSNAHME: Fahrzeug " << fzg->getName() << " am Ende (Sackgasse/Ziel)." << std::endl;
}
