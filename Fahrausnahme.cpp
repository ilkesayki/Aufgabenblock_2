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


extern double dGlobaleZeit;


void Losfahren::vBearbeiten() const {
    std::cout << "AUSNAHME: Fahrzeug \"" << p_pFahrzeug.getName()
              << "\" faehrt auf Weg \"" << p_pWeg.getName() << "\" los!" << std::endl;

    //Remove the vehicle from the road
    std::unique_ptr<Fahrzeug> fzg = p_pWeg.pAbgabe(p_pFahrzeug);

    //Put the vehicle back on the roaad
    if (fzg != nullptr) {
        p_pWeg.vAnnahme(std::move(fzg));
    }
}


void Streckenende::vBearbeiten() const {
	//Remove the vehicle from the road
    std::unique_ptr<Fahrzeug> fzg = p_pWeg.pAbgabe(p_pFahrzeug);


    if (fzg == nullptr) return;

    //Find the Krezung
    auto zielKreuzung = p_pWeg.getZielkreuzung();


    if (zielKreuzung != nullptr) {

        zielKreuzung->vTanken(*fzg);

        //Fahrausnahme.cpp -> Weg.cpp (Get info) -> Kreuzung.cpp (decide) -> Fahrausnahme.cpp (get result).
        auto neuerWeg = zielKreuzung->pZufaelligerWeg(p_pWeg.getRueckweg()); //use auto instead of std::shared_ptr<Weg>

        //Road true?
        if (neuerWeg != nullptr) {


            std::cout << "ZEIT     : " << dGlobaleZeit << std::endl
                      << "KREUZUNG : " << zielKreuzung->getName() << " " << zielKreuzung->getTankstelle() << "L" << std::endl
                      << "WECHSEL  : " << p_pWeg.getName() << " -> " << neuerWeg->getName() << std::endl
                      << "FAHRZEUG : " << fzg->getName() << std::endl;

            //Put the vehicle back on the road
            neuerWeg->vAnnahme(std::move(fzg));
            return;
        }
    }


    std::cout << "AUSNAHME: Fahrzeug " << fzg->getName() << " am Ende (Sackgasse/Ziel)." << std::endl;
}
