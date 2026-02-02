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

// Forward Declaration (to prevent Circular Dependency)
class Fahrzeug;

class Kreuzung;

class Weg : public Simulationsobjekt {
private:
    double p_dLaenge;
    Tempolimit p_eTempolimit;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; // Verträgte Liste
    //unique instead of shared to move instead of copy

    std::weak_ptr<Kreuzung> p_pZielkreuzung;
    std::weak_ptr<Weg> p_pRueckweg;          //mark the intersection without owning it.

public:
    Weg(std::string name, double laenge, Tempolimit limit = Tempolimit::Autobahn);
    virtual ~Weg();

    double getTempolimit() const;

    double getLaenge() const { return p_dLaenge; }

    // Vehicle Acceptance: unique_ptr (move not copy)
    void vAnnahme(std::unique_ptr<Fahrzeug> fzg);
    void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startzeit);

    virtual void vSimulieren() override;
    virtual void vAusgeben(std::ostream& o) const override;

    void vZeichnen() const;
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fzg); //ownership (unique_ptr) is returned after reaching the end

    // weak_ptr doesn't own the object, it cant guarantee that the object still exists.
    //Direct access is unsafe. That's why use lock()
    std::shared_ptr<Weg> getRueckweg() const { return p_pRueckweg.lock(); }
    std::shared_ptr<Kreuzung> getZielkreuzung() const { return p_pZielkreuzung.lock(); }


    void setZielkreuzung(std::weak_ptr<Kreuzung> ziel) { p_pZielkreuzung = ziel; }
    void setRueckweg(std::weak_ptr<Weg> rueckweg) { p_pRueckweg = rueckweg; }

    static void vKopf();
};

#endif /* WEG_H_ */
