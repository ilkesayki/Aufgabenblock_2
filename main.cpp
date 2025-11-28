/*
 * main.cpp
 *
 * Created on: Nov 3, 2025
 * Author: ilkesayki
 */

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// Tasks
void vAufgabe_1();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
// ------------------------------------------

// Global Time, declared extern in classes
double dGlobaleZeit = 0.0;

// Smart Pointer and Memory Management Test
void vAufgabe_1() {
    cout << "--- 4.2.4: Static, Dynamic and Smart Pointer Test ---" << endl;

    // Note: Output within constructors/destructors (Fahrzeug.cpp) remains in German
    // to track creation/deletion operations with original log messages.

    // A) Static and Dynamic Objects
    cout << "\n[A] Static and Dynamic Objects:" << endl;
    Fahrzeug f_statisch("Static_Car");
    Fahrzeug* f_ptr = new Fahrzeug("Dynamic_Ptr");

    delete f_ptr;

    // B) Smart Pointers
    cout << "\n[B] Smart Pointers:" << endl;

    auto up1 = make_unique<Fahrzeug>("Unique_1");
    auto up2 = make_unique<Fahrzeug>("Unique_2");

    auto sp1 = make_shared<Fahrzeug>("Shared_1");

    cout << "Shared_1 Reference Count (initial): " << sp1.use_count() << endl;

    shared_ptr<Fahrzeug> sp_copy = sp1;
    cout << "Shared_1 Reference Count (after copy): " << sp1.use_count() << endl;

    // C) unique_ptr and shared_ptr Vectors

    cout << "\n[C1] unique_ptr Vector Test:" << endl;
    vector<unique_ptr<Fahrzeug>> v_unique;


    v_unique.push_back(std::move(up1));
    v_unique.push_back(make_unique<Fahrzeug>("Unique_In_Vector_3"));

    cout << "Vector is being cleared (v_unique.clear())..." << endl;
    v_unique.clear();
}


//Inheritance, Fueling, and Polymorphism (User Input Version)
void vAufgabe_2() {
    std::cout << "\n--- 4.3.4: PKW, Bicycle and Fueling Test (vAufgabe_2) (User Input Version) ---" << std::endl;

    // --- PKW Input ---
    int anzahlPKW;
    std::cout << "\n[PKW Data Input]" << std::endl;
    std::cout << "Enter the number of PKWs to create (2-4 recommended): ";
    std::cin >> anzahlPKW;

    if (anzahlPKW < 0) anzahlPKW = 0;

    std::vector<std::string> pkwNamen = {"Audi", "BMW", "VW", "Mercedes", "Porsche", "Ferrari"};

    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

    for (int i = 0; i < anzahlPKW; ++i) {
        std::string name = pkwNamen[i % pkwNamen.size()];
        double maxGeschw;
        double verbrauch;

        std::cout << "\n--- PKW " << i + 1 << " (" << name << ") ---" << std::endl;

        // Max Speed Input
        std::cout << "Enter Maximum Speed (km/h) for " << name << ": ";
        std::cin >> maxGeschw;

        // Consumption Input
        std::cout << "Enter Consumption (L/100km) for " << name << ": ";
        std::cin >> verbrauch;

        fahrzeuge.push_back(std::make_unique<PKW>(name + "_" + std::to_string(i + 1),
                                                 std::max(1.0, maxGeschw),
                                                 std::max(0.1, verbrauch)));
    }

    // --- Bicycle Input ---
    int anzahlFahrrad;
    std::cout << "\n[Bicycle Data Input]" << std::endl;
    std::cout << "Enter the number of Bicycles to create: ";
    std::cin >> anzahlFahrrad;

    for (int i = 0; i < anzahlFahrrad; ++i) {
        fahrzeuge.push_back(std::make_unique<Fahrrad>("Bicycle_" + std::to_string(i + 1), 30.0));
    }


    if (fahrzeuge.empty()) {
        std::cout << "No vehicles created. Test ending." << std::endl;
        return;
    }

    double dZeitTakt = 1.0;
    int anzahlSchritte = 15;

    const double TOLERANZ = 1e-9;
    const double TANKZEIT = 3.0;

    dGlobaleZeit = 0.0;

    for (int schritt = 1; schritt <= anzahlSchritte; ++schritt) {
        dGlobaleZeit += dZeitTakt;

        std::cout << "\n==========================================================" << std::endl;
        std::cout << ">>> Simulation Step " << schritt << " (Global Time: " << dGlobaleZeit << "h) <<<" << std::endl;

        // Fueling after 3 hours
        if (std::fabs(dGlobaleZeit - TANKZEIT) < TOLERANZ) {
            std::cout << "\n--- !!! REFUELING AFTER 3 HOURS !!! ---" << std::endl;
            for (const auto& fzg_ptr : fahrzeuge) {
                PKW* pkwPtr = dynamic_cast<PKW*>(fzg_ptr.get());
                if (pkwPtr != nullptr) {
                    double getankt = pkwPtr->dTanken();
                    std::cout << pkwPtr->getName() << " refueled: " << getankt << " L." << std::endl;
                }
            }
            std::cout << "--- !!! REFUELING FINISHED !!! ---\n" << std::endl;
        }

        Fahrzeug::vKopf(); // Output table header

        // Simulate all vehicles
        for (const auto& fzg_ptr : fahrzeuge) {
            fzg_ptr->vSimulieren();
            std::cout << *fzg_ptr << std::endl;
        }
    }
}


// Operator Overloading Test
void vAufgabe_3() {
    std::cout << "\n--- 4.4.6: Operator Test (vAufgabe_3) ---" << endl;

    // Note: Output within constructors/destructors remains in German log
    std::unique_ptr<PKW> pkw1 = std::make_unique<PKW>("BMW", 200.0, 8.0);
    std::unique_ptr<PKW> pkw2 = std::make_unique<PKW>("Audi", 180.0, 7.5);
    std::unique_ptr<Fahrrad> bike = std::make_unique<Fahrrad>("BMX", 35.0);

    // Set simulation state
    dGlobaleZeit = 1.0;
    pkw1->vSimulieren();
    dGlobaleZeit = 2.0;
    pkw2->vSimulieren();
    dGlobaleZeit = 3.0;
    bike->vSimulieren();

    std::cout << "\n--- 1. operator<< Test (Output Operator) ---" << std::endl;
    Fahrzeug::vKopf();
    std::cout << *pkw1 << std::endl;
    std::cout << *pkw2 << std::endl;
    std::cout << *bike << std::endl;

    std::cout << "\n--- 2. operator< Test (Comparison by Distance) ---" << std::endl;
    if (*pkw1 < *pkw2) {
        std::cout << "PKW1 (BMW) distance is less than PKW2 (Audi) (OK). " << std::endl;
    } else {
        std::cout << "PKW1 (BMW) distance is greater than or equal to PKW2 (Audi) (ERROR). " << std::endl;
    }

    if (*bike < *pkw1) {
        std::cout << "Bicycle (BMX) distance is less than PKW1 (BMW) (OK). " << std::endl;
    } else {
        std::cout << "Bicycle (BMX) distance is greater than or equal to PKW1 (BMW) (ERROR). " << std::endl;
    }

    std::cout << "\n--- 3. operator= Test (Assignment Operator) ---" << std::endl;
    PKW pkw_target("Target", 100.0, 5.0, 40.0);

    std::cout << "Target (ID: " << pkw_target.getID() << ", Before Assignment): " << pkw_target << std::endl;

    // Assignment (copies only name and max speed, other data like ID, distance, fuel is not copied)
    pkw_target = *pkw1;

    std::cout << "Target (ID: " << pkw_target.getID() << ", After Assignment): " << pkw_target << std::endl;
}

void vAufgabe_4() {
    Weg w1("B54", 50.0, Tempolimit::Innerorts);

    auto p1 = std::make_unique<PKW>("BMW", 120, 8.5);
    auto p2 = std::make_unique<Fahrrad>("BMX", 25);

    // Araçları yola ekle
    w1.vAnnahme(std::move(p1));
    w1.vAnnahme(std::move(p2));

    Weg::vKopf();
    std::cout << w1 << std::endl;
}

void vAufgabe_5() {
    Weg w1("B54", 50.0, Tempolimit::Innerorts);

    auto p1 = std::make_unique<PKW>("BMW", 120, 8.5);
    auto p2 = std::make_unique<Fahrrad>("BMX", 25);
    auto p3 = std::make_unique<PKW>("Audi", 150, 9.0);

    // Park eden araç (3 saat sonra kalkacak)
    w1.vAnnahme(std::move(p1), 3.0);

    // Giden araçlar
    w1.vAnnahme(std::move(p2));
    w1.vAnnahme(std::move(p3));

    // Simülasyon Döngüsü
    dGlobaleZeit = 0.0;
    for (int i = 0; i < 10; ++i) {
        dGlobaleZeit += 0.5;
        w1.vSimulieren();
        std::cout << "Zeit: " << dGlobaleZeit << std::endl;
        std::cout << w1 << std::endl;
        std::cout << "------------------" << std::endl;
    }
}

void vAufgabe_6() {
    // 1. Grafik Server ile bağlantı kur
    // Eğer SimuServer.jar çalışmıyorsa bu adımda hata alabilirsin.
    if (bInitialisiereGrafik(800, 500)) {
        std::cout << "Grafik baslatildi!" << std::endl;
    } else {
        std::cout << "Grafik server baglantisi basarisiz! (SimuServer.jar acik mi?)" << std::endl;
        return;
    }

    // 2. Yolları Oluştur (Gidiş ve Dönüş olarak çizilir ama biz şimdilik tek yol kullanıyoruz)
    Weg w1("B54", 500.0, Tempolimit::Autobahn);

    // Yolu çizmek için koordinatları veriyoruz (Düz bir çizgi)
    int iKoord[] = { 100, 250, 700, 250 }; // x1, y1, x2, y2
    bZeichneStrasse("B54", "B54_Rueck", 500, 2, iKoord); // Rückweg ismi formalite

    // 3. Araçları Oluştur
    auto p1 = std::make_unique<PKW>("BMW", 120, 8.5);
    auto p2 = std::make_unique<Fahrrad>("BMX", 25);
    auto p3 = std::make_unique<PKW>("Audi", 150, 9.0);

    w1.vAnnahme(std::move(p1), 3.0); // Park eden araç
    w1.vAnnahme(std::move(p2));
    w1.vAnnahme(std::move(p3));

    // 4. Simülasyon Döngüsü
    dGlobaleZeit = 0.0;
    for (int i = 0; i < 200; ++i) { // Daha uzun süre dönsün
        dGlobaleZeit += 0.2; // Zaman adımını küçülttük daha akıcı görünsün
        vSetzeZeit(dGlobaleZeit); // Server'daki saati güncelle

        w1.vSimulieren(); // Hatalar (Exception) ekrana basılmaya devam edecek
        w1.vZeichnen();   // Grafik güncelle

        vSleep(100); // 100ms bekle (Simülasyonu yavaşlat)
    }

    // Bağlantıyı kes
    vBeendeGrafik();
}


int main() {
    int iAuswahl;

    while (true) {
        // Menü Yazıları
        std::cout << "\n\n==============================================" << std::endl;
        std::cout << "VERKEHRSSIMULATION - HAUPTMENU" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "1. vAufgabe_1() : Statisch, Dynamisch & Smart Pointers" << std::endl;
        std::cout << "2. vAufgabe_2() : Fahrzeuge, PKW & Fahrrad (Eingabe)" << std::endl;
        std::cout << "3. vAufgabe_3() : Operator Overloading" << std::endl;
        std::cout << "4. vAufgabe_4() : Weg & Listen" << std::endl;
        std::cout << "5. vAufgabe_5() : Verhalten (Parken & Fahren)" << std::endl;
        std::cout << "6. vAufgabe_6() : Grafik & Exceptions" << std::endl;
        std::cout << "0. Beenden" << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "Ihre Auswahl: ";
        std::cin >> iAuswahl;

        // Hatalı giriş kontrolü (Harf girilirse döngü bozulmasın diye)
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ungueltige Eingabe! Bitte eine Zahl eingeben." << std::endl;
            continue;
        }

        // Çıkış komutu
        if (iAuswahl == 0) {
            std::cout << "Programm beendet." << std::endl;
            break;
        }

        // Her görevden önce global zamanı sıfırla!
        dGlobaleZeit = 0.0;

        switch (iAuswahl) {
            case 1:
                vAufgabe_1();
                break;
            case 2:
                vAufgabe_2();
                break;
            case 3:
                vAufgabe_3();
                break;
            case 4:
                vAufgabe_4();
                break;
            case 5:
                vAufgabe_5();
                break;
            case 6:
                // Grafik için uyarı
                std::cout << ">>> Starten Sie 'SimuServer.jar' im Hintergrund! <<<" << std::endl;
                vAufgabe_6();
                break;
            default:
                std::cout << "Unbekannte Auswahl: " << iAuswahl << std::endl;
                break;
        }

        // Görev bittikten sonra biraz bekleme veya enter isteme (Opsiyonel)
        // std::cout << "\nDruecken Sie ENTER fuer das Menue...";
        // std::cin.ignore(); std::cin.get();
    }

    return 0;
}
