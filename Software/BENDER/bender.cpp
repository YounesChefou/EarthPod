#ifndef BENDER_H
#define BENDER_H

#include "bender.h"

#endif
//station de mesure multicapteur
AnalogIn Violet(A1);
AnalogIn Noir(A2);
Serial pc(SERIAL_TX, SERIAL_RX);

const double seuil = 1.6;

 double mesure(){
     return abs(Violet.read()-Noir.read())*20;
     }


double mesure_seuil_bender(){
    double diff = mesure();
    if(diff>=seuil){
        pc.printf(" diff= %.3f\t",diff);
        return diff;
        }
    return -1;
 }
