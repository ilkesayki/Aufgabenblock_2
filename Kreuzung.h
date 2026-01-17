/*
 * Kreuzung.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <list>
#include <memory>
#include <string>

// Forward declaration
class Weg;
class Fahrzeug;

class Kreuzung : public Simulationsobjekt {
private:
    std::list<std::shared_ptr<Weg>> p_pWege; // Kavşaktan çıkan yollar
    double p_dTankstelle; // Kavşaktaki benzin miktarı

public:
    Kreuzung(std::string name, double tankstelle = 0.0);
    virtual ~Kreuzung();

    // Statik Bağlantı Fonksiyonu (İki kavşağı bağlar)
    static void vVerbinde(std::shared_ptr<Kreuzung> k1, std::shared_ptr<Kreuzung> k2,
                          std::string nameHin, std::string nameRueck,
                          double laenge, bool bUeberholverbot = true,
                          Tempolimit limit = Tempolimit::Autobahn);

    // Araç Yakıt Alma
    void vTanken(Fahrzeug& fzg);

    // Aracı kabul edip uygun bir yola yönlendirme
    void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit);

    // Simülasyon
    virtual void vSimulieren() override;

    // Rastgele yol seçimi (Geldiği yola geri dönmesin)
    std::shared_ptr<Weg> pZufaelligerWeg(std::weak_ptr<Weg> ankunftsweg);

    // Getter
    double getTankstelle() const { return p_dTankstelle; }
};

#endif /* KREUZUNG_H_ */
