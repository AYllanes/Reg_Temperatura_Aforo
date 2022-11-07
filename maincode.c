#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "conio.h"
#include "MLX90614.h"
#include "LCD.h"
#include "ULTRASONIDO.h"
#include "cabecera.h"
#define CPUCLOCK 48000000
#define _XTAL_FREQ CPUCLOCK
#define ROJO LATEbits.LE0
#define VERDE LATEbits.LE1
#define BUZZER LATEbits.LE2

unsigned char buffer[20];
unsigned char buffer_d[20];
float t = 0.0;
unsigned int buffer2;
unsigned char high;
unsigned char low;
unsigned char distancia;
float d = 0.0;
unsigned long long int dato;
unsigned char grados[] = {7,5,7,0,0,0,0,0};
unsigned char TEMP[]={"La temperatura que tiene es:"};
unsigned char M1[]={"Por favor cuide su salud no puede ingresar"};
unsigned char M2[]={"Excelente puedes ingresar"};
unsigned char TEMP_ALTA[]={"TEMPERATURA ALTA!!!  Sobrepasa a 37.5 grados C"};
unsigned char TEMP_BAJA[]={"Temperatura correcta :)"};

void EUSAR_config(void){
    TRISCbits.RC6=0;    //RC6 salida como TX
    SPBRG=12;           //57600 TX
    RCSTAbits.SPEN=1;   //ACTIVAR PUERTO SERIAL
    RCSTAbits.CREN=1;   //ACTIVAR EL RECEPTOR
    TXSTAbits.TXEN=1;   //ACTIVAR EL TRANSMISOR
}
void SERIAL_newline(void){
    TXREG = 0x0A;               //ESPACIO HACIA ABAJO
    while(TXSTAbits.TRMT==0);   //YA TERMINASTE?
    TXREG=0x0D;                 //RETORNO DEL CARRO
    while(TXSTAbits.TRMT==0);   //YA TERMINASTE?
}
void SERIAL_escribe(const unsigned char *vector){
    unsigned int cantidad=0;
    unsigned char x;
    cantidad=strlen(vector);
    for (x=0;x<cantidad;x++){
        TXREG=vector[x];            // TXREG ENVIA EL MENSAJE
        while(TXSTAbits.TRMT==0);   //YA TERMINASTE DE ENVIAR?
    }
}

void main(void) {
    EUSAR_config();
    ADCON1 = 15;
    __delay_ms(100);
    TRISD = 0;
    TRISE = 0;
    LATE = 0;
    LCD_CONFIG();
    CURSOR_ONOFF(OFF);
    BORRAR_LCD();
    CURSOR_HOME();
    EUSAR_config();
    ultrasonic1_init();
    GENERACARACTER(grados,5);

    while(1){
        d = 6;
        while(d>4){
            d = ultrasonic1_shot();
            POS_CURSOR(1,1);
            ESCRIBE_MENSAJE("Por favor camine");
            POS_CURSOR(2,1);
            ESCRIBE_MENSAJE("hacia el logo");
            POS_CURSOR(3,1);
            ESCRIBE_MENSAJE("y acerque su frente");
            POS_CURSOR(4,1);
            ESCRIBE_MENSAJE("Distancia: ");
            sprintf(buffer_d,"%.2f",d);
            ESCRIBE_MENSAJE(buffer_d);
            ESCRIBE_MENSAJE(" cm.");
        }
            
            t = mlx90614_temp();
            //t = 40;
            BUZZER = 1;
            __delay_ms(200);
            BORRAR_LCD();
            CURSOR_HOME();
            ESCRIBE_MENSAJE("Distancia correcta");
            POS_CURSOR(3,1);
            ESCRIBE_MENSAJE("Distancia: 4cm");
            BUZZER = 0;
            __delay_ms(3000);
            LCD_CONFIG();
            CURSOR_ONOFF(OFF);
            BORRAR_LCD();
            CURSOR_HOME();
            ultrasonic1_init();      
            GENERACARACTER(grados,5);
            ESCRIBE_MENSAJE("Temperatura: ");
            sprintf(buffer,"%.2f",t);
            POS_CURSOR(2,1);
            ESCRIBE_MENSAJE(buffer);
            ENVIA_CHAR(5);
            ESCRIBE_MENSAJE("C");
            POS_CURSOR(3,1);
            ESCRIBE_MENSAJE("Temperatura");
            if(t>37.5){
                SERIAL_escribe(TEMP_ALTA);
                SERIAL_newline();
                sprintf(buffer,"%.2f",t);
                SERIAL_escribe(TEMP);
                SERIAL_escribe(buffer);
                SERIAL_newline();
                SERIAL_escribe(M1);
                SERIAL_newline();
                

                ESCRIBE_MENSAJE(" Alta");
                POS_CURSOR(4,1);
                ESCRIBE_MENSAJE("No puede pasar! :C");
                ROJO = 1;
                BUZZER = 1;
            }
            else{
                SERIAL_escribe(TEMP_BAJA);
                SERIAL_newline();
                sprintf(buffer,"%.2f",t);
                SERIAL_escribe(TEMP);
                SERIAL_escribe(buffer);
                SERIAL_newline();
                SERIAL_escribe(M2);
                SERIAL_newline();
                
                
                ESCRIBE_MENSAJE(" Normal ");
                POS_CURSOR(4,1);
                ESCRIBE_MENSAJE("Puede pasar :D");
                VERDE = 1;
            }
            __delay_ms(3000);
            BORRAR_LCD();
            VERDE = 0;
            ROJO = 0;
            BUZZER = 0;
            __delay_ms(100);
            LCD_CONFIG();
            CURSOR_ONOFF(OFF);
            BORRAR_LCD();
            CURSOR_HOME();
            ultrasonic1_init();
            GENERACARACTER(grados,5);
    }
    return;
}


