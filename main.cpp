#include "mbed.h"

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
