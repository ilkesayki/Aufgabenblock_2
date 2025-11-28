/*
 * Tempolimit.h
 *
 *  Created on: Nov 28, 2025
 *      Author: ilkesayki
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include <limits>

enum class Tempolimit {
    Innerorts = 50,
    Landstrasse = 100,
    Autobahn = std::numeric_limits<int>::max() // Limitsiz
};

// Enum'ı double'a çeviren yardımcı fonksiyon
inline double getTempolimit(Tempolimit limit) {
    return static_cast<double>(limit);
}

#endif /* TEMPOLIMIT_H_ */
