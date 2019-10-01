#include "st059.h"

//La branche S du capteur doit être relié à la pin D3 de la nucleo

DigitalOut led3(LED1);  // LD3 sur la carte
DigitalIn S(D3);        //entrée S du capteur

int val;                // valeur temporaire de stockage des infos

void detection_st059(){ //detecte les vibrations et allume la led ld3.

    val = S.read();
     
    if (val) led3.write(1);
    
    else led3.write(0);
}
