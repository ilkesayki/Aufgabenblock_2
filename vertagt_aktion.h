/*
 * vertagt_aktion.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef VERTAGT_AKTION_H_
#define VERTAGT_AKTION_H_

#include <list>

namespace vertagt {

// Üst Sınıf
template <class T>
class VAktion {
protected:
	std::list<T>& p_pListe;

public:
    VAktion(std::list<T>& ptListe) : p_pListe(ptListe) {}
    virtual ~VAktion() = default;
    virtual void vAusfuehren() = 0;
};

// PushFront Aksiyonu
template <class T>
class VPushFront : public VAktion<T> {
private:
	T p_objekt;
public:
	VPushFront(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj)) {}
	virtual void vAusfuehren() override {
		this->p_pListe.push_front(std::move(p_objekt));
	}
};

// PushBack Aksiyonu
template <class T>
class VPushBack : public VAktion<T> {
private:
	T p_objekt;
public:
	VPushBack(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj)) {}
	virtual void vAusfuehren() override {
		this->p_pListe.push_back(std::move(p_objekt));
	}
};

// Erase Aksiyonu
template <class T>
class VErase : public VAktion<T> {
public:
    using iterator = typename std::list<T>::iterator;

private:
    iterator p_it;

public:
    VErase(std::list<T>& liste, iterator it) : VAktion<T>(liste), p_it(it) {}
    virtual void vAusfuehren() override {
        this->p_pListe.erase(p_it);
    }
};

} // namespace vertagt
#endif
