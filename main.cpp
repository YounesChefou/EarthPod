#include "mbed.h"

// screen /dev/ttyACM0 9000 -> CARTE
// screen /dev/ttyUSB0 9600 -> CONVERTISSEUR

/* 
    afficher tous les screen -> screen -ls
    attacher un screen -> screen -r numero
    quitter un screen C^a, puis \, puis y
*/ 
   
 
Serial nucleo_modem(D1,D0);

int main() {
    int i = 1;
    
    while (i < 4) {
        nucleo_modem.printf("AT$SF=%02x\r\n", i);
        i++;
        wait(5);
    }
    
    while(1);
    
}
