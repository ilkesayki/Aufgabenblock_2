#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>

using namespace std;

// --- FONKSİYON BİLDİRİMLERİ (PROTOTİPLER) ---
void vAufgabe_1();
void vAufgabe_2();
void vAufgabe_3();
// ---------------------------------------------

// Global saatin tanımı (Adım 4.2.7)
double dGlobaleZeit = 0.0;

// Görev 4.2.4'ü test eden fonksiyon (Smart Pointers)
void vAufgabe_1() {
    cout << "--- 4.2.4: Statik, Dinamik und Smart Pointer Test ---" << endl;

    // A) Statik und Dynamik Nesneler
    cout << "\n[A] Statik und Dinamik Nesneler:" << endl;
    Fahrzeug f_statisch("Statik_Auto");
    Fahrzeug* f_ptr = new Fahrzeug("Dinamik_Ptr");

    delete f_ptr;

    // B) Smart Pointers
    cout << "\n[B] Smart Pointer'lar:" << endl;

    auto up1 = make_unique<Fahrzeug>("Unique_1");
    auto up2 = make_unique<Fahrzeug>("Unique_2");

    auto sp1 = make_shared<Fahrzeug>("Shared_1");

    cout << "Shared_1 Referans Sayısı (başlangıç): " << sp1.use_count() << endl;

    shared_ptr<Fahrzeug> sp_copy = sp1;
    cout << "Shared_1 Referans Sayısı (kopyalama sonrası): " << sp1.use_count() << endl;

    // C) unique_ptr ve shared_ptr Vektörleri

    // 1. vector<unique_ptr<Fahrzeug>>
    cout << "\n[C1] unique_ptr Vector Testi:" << endl;
    vector<unique_ptr<Fahrzeug>> v_unique;

    v_unique.push_back(std::move(up1));
    v_unique.push_back(make_unique<Fahrzeug>("Unique_In_Vector_3"));

    cout << "Vektör temizleniyor (v_unique.clear())..." << endl;
    v_unique.clear();
}


// Görev 4.3.4'ü test eden fonksiyon (PKW, Fahrrad, Tanken, Polimorfizm)
void vAufgabe_2() {
    std::cout << "\n--- 4.3.4: PKW, Fahrrad und Tanken Test (vAufgabe_2) ---" << std::endl;

    int anzahlPKW, anzahlFahrrad;
    std::cout << "Anzahl PKW: ";
    std::cin >> anzahlPKW;
    std::cout << "Anzahl Fahrräder: ";
    std::cin >> anzahlFahrrad;

    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

    // PKW'leri oluştur
    for (int i = 0; i < anzahlPKW; ++i) {
        fahrzeuge.push_back(std::make_unique<PKW>("PKW_" + std::to_string(i + 1),
                                                 150.0 + i * 10,
                                                 7.0));
    }
    // Bisikletleri oluştur
    for (int i = 0; i < anzahlFahrrad; ++i) {
        fahrzeuge.push_back(std::make_unique<Fahrrad>("Fahrrad_" + std::to_string(i + 1),
                                                      30.0));
    }

    double dZeitTakt = 0.25;
    int anzahlSchritte = 15;

    const double TOLERANZ = 1e-9;
    const double TANKZEIT = 3.0;

    dGlobaleZeit = 0.0;

    for (int schritt = 1; schritt <= anzahlSchritte; ++schritt) {
        dGlobaleZeit += dZeitTakt;

        std::cout << "\n==========================================================" << std::endl;
        std::cout << ">>> Simulationsschritt " << schritt << " (Globale Zeit: " << dGlobaleZeit << "h) <<<" << std::endl;

        // --- Tanklama Kontrolü (Tam 3 saatte) ---
        if (std::fabs(dGlobaleZeit - TANKZEIT) < TOLERANZ) {
            std::cout << "\n--- !!! TANKEN NACH 3 STUNDEN !!! ---" << std::endl;
            for (const auto& fzg_ptr : fahrzeuge) {
                PKW* pkwPtr = dynamic_cast<PKW*>(fzg_ptr.get());
                if (pkwPtr != nullptr) {
                    double getankt = pkwPtr->dTanken();
                    std::cout << pkwPtr->getName() << " getankt: " << getankt << " L." << std::endl;
                }
            }
            std::cout << "--- !!! TANKEN BEENDET !!! ---\n" << std::endl;
        }

        Fahrzeug::vKopf();

        for (const auto& fzg_ptr : fahrzeuge) {
            fzg_ptr->vSimulieren();
            std::cout << *fzg_ptr << std::endl;
        }
    }
}


// Görev 4.4.6'yı test eden fonksiyon (Operatör Testleri)
void vAufgabe_3() {
    std::cout << "\n--- 4.4.6: Operatör Testi (vAufgabe_3) ---" << std::endl;

    std::unique_ptr<PKW> pkw1 = std::make_unique<PKW>("BMW", 200.0, 8.0);
    std::unique_ptr<PKW> pkw2 = std::make_unique<PKW>("Audi", 180.0, 7.5);
    std::unique_ptr<Fahrrad> bike = std::make_unique<Fahrrad>("BMX", 35.0);

    dGlobaleZeit = 1.0;
    pkw1->vSimulieren();
    dGlobaleZeit = 2.0;
    pkw2->vSimulieren();
    dGlobaleZeit = 3.0;
    bike->vSimulieren();

    std::cout << "\n--- 1. operator<< Testi ---" << std::endl;
    Fahrzeug::vKopf();
    std::cout << *pkw1 << std::endl;
    std::cout << *pkw2 << std::endl;
    std::cout << *bike << std::endl;

    std::cout << "\n--- 2. operator< Testi (Mesafeye Göre) ---" << std::endl;
    if (*pkw1 < *pkw2) {
        std::cout << "PKW1 (BMW) mesafesi PKW2'den (Audi) küçüktür (OK). " << std::endl;
    } else {
        std::cout << "PKW1 (BMW) mesafesi PKW2'den (Audi) büyük veya eşittir (HATA). " << std::endl;
    }

    if (*bike < *pkw1) {
        std::cout << "Bike (BMX) mesafesi PKW1'den (BMW) küçüktür (OK). " << std::endl;
    } else {
        std::cout << "Bike (BMX) mesafesi PKW1'den (BMW) büyük veya eşittir (HATA). " << std::endl;
    }

    std::cout << "\n--- 3. operator= Testi (Atama) ---" << std::endl;
    PKW pkw_target("Target", 100.0, 5.0, 40.0);

    // Hata Çözümü: p_iID yerine getID() kullanıldı
    std::cout << "Target (ID: " << pkw_target.getID() << ", Önce): " << pkw_target << std::endl;

    pkw_target = *pkw1;

    // Hata Çözümü: p_iID yerine getID() kullanıldı
    std::cout << "Target (ID: " << pkw_target.getID() << ", Sonra): " << pkw_target << std::endl;
}


int main() {
    vAufgabe_1(); // Smart Pointer Testi
    vAufgabe_2(); // Kalıtım ve Tanklama Testi
    vAufgabe_3(); // Operatör Testi
    return 0;
}
