#include "mbed.h"
#include "MMA8451.h"
#include "st059.h"
#include "bender.h"

Timer t10sec;
I2C i2c(D12, A6); //I2C3 
MMA8451 accelerometre(i2c, 0x1D);
Serial sigfox(D1, D0);
DigitalOut alimentation(D2); // pin de controle de l'alimentation : D2 = 1 <=> passant  

int xAccel, yAccel, zAccel;

int n = 0; //nombre d'itérations d'envoi de données

int main() {
   
   alimentation = 0;
    
    while(1){
            
            //accelerometre.setStandbyMode(); //l'accelerometre est en veille lorsqu'il n'y a pas de vibrations.
            //Mettre le module Wisol en veille
            //sigfox.printf("AT$P=1")
            
            if(detection_st059() == 1 && mesure_seuil() !=-1){
                printf("Vibration\r\n");
                t10sec.start(); 
                accelerometre.setActiveMode();
                //Activer le module Wisol
                while(n <= 6){
                    
                    if(t10sec.read() >= 10){
                        
                        //Acquisition données
                        xAccel = abs(accelerometre.getX())*1000;
                        yAccel = abs(accelerometre.getY())*1000;
                        zAccel = abs(accelerometre.getZ())*1000;
                        
                        printf("X = %d, Y = %d, Z = %d\r\n",xAccel, yAccel, zAccel);
                        
                        //Envoi données Sigfox
                        sigfox.printf("AT$SF=%04x%04x%04x\r\n",xAccel, yAccel, zAccel);
                        printf("AT$SF=%04x%04x%04x\r\n",xAccel, yAccel, zAccel);
                        
                        n++;
                        
                        t10sec.reset();
                    }
                }
                
                n = 0; 
            }
            
    }
    
}
