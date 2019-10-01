#include "mbed.h"

AnalogIn piezo(A0);

//Lit 
void lireValeursDF(Serial pc){
    pc.printf("Valeur : %.3f\r\n", piezo.read());
}

//Renvoie les valeurs relevés par le capteur Piezo 
//pendant 20 secondes
void testDFRobot(Serial pc){
    int i = 0;
    
    while(1) {
        lireValeursDF(pc);
        i++;
        wait(2);
    }
}
