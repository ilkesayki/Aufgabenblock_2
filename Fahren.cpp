/*
 * Fahren.cpp
 *
 * Created on: Nov 28, 2025
 * Author: ilkesayki
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrausnahme.h"
#include <iostream>
#include <algorithm>      // std::min için gerekli
#include <cmath>          // std::abs için gerekli

Fahren::Fahren(Weg& weg) : Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {

    // --- 1. ADIM: Gerçek Hızı Hesapla (Sınav için kritik nokta) ---
    // Aracın max hızı ile Yolun limiti kıyaslanır, düşük olan alınır.

    double dFahrzeugSpeed = aFzg.dGeschwindigkeit();   // Örn: 200 km/h
    double dWegLimit = p_pWeg.getTempolimit();         // Örn: 50 km/h (Weg.cpp'deki fonksiyonun)

    // Gerçek hız ikisinin küçüğüdür
    double dRealSpeed = std::min(dFahrzeugSpeed, dWegLimit);

    // Gidilebilecek yol = Gerçek Hız * Zaman
    double dMoeglicheStrecke = dRealSpeed * dZeitIntervall;

    // -----------------------------------------------------------

    // Kalan yol ne kadar?
    double dRestStrecke = p_pWeg.getLaenge() - aFzg.getAbschnittStrecke();

    // Güvenlik kontrolü: Double sayıları 0 ile kıyaslarken tolerans kullanmak iyidir
    if (std::abs(dRestStrecke) < 1e-6 || dRestStrecke < 0) {
         throw Streckenende(aFzg, p_pWeg);
    }

    // Durum A: Yol bitmiyor, sürmeye devam
    if (dMoeglicheStrecke < dRestStrecke) {
        return dMoeglicheStrecke;
    }
    // Durum B: Yol bitti (veya tam ucu ucuna yetti)
    else {
        // İSTİSNA FIRLAT (Akış burada kesilir ve catch bloğuna gider)
        throw Streckenende(aFzg, p_pWeg);

        // Bu satıra asla gelinmez ama derleyici "return yok" demesin diye:
        return dRestStrecke;
    }
}
