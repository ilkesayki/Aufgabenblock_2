/*
 * Tempolimit.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include <limits>

enum class Tempolimit { //class makes it Type Safety
    Innerorts = 50,
    Landstrasse = 100,
    Autobahn = std::numeric_limits<int>::max() // limitless
};

//converts an enum to a double
inline double getTempolimit(Tempolimit limit) {
    return static_cast<double>(limit);
}

#endif /* TEMPOLIMIT_H_ */
