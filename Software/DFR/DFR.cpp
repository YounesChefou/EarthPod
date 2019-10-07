#ifndef DFR_H
#define DFR_H

#include "dfr.h"

#endif

AnalogIn DFR(A0);

double lireValeursDFR() {	// //Renvoie la valeur relevée par le capteur

    return DFR.read();
}
