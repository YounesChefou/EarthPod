
#ifndef ST059_H
#define ST059_H

#include "st059.h"

#endif

DigitalOut led3(LED1);  // LD3 sur la carte
DigitalIn S(D13);     //entrée S du capteur

int detection_st059(){ //detecte les vibrations et allume la led ld3.

    int val = S.read();
     
    if (val) led3.write(1);
    
    else led3.write(0);
    
    return val;
}
