#include <xc.h>
#include "ULTRASONIDO.h"
#define _XTAL_FREQ 48000000
/////////////////////////////////
//void EUSAR_config(void){
//    TRISCbits.RC6=0;    //RC6 salida como TX
//    SPBRG=77;           //9600 TX
//    RCSTAbits.SPEN=1;   //ACTIVAR PUERTO SERIAL
//    RCSTAbits.CREN=1;   //ACTIVAR EL RECEPTOR
//    TXSTAbits.TXEN=1;   //ACTIVAR EL TRANSMISOR
//}
//void SERIAL_newline(void){
//    TXREG = 0x0A;               //ESPACIO HACIA ABAJO
//    while(TXSTAbits.TRMT==0);   //YA TERMINASTE?
//    TXREG=0x0D;                 //RETORNO DEL CARRO
//    while(TXSTAbits.TRMT==0);   //YA TERMINASTE?
//}
//void SERIAL_escribe(const unsigned char *vector){
//    unsigned int cantidad=0;
//    unsigned char x;
//    cantidad=strlen(vector);
//    for (x=0;x<cantidad;x++){
//        TXREG=vector[x];            // TXREG ENVIA EL MENSAJE
//        while(TXSTAbits.TRMT==0);   //YA TERMINASTE DE ENVIAR?
//    }
//}
////////////////////////////////
/*
void eusart_init(void){
    SPBRG = 51; //51
    TXSTAbits.BRGH = 1;
    RCSTAbits.SPEN = 1;
}
void eusart_tx_com(unsigned char dato){
    TXSTAbits.TXEN = 1;
    TXREG = dato;
    while(TXSTAbits.TRMT == 0);
    TXSTAbits.TXEN = 0;
}
void eusart_tx(unsigned char *dato){
    unsigned char i=0;
    TXSTAbits.TXEN = 1;
    while(dato[i]!=0){
        TXREG = dato[i];
        while(TXSTAbits.TRMT == 0);
        i++;
    }
    TXSTAbits.TXEN = 0;
}

unsigned char eusart_rx(void){
    PIR1bits.RCIF = 0;
    RCSTAbits.CREN = 1;
    while(PIR1bits.RCIF == 0);
    PIR1bits.RCIF = 0;
    RCSTAbits.CREN = 0;
    return RCREG;
}
*/
void ultrasonic1_init(void){
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 0;      // Asignamos el nombre "Pin_Echo" salida
    LATAbits.LA1 = 0;       // Asignamos el nombre "Pin_Trig" entrada
    __delay_us(50);
}
float ultrasonic1_shot(void){
    unsigned long int tiempo = 0;
    float distancia;
    LATAbits.LA1 = 1;
    __delay_us(10);
    LATAbits.LA1 = 0;
    while(PORTAbits.RA0 == 0);
    while(PORTAbits.RA0 == 1){
        tiempo++;
    }
    distancia = tiempo*0.9*0.0343/2;
    __delay_ms(100);
    return distancia;
}
void ultrasonic2_init(void){
    TRISAbits.RA2 = 1;
    TRISAbits.RA3 = 0;
    LATAbits.LA3 = 0;
    __delay_us(50);
}
float ultrasonic2_shot(void){
    unsigned long int tiempo = 0;
    float distancia;
    LATAbits.LA3 = 1;
    __delay_us(10);
    LATAbits.LA3 = 0;
    while(PORTAbits.RA2 == 0);
    while(PORTAbits.RA2 == 1){
        tiempo++;
    }
    distancia = tiempo*0.9*0.0343/2;
    __delay_ms(100);
    return distancia;
}
void ultrasonic3_init(void){
    TRISAbits.RA4 = 1;
    TRISAbits.RA5 = 0;
    LATAbits.LA5 = 0;
    __delay_us(50);
}
float ultrasonic3_shot(void){
    unsigned long int tiempo = 0;
    float distancia;
    LATAbits.LA5 = 1;
    __delay_us(10);
    LATAbits.LA5 = 0;
    while(PORTAbits.RA4 == 0);
    while(PORTAbits.RA4 == 1){
        tiempo++;
    }
    distancia = tiempo*0.9*0.0343/2;
    __delay_ms(100);
    return distancia;
}