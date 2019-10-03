#include "mbed.h"

AnalogIn piezo(A0);

//Affiche la valeur relevée par le capteur
void lireValeursDF(){
    printf("Valeur : %.3f\r\n", piezo.read());
}

//Affiche les valeurs relevés par le capteur Piezo 
//pendant 20 secondes
void testDFRobot(){
    int i = 0;
    
    while(1) {
        lireValeursDF();
        i++;
        wait(2);
    }
}
