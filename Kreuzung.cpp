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
#include <algorithm>
#include <random>

Kreuzung::Kreuzung(std::string name, double tankstelle)
    : Simulationsobjekt(name), p_dTankstelle(tankstelle)
{}

Kreuzung::~Kreuzung() {}

void Kreuzung::vVerbinde(std::shared_ptr<Kreuzung> k1, std::shared_ptr<Kreuzung> k2,
                         std::string nameHin, std::string nameRueck,
                         double laenge, bool bUeberholverbot, Tempolimit limit)
{
    // make_shared allocates a single block for the object and control block, which is faster than new
    auto hin = std::make_shared<Weg>(nameHin, laenge, limit);
    auto rueck = std::make_shared<Weg>(nameRueck, laenge, limit);


    hin->setRueckweg(rueck);
    rueck->setRueckweg(hin);


    hin->setZielkreuzung(k2);
    rueck->setZielkreuzung(k1);


    k1->p_pWege.push_back(hin);
    k2->p_pWege.push_back(rueck);


    std::cout << "Verbindung erstellt: " << k1->getName() << " <--> " << k2->getName() << std::endl;
}

void Kreuzung::vTanken(Fahrzeug& fzg) {
    if (p_dTankstelle > 0) {
        double getankt = fzg.dTanken();
        p_dTankstelle -= getankt;
        if (p_dTankstelle < 0) p_dTankstelle = 0;
    }
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit) {
    vTanken(*fzg);

    if (!p_pWege.empty()) {
        p_pWege.front()->vAnnahme(std::move(fzg), startzeit);
    }
}

void Kreuzung::vSimulieren() {
    for (auto& weg : p_pWege) {
        weg->vSimulieren();
    }
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(std::weak_ptr<Weg> ankunftsweg) {
    if (p_pWege.empty()) return nullptr;
    if (p_pWege.size() == 1) return p_pWege.front();

    static std::mt19937 device(0); //static makes choose something different every time
    std::uniform_int_distribution<int> dist(0, p_pWege.size() - 1);

    auto ankunft = ankunftsweg.lock(); //Locks the Ankunftsweg

    while (true) {
        int index = dist(device);
        auto it = p_pWege.begin();
        std::advance(it, index);

        if (ankunft && *it == ankunft) {
            continue;
        }


        return *it;
    }
}

