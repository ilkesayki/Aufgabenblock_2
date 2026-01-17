/*
 * Kreuzung.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Tempolimit.h"
#include <iostream>
#include <algorithm> // random_shuffle veya benzeri için
#include <random>    // Yeni C++ random için

Kreuzung::Kreuzung(std::string name, double tankstelle)
    : Simulationsobjekt(name), p_dTankstelle(tankstelle)
{}

Kreuzung::~Kreuzung() {}

void Kreuzung::vVerbinde(std::shared_ptr<Kreuzung> k1, std::shared_ptr<Kreuzung> k2,
                         std::string nameHin, std::string nameRueck,
                         double laenge, bool bUeberholverbot, Tempolimit limit)
{
    // 1. Yolları Oluştur (make_shared)
    auto hin = std::make_shared<Weg>(nameHin, laenge, limit);
    auto rueck = std::make_shared<Weg>(nameRueck, laenge, limit);

    // 2. Yolların özelliklerini ayarla (Ueberholverbot vs. eklenebilir)

    // 3. Bağlantıları Kur (Rueckweg)
    hin->setRueckweg(rueck);
    rueck->setRueckweg(hin);

    // 4. Hedef Kavşakları Ayarla
    hin->setZielkreuzung(k2);
    rueck->setZielkreuzung(k1);

    // 5. Yolları Kavşaklara Ekle (Kavşak giden yolu tutar)
    k1->p_pWege.push_back(hin);
    k2->p_pWege.push_back(rueck);

    // Log
    std::cout << "Verbindung erstellt: " << k1->getName() << " <--> " << k2->getName() << std::endl;
}

void Kreuzung::vTanken(Fahrzeug& fzg) {
    if (p_dTankstelle > 0) {
        // Aracı full depoya tamamla, tanktan düş
        // (Burada basitçe 0 gönderip dolumu sağlıyoruz, gerçek miktar Fahrzeug::dTanken'dan döner)
        double getankt = fzg.dTanken();
        p_dTankstelle -= getankt;
        if (p_dTankstelle < 0) p_dTankstelle = 0;
    }
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit) {
    // Aracı yakıtla
    vTanken(*fzg);

    // İlk yola yerleştir (Basit mantık: Listenin başındaki yola koy)
    if (!p_pWege.empty()) {
        p_pWege.front()->vAnnahme(std::move(fzg), startzeit);
    }
}

void Kreuzung::vSimulieren() {
    // Kavşağa bağlı tüm yolları simüle et
    for (auto& weg : p_pWege) {
        weg->vSimulieren();
    }
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(std::weak_ptr<Weg> ankunftsweg) {
    if (p_pWege.empty()) return nullptr;
    if (p_pWege.size() == 1) return p_pWege.front();

    static std::mt19937 device(0);
    std::uniform_int_distribution<int> dist(0, p_pWege.size() - 1);

    // ankunft: Bizim geldiğimiz yolun tersi (yani kaçınmamız gereken yol)
    auto ankunft = ankunftsweg.lock();

    while (true) {
        int index = dist(device);
        auto it = p_pWege.begin();
        std::advance(it, index);

        // --- DÜZELTME BURADA ---
        // Seçilen yol (*it), kaçınmamız gereken yol (ankunft) ile AYNI ise tekrar seç.
        if (ankunft && *it == ankunft) {
            continue;
        }
        // -----------------------

        return *it;
    }
}

