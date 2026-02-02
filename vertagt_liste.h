/*
 * vertagt_liste.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef VERTAGT_LISTE_H_
#define VERTAGT_LISTE_H_

#include "vertagt_aktion.h"
#include <list>
#include <memory>

namespace vertagt {

template <class T> //works both for int and Fahrzeug (Generic Programing)
class VListe {
private:
	std::list<T> p_objekte; //holds vehicles
	std::list<std::unique_ptr<VAktion<T>>> p_aktionen; //holds orders (remove/add)

public:
	using iterator = typename std::list<T>::iterator;
	using const_iterator = typename std::list<T>::const_iterator;

	VListe() = default;
	~VListe() {
		vAktualisieren();
		p_objekte.clear();
	}

	void clear() {
		vAktualisieren();
		p_objekte.clear();
	}

	//act like std::list importent for Range-based for loop
	iterator begin() { return p_objekte.begin(); } 	//to change the list (vSimulation)
	iterator end() { return p_objekte.end(); }		//
	const_iterator begin() const { return p_objekte.begin(); }	// to read the list (<<operator ->const VListe&)
	const_iterator end() const { return p_objekte.end(); }		// for data security
	bool empty() const { return p_objekte.empty(); }
	size_t size() const { return p_objekte.size(); }

	void push_back(T obj) { //add given order
		p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj)));
	}

	void push_front(T obj) { //add given order
		p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj)));
	}

	void erase(iterator it) { //remove given order (iterator holds the info)
		p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte, it));
	}

	void vAktualisieren() { //do all the given orders
		for (auto& aktion : p_aktionen) {
			aktion->vAusfuehren(); //make it happen
		}
		p_aktionen.clear(); //clear the list cuz it happend
	}
};

}
#endif


