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

template <class T>
class VListe {
private:
	std::list<T> p_objekte;
	std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

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

	iterator begin() { return p_objekte.begin(); }
	iterator end() { return p_objekte.end(); }
	const_iterator begin() const { return p_objekte.begin(); }
	const_iterator end() const { return p_objekte.end(); }
	bool empty() const { return p_objekte.empty(); }
	size_t size() const { return p_objekte.size(); }

	void push_back(T obj) {
		p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj)));
	}

	void push_front(T obj) {
		p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj)));
	}

	void erase(iterator it) {
		p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte, it));
	}

	void vAktualisieren() {
		for (auto& aktion : p_aktionen) {
			aktion->vAusfuehren();
		}
		p_aktionen.clear();
	}
};

} // namespace vertagt
#endif


