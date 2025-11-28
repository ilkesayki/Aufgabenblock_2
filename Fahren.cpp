/*
 * Fahren.cpp
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrausnahme.h"
#include <iostream>

Fahren::Fahren(Weg& weg) : Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
    double dMoeglicheStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;
    double dRestStrecke = p_pWeg.getLaenge() - aFzg.getAbschnittStrecke();

    if (dRestStrecke <= 0) {
         // Yol zaten bitmişti, tekrar çağrıldıysa hata fırlat
         throw Streckenende(aFzg, p_pWeg);
    }

    if (dMoeglicheStrecke < dRestStrecke) {
        return dMoeglicheStrecke;
    } else {
        // Yolun sonuna gelindi -> İSTİSNA FIRLAT
        // Önce aracı tam yolun sonuna koyalım (return dRestStrecke yapılacak ama throw araya giriyor)
        // Yönergeye göre burada throw atmamız lazım.
        // Ancak dStrecke double dönüyor. Throw attığımızda akış kesilir.

        throw Streckenende(aFzg, p_pWeg);

        // Bu satıra asla gelinmez ama derleyici susması için:
        return dRestStrecke;
    }
}


