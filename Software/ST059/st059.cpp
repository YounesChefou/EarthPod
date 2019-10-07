
#ifndef ST059_H
#define ST059_H

#include "st059.h"

#endif

DigitalIn ST059(D3);        //entrée S du capteur

int detection_st059(){ //detecte les vibrations et allume la led ld3.

    return ST059.read();
}
