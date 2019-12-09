#include "mbed.h"
#include "MMA8451.h"
#include "st059.h"
#include "bender.h"


Timer t10sec;
Timer tNorme;
I2C i2c(D12, A6); //I2C3 
MMA8451 accelerometre(i2c, 0x1D);

Serial sigfox(D1, D0);
AnalogIn batterie(A6); // Tension au niveau de la batterie, sachant qu'on travaille en 3.3V
InterruptIn ST059(D13); 

double xAccel, yAccel, zAccel;
double bender;

int n = 0; //nombre d'itérations d'envoi de données
int nbMesures = 0;
float sommeNormes = 0.0;
float sommeBender = 0.0;

//Penser à rajouter les descriptions des fonctions en commentaire
void norme(){
    
    xAccel = accelerometre.getX();
    yAccel = accelerometre.getY();
    zAccel = accelerometre.getZ();
    bender = mesure();
     
    sommeNormes = sommeNormes + sqrt(xAccel*xAccel + yAccel*yAccel + (1-zAccel)*(1-zAccel));
    sommeBender = sommeBender + bender;
    printf("X = %.3f, Y = %.3f, Z = %.3f, Bender = %.3f\r\n", xAccel, yAccel, 1-zAccel, bender); 
    nbMesures = nbMesures + 1;
    printf("Nombre mesures = %d, Somme normes = %.3f, Somme bender = %.3f\r\n", nbMesures, sommeNormes, sommeBender);
}


// reveil est appelé si ST059.rise : cela reveil la nculéo et lance des mesures
void reveil(){
    
    printf("Reveil car st059.rise\n\r");
    t10sec.start();
    tNorme.start();
    
    accelerometre.setActiveMode();
    
    //Activer le module Wisol
    while(n <= 2){ // Defaut : 6 
        
        if(tNorme.read() >= (double)0.10){
            norme(); 
            tNorme.reset();
        }
                            
        if(t10sec.read() >= 10){       
            //Acquisition données
            int moyenneNorme = (sommeNormes/nbMesures)*1000;
            int moyenneBender = (sommeBender/nbMesures)*1000;
            
            //int niveauBatterie = batterie.read()*1000;

            printf("===========================================\r\n");
            printf("MoyenneNorme : %d, MoyenneBender : %d \r\n", moyenneNorme, moyenneBender);
            
            //Envoi données Sigfox
            printf("AT$SF=%04x%04x\r\n", moyenneNorme, moyenneBender);
            printf("===========================================\r\n");
            sigfox.printf("AT$SF=%04x%04x%04x\r\n", moyenneNorme, moyenneBender);
            
            sommeNormes = 0;
            sommeBender = 0;
            nbMesures = 0;
                        
            n++;            
            t10sec.reset();
        }
    }
    
    n = 0; 
}

int main(){
    ST059.rise(&reveil);
    sleep();
    
    while(1){
            
        //accelerometre.setStandbyMode(); //l'accelerometre est en veille lorsqu'il n'y a pas de vibrations.
        //Mettre le module Wisol en veille
        //sigfox.printf("AT$P=1")
                
        printf("Sleep1\r\n");
        sleep();   // deepsleep ne fonctionne pas
    }
    
}
