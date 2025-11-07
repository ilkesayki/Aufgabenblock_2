/*
 * main.cpp
 *
 * Created on: Nov 3, 2025
 * Author: ilkesayki
 */

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

// --- FUNCTION DECLARATIONS (PROTOTYPES) ---
void vAufgabe_1();
void vAufgabe_2();
void vAufgabe_3();
// ------------------------------------------

// Global time definition (4.2.7)
double dGlobaleZeit = 0.0;

// Task 4.2.4: Smart Pointer and Memory Management Test
void vAufgabe_1() {
    cout << "--- 4.2.4: Static, Dynamic and Smart Pointer Test ---" << endl;

    // A) Static and Dynamic Objects
    cout << "\n[A] Static and Dynamic Objects:" << endl;
    Fahrzeug f_statisch("Static_Car"); // Static object (deleted upon function exit)
    Fahrzeug* f_ptr = new Fahrzeug("Dynamic_Ptr"); // Dynamic object (requires manual delete)

    delete f_ptr; // Manual deletion

    // B) Smart Pointers
    cout << "\n[B] Smart Pointers:" << endl;

    auto up1 = make_unique<Fahrzeug>("Unique_1"); // unique_ptr (Single ownership)
    auto up2 = make_unique<Fahrzeug>("Unique_2");

    auto sp1 = make_shared<Fahrzeug>("Shared_1"); // shared_ptr (Shared ownership)

    cout << "Shared_1 Reference Count (initial): " << sp1.use_count() << endl;

    shared_ptr<Fahrzeug> sp_copy = sp1; // Copying increases use count
    cout << "Shared_1 Reference Count (after copy): " << sp1.use_count() << endl;

    // C) unique_ptr and shared_ptr Vectors

    // 1. vector<unique_ptr<Fahrzeug>>
    cout << "\n[C1] unique_ptr Vector Test:" << endl;
    vector<unique_ptr<Fahrzeug>> v_unique;

    // Moving ownership is mandatory for unique_ptr
    v_unique.push_back(std::move(up1));
    v_unique.push_back(make_unique<Fahrzeug>("Unique_In_Vector_3"));

    cout << "Vector is being cleared (v_unique.clear())..." << endl;
    v_unique.clear(); // Objects deleted here (RAII)
}


// Task 4.3.4: Inheritance, Fueling, and Polymorphism Test
void vAufgabe_2() {
    std::cout << "\n--- 4.3.4: PKW, Bicycle and Fueling Test (vAufgabe_2) ---" << std::endl;

    int anzahlPKW, anzahlFahrrad;
    std::cout << "Number of PKW (Cars): ";
    std::cin >> anzahlPKW;
    std::cout << "Number of Bicycles: ";
    std::cin >> anzahlFahrrad;

    // Polymorphism: Storing different types in a base class unique_ptr vector
    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

    // Create PKWs
    for (int i = 0; i < anzahlPKW; ++i) {
        fahrzeuge.push_back(std::make_unique<PKW>("PKW_" + std::to_string(i + 1),
                                                 150.0 + i * 10,
                                                 7.0));
    }
    // Create Bicycles
    for (int i = 0; i < anzahlFahrrad; ++i) {
        fahrzeuge.push_back(std::make_unique<Fahrrad>("Bicycle_" + std::to_string(i + 1),
                                                      30.0));
    }

    double dZeitTakt = 1.0;
    int anzahlSchritte = 15;

    const double TOLERANZ = 1e-9; // Tolerance for float comparison
    const double TANKZEIT = 3.0;

    dGlobaleZeit = 0.0; // Reset global time

    for (int schritt = 1; schritt <= anzahlSchritte; ++schritt) {
        dGlobaleZeit += dZeitTakt;

        std::cout << "\n==========================================================" << std::endl;
        std::cout << ">>> Simulation Step " << schritt << " (Global Time: " << dGlobaleZeit << "h) <<<" << std::endl;

        // --- Fueling Check (Exactly at 3 hours) ---
        // Uses std::fabs and tolerance for robust float comparison
        if (std::fabs(dGlobaleZeit - TANKZEIT) < TOLERANZ) {
            std::cout << "\n--- !!! REFUELING AFTER 3 HOURS !!! ---" << std::endl;
            for (const auto& fzg_ptr : fahrzeuge) {
                // Downcast to PKW is necessary as dTanken is not virtual in Fahrzeug
                PKW* pkwPtr = dynamic_cast<PKW*>(fzg_ptr.get());
                if (pkwPtr != nullptr) {
                    double getankt = pkwPtr->dTanken(); // Refuel completely (default)
                    std::cout << pkwPtr->getName() << " refueled: " << getankt << " L." << std::endl;
                }
            }
            std::cout << "--- !!! REFUELING FINISHED !!! ---\n" << std::endl;
        }

        Fahrzeug::vKopf(); // Output table header

        // Simulate all vehicles
        for (const auto& fzg_ptr : fahrzeuge) {
            fzg_ptr->vSimulieren();
            std::cout << *fzg_ptr << std::endl; // Uses overloaded operator<< (Polymorphism)
        }
    }
}


// Task 4.4.6: Operator Overloading Test
void vAufgabe_3() {
    std::cout << "\n--- 4.4.6: Operator Test (vAufgabe_3) ---" << endl;

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

    std::cout << "\n--- 1. operator<< Test ---" << std::endl;
    Fahrzeug::vKopf();
    std::cout << *pkw1 << std::endl;
    std::cout << *pkw2 << std::endl;
    std::cout << *bike << std::endl;

    std::cout << "\n--- 2. operator< Test (by Distance) ---" << std::endl;
    // Expected: 200 km < 360 km (True)
    if (*pkw1 < *pkw2) {
        std::cout << "PKW1 (BMW) distance is less than PKW2 (Audi) (OK). " << std::endl;
    } else {
        std::cout << "PKW1 (BMW) distance is greater than or equal to PKW2 (Audi) (ERROR). " << std::endl;
    }

    // Expected: 105 km < 200 km (True)
    if (*bike < *pkw1) {
        std::cout << "Bicycle (BMX) distance is less than PKW1 (BMW) (OK). " << std::endl;
    } else {
        std::cout << "Bicycle (BMX) distance is greater than or equal to PKW1 (BMW) (ERROR). " << std::endl;
    }

    std::cout << "\n--- 3. operator= Test (Assignment) ---" << std::endl;
    PKW pkw_target("Target", 100.0, 5.0, 40.0);

    // Access ID using the public getter
    std::cout << "Target (ID: " << pkw_target.getID() << ", Before): " << pkw_target << std::endl;

    // Assignment operation (Copies only Name/Stammdaten)
    pkw_target = *pkw1;

    // Verify Name copied, but ID/Simulation state preserved
    std::cout << "Target (ID: " << pkw_target.getID() << ", After): " << pkw_target << std::endl;
}


int main() {
    vAufgabe_1(); // Smart Pointer Test
    vAufgabe_2(); // Inheritance and Fueling Test
    vAufgabe_3(); // Operator Test
    return 0;
}
