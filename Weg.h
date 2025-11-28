/*
 * Weg.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include <memory>

// Forward Declaration (Zirkuläre Abhängigkeit önlemek için)
class Fahrzeug;

class Weg : public Simulationsobjekt {
private:
    double p_dLaenge;
    Tempolimit p_eTempolimit;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; // Yeni

public:
    Weg(std::string name, double laenge, Tempolimit limit = Tempolimit::Autobahn);
    virtual ~Weg();

    double getTempolimit() const;

    double getLaenge() const { return p_dLaenge; }

    // Araç kabul etme (unique_ptr move ile alınır)
    void vAnnahme(std::unique_ptr<Fahrzeug> fzg);
    void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit);

    virtual void vSimulieren() override;
    virtual void vAusgeben(std::ostream& o) const override;

    void vZeichnen() const;
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fzg);

    static void vKopf();
};

#endif /* WEG_H_ */
