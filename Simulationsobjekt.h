/*
 * Simulationsobjekt.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>
#include <iostream>
#include <iomanip>

class Simulationsobjekt {
private:
    static int p_iMaxID; // Tüm simulation objeleri için ortak sayaç

protected:
    const int p_iID;
    std::string p_sName;
    double p_dZeit; // En son simüle edildiği zaman

public:
    Simulationsobjekt(std::string name);
    virtual ~Simulationsobjekt();

    // Copy Constructor yasaklandı (Yönerge gereği)
    Simulationsobjekt(const Simulationsobjekt&) = delete;

    // Assignment operator (Sadece ismi kopyalar, ID değişmez)
    Simulationsobjekt& operator=(const Simulationsobjekt& other);

    // Getters
    const std::string& getName() const { return p_sName; }
    int getID() const { return p_iID; }
    double getZeit() const { return p_dZeit; }

    // Pure Virtual Fonksiyon (Sınıfı soyut yapar)
    virtual void vSimulieren() = 0;

    virtual void vAusgeben(std::ostream& o) const;

    // Operatörler
    bool operator==(const Simulationsobjekt& other) const;
};

// Global çıkış operatörü (Artık Simulationsobjekt alıyor)
std::ostream& operator<<(std::ostream& o, const Simulationsobjekt& so);

#endif /* SIMULATIONSOBJEKT_H_ */
