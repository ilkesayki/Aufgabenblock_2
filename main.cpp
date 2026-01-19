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
#include "Kreuzung.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <random>

using namespace std;

// Tasks
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();
void vAufgabe_7();
// ------------------------------------------

// Global Time, declared extern in classes
double dGlobaleZeit = 0.0;

// Smart Pointer and Memory Management Test
void vAufgabe_1a() {
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
    std::cout << "\n--- 4. Task: Weg & Listen Test ---" << std::endl;

    Weg w1("B54", 50.0, Tempolimit::Innerorts);

    auto p1 = std::make_unique<PKW>("BMW", 120, 8.5);
    auto p2 = std::make_unique<Fahrrad>("BMX", 25);

    // Araçları yola ekle (Şu an kuyrukta bekliyorlar)
    w1.vAnnahme(std::move(p1));
    w1.vAnnahme(std::move(p2));

    // --- DÜZELTME BURADA ---
    // Listeyi güncellemek için simülasyonu bir kez tetikliyoruz.
    // Bu işlem, bekleme kuyruğundaki 'push_back' emirlerini gerçekleştirir.
    w1.vSimulieren();
    // -----------------------

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

void vAufgabe_6a() {
    using namespace vertagt;

    std::cout << ">>> vAufgabe_6a: VListe Testi (Tamsayilar ile) <<<" << std::endl;

    // 1. Liste oluştur ve Rastgele Sayılarla Doldur
    VListe<int> liste;
    static std::mt19937 device(0);
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < 10; ++i) {
        liste.push_back(dist(device));
    }

    // --- DÜZELTME BURADA ---
    // Sayıların listeye girmesi için GÜNCELLEME yapıyoruz
    liste.vAktualisieren();
    // -----------------------

    // 2. Listeyi Yazdır
    std::cout << "Liste (Ilk Hali): ";
    for (auto& sayi : liste) {
        std::cout << sayi << " ";
    }
    std::cout << std::endl;

    // 3. 5'ten büyük sayıları sil (erase komutu ver)
    for (auto it = liste.begin(); it != liste.end(); ++it) {
        if (*it > 5) {
            liste.erase(it);
        }
    }

    // 4. Listeyi Tekrar Yazdır (Değişiklik olMAMAlı, çünkü güncellemedik)
    std::cout << "Liste (Aktualisieren oncesi - Silinmedi): ";
    for (auto& sayi : liste) {
        std::cout << sayi << " ";
    }
    std::cout << std::endl;

    // 5. Listeyi Güncelle (Şimdi silinmeli)
    liste.vAktualisieren();

    // 6. Sonuç
    std::cout << "Liste (Aktualisieren sonrasi - >5 Silindi): ";
    for (auto& sayi : liste) {
        std::cout << sayi << " ";
    }
    std::cout << std::endl;

    // 7. Başa ve Sona ekle
    liste.push_front(99);
    liste.push_back(100);
    liste.vAktualisieren();

    std::cout << "Liste (99 ve 100 eklendi): ";
    for (auto& sayi : liste) {
        std::cout << sayi << " ";
    }
    std::cout << std::endl;
}

void vAufgabe_7() {
    // 1. Grafik Başlat
    bInitialisiereGrafik(1000, 600); // Pencereyi biraz büyüttük

    // 2. Kavşakları Oluştur
    // Kr2'de benzin istasyonu var (1000 Litre)
    auto Kr1 = std::make_shared<Kreuzung>("Kr1");
    auto Kr2 = std::make_shared<Kreuzung>("Kr2", 1000.0);
    auto Kr3 = std::make_shared<Kreuzung>("Kr3");
    auto Kr4 = std::make_shared<Kreuzung>("Kr4");

    // Kavşakları Çiz (Koordinatlar PDF Fig 5.4'e göre yaklaşık değerler)
    bZeichneKreuzung(680, 40);  // Kr1
    bZeichneKreuzung(680, 300); // Kr2
    bZeichneKreuzung(680, 570); // Kr3
    bZeichneKreuzung(320, 300); // Kr4

    // 3. Yolları Bağla (Strassen)
    // Parametreler: (K1, K2, IsimHin, IsimRueck, Uzunluk, SollamaYasagi, HızLimiti)

    // Strasse 1 (Kr1 <-> Kr2): 40km, Innerorts
    Kreuzung::vVerbinde(Kr1, Kr2, "W12", "W21", 40.0, true, Tempolimit::Innerorts);
    int k1[] = {680, 40, 680, 300};
    bZeichneStrasse("W12", "W21", 40, 2, k1);

    // Strasse 2 (Kr2 <-> Kr3): 115km, Landstrasse
    Kreuzung::vVerbinde(Kr2, Kr3, "W23a", "W32a", 115.0, false, Tempolimit::Landstrasse);
    int k2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570}; // Kıvrımlı yol
    bZeichneStrasse("W23a", "W32a", 115, 6, k2);

    // Strasse 3 (Kr2 <-> Kr3 düz): 40km, Innerorts
    Kreuzung::vVerbinde(Kr2, Kr3, "W23b", "W32b", 40.0, true, Tempolimit::Innerorts);
    int k3[] = {680, 300, 680, 570};
    bZeichneStrasse("W23b", "W32b", 40, 2, k3);

    // Strasse 4 (Kr2 <-> Kr4): 55km, Innerorts
    Kreuzung::vVerbinde(Kr2, Kr4, "W24", "W42", 55.0, true, Tempolimit::Innerorts);
    int k4[] = {680, 300, 320, 300};
    bZeichneStrasse("W24", "W42", 55, 2, k4);

    // Strasse 5 (Kr3 <-> Kr4): 85km, Landstrasse
    Kreuzung::vVerbinde(Kr3, Kr4, "W34", "W43", 85.0, false, Tempolimit::Landstrasse);
    int k5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
    bZeichneStrasse("W34", "W43", 85, 5, k5);

    // Strasse 6 (Kr4 <-> Kr4 Loop): 130km, Landstrasse
    // Kendi kendine dönen yol biraz özeldir, grafikte hata verirse burayı yorum satırına alabilirsin.
    // Ancak mantıken bir kavşağı kendine bağlayabiliriz.
    Kreuzung::vVerbinde(Kr4, Kr4, "W44a", "W44b", 130.0, false, Tempolimit::Landstrasse);
    int k6[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300};
    bZeichneStrasse("W44a", "W44b", 130, 7, k6);


    // 4. Araçları Oluştur ve Yerleştir
    auto p1 = std::make_unique<PKW>("BMW", 120, 8.5);
    auto p2 = std::make_unique<Fahrrad>("BMX", 25);
    auto p3 = std::make_unique<PKW>("Audi", 150, 9.0);

    // Araçları Kr1'e veriyoruz, o uygun bir yola koyacak
    Kr1->vAnnahme(std::move(p1), 0.5); // 0.5 saat sonra kalksın
    Kr1->vAnnahme(std::move(p2), 0.0);
    Kr1->vAnnahme(std::move(p3), 1.0);


    // 5. Simülasyon Döngüsü
    dGlobaleZeit = 0.0;
    for (int i = 0; i < 500; ++i) { // Uzun süreli simülasyon
        dGlobaleZeit += 0.2;
        vSetzeZeit(dGlobaleZeit);

        // Tüm kavşakları simüle et (Kavşaklar da yollarını simüle eder)
        Kr1->vSimulieren();
        Kr2->vSimulieren();
        Kr3->vSimulieren();
        Kr4->vSimulieren();

        // Çizim (Weg::vZeichnen'e nullptr kontrolü eklediğin için sorun olmaz)
        // SimuClient her şeyi otomatik çizmez, yolları tek tek çizdirmemiz lazım
        // Ama biz yolları Kreuzung içinde tutuyoruz.
        // Basitlik adına Kreuzung içine vZeichnen ekleyebilirsin veya burada manuel çizebilirsin.
        // Hızlı çözüm: Kreuzung'un vSimulieren'i içinde yolların vSimulieren'i çağrılıyor.
        // Yolların vSimulieren'i içinde de vZeichnen çağrılıyor (Weg.cpp'deki kodunda var mı?).
        // Eğer Weg::vSimulieren içinde fzg->vZeichnen(*this) varsa otomatik çizilir.

        vSleep(50);
    }
    vBeendeGrafik();
}

int main() {
    int iAuswahl;

    while (true) {
        // Menü Yazıları
        std::cout << "\n\n==============================================" << std::endl;
        std::cout << "VERKEHRSSIMULATION - HAUPTMENU" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "1. vAufgabe_1a() : Statisch, Dynamisch & Smart Pointers" << std::endl;
        std::cout << "2. vAufgabe_2() : Fahrzeuge, PKW & Fahrrad (Eingabe)" << std::endl;
        std::cout << "3. vAufgabe_3() : Operator Overloading" << std::endl;
        std::cout << "4. vAufgabe_4() : Weg & Listen" << std::endl;
        std::cout << "5. vAufgabe_5() : Verhalten (Parken & Fahren)" << std::endl;
        std::cout << "6. vAufgabe_6() : Grafik & Exceptions" << std::endl;
        std::cout << "7. vAufgabe_6a() : VListe Testi (Int)" << std::endl;
        std::cout << "8. vAufgabe_7() : Verkehrsnetz (Kreuzungen & Grafik)" << std::endl;
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
                vAufgabe_1a();
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
            case 7:
            	vAufgabe_6a();
            	break;
            case 8:
                std::cout << ">>> Grafik: Netzwerk-Simulation <<<" << std::endl;
                vAufgabe_7();
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
