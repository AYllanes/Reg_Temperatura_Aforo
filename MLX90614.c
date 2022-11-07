#include <xc.h>
#include "MLX90614.h"
#define _XTAL_FREQ 48000000
void i2c_master_init(void){
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    SSPSTATbits.SMP = 1;
    SSPSTATbits.CKE = 0;
    SSPCON1bits.SSPEN = 1;
    SSPCON1bits.SSPM = 8;
    SSPADD = 119;                    // Para una frecuancia de 48 MHz
}
void i2c_slave_init(void){
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    SSPSTATbits.SMP = 1;
    SSPSTATbits.CKE = 0;
    SSPCON1bits.SSPEN = 1;
    SSPCON1bits.SSPM = 6;
    SSPADD = 2;    
}
void i2c_star(void){
    SSPCON2bits.SEN = 1;
    while(SSPCON2bits.SEN == 1);
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
}
void i2c_stop(void){
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN == 1);
}
void i2c_master_tx(unsigned char dato){
    PIR1bits.SSPIF = 0;
    SSPBUF = dato;
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
}
unsigned char i2c_master_rx(const char fn){
    SSPCON2bits.ACKDT = 0;
    unsigned char dato;
    PIR1bits.SSPIF = 0;
    SSPCON2bits.RCEN = 1;
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
    dato = SSPBUF;
    if(fn==1){
        SSPCON2bits.ACKDT = 1;
    }
    SSPCON2bits.ACKEN = 1;
    while(SSPCON2bits.ACKEN == 1);
    PIR1bits.SSPIF = 0;
    return (dato);
}
void i2c_slave_tx(unsigned char dato){
    while(SSPCON1bits.CKP==1);
    SSPBUF = dato;
    SSPCON1bits.CKP = 1;
    PIR1bits.SSPIF = 0;
}
unsigned char i2c_slave_rx(void){
    unsigned char dato;
    while(PIR1bits.SSPIF == 0);
    PIR1bits.SSPIF = 0;
    if(SSPSTATbits.DA==1){
        dato = SSPBUF;
    }
    return (dato);
}


float mlx90614_temp(void){
    unsigned char dato;
    unsigned char dato2;
    unsigned char dato3;
    unsigned int buffer;
    float temp;
    i2c_master_init();
    i2c_star();
    i2c_master_tx(0xB4);
    i2c_master_tx(0x07);
    i2c_star();
    i2c_master_tx(0xB5);
    dato = i2c_master_rx(0);
    dato2 = i2c_master_rx(0);
    dato3 = i2c_master_rx(1);
    i2c_stop();
    __delay_ms(20);
    buffer = (dato2<<8)|dato;
    temp = ((buffer*0.02)-273.15);
    return temp;
}
void mlx90614_w_eeprom(unsigned char direccion,unsigned int dato){
    unsigned char comando;
    unsigned char lsb;
    unsigned char msb;
    unsigned long long int solpec;
    unsigned long long int solpec2;
    comando = 0x20|direccion;
    lsb = dato;
    msb = dato>>8;
    solpec = (0xB4<<8)|comando;
    solpec = (solpec<<8)|lsb;
    solpec = (solpec<<8)|msb;
    
    solpec2 = (0xB4<<8)|comando;
    solpec2 = (solpec2<<8)|0x00;
    solpec2 = (solpec2<<8)|0x00;    
    
    i2c_master_init();
    i2c_star();
    i2c_master_tx(0xB4);
    i2c_master_tx(comando);
    i2c_master_tx(0x00);
    i2c_master_tx(0x00);
    i2c_master_tx(CRC_8(solpec2));
    i2c_stop();
    __delay_ms(11);
    i2c_star();
    i2c_master_tx(0xB4);
    i2c_master_tx(comando);
    i2c_master_tx(lsb);
    i2c_master_tx(msb);
    i2c_master_tx(CRC_8(solpec));
    i2c_stop();
    __delay_ms(11);
}
unsigned long int mlx90614_r_eeprom(unsigned char direccion){
    unsigned char comando;
    unsigned long int dato;
    comando = 0x20|direccion;
    i2c_master_init();
    i2c_star();
    i2c_master_tx(0xB4);
    i2c_master_tx(comando);
    i2c_star();
    i2c_master_tx(0xB5);
    dato = i2c_master_rx(0);
    dato = (dato<<8)|i2c_master_rx(0);
    dato = (dato<<8)|i2c_master_rx(1);
    i2c_stop();
    return dato;

}
unsigned long int mlx90614_r_ram(unsigned char direccion){
    unsigned long int dato;
    i2c_master_init();
    i2c_star();
    i2c_master_tx(0xB4);
    i2c_master_tx(direccion);
    i2c_star();
    i2c_master_tx(0xB5);
    dato = i2c_master_rx(0);
    dato = (dato<<8)|i2c_master_rx(0);
    dato = (dato<<8)|i2c_master_rx(1);
    i2c_stop();
    return dato;    
}

unsigned char CRC_8(unsigned long long int dato){
    unsigned long long int busq = 0;
    unsigned long long int polinomio_crc8 = 0x107;
    unsigned long long int aux = 0b1000000000000000000000000000000000000000000000000000000000000000;
    signed char i = 0;
    dato = dato<<8;
    while(1){
        busq = dato & (aux>>i);
        if(busq != 0){
            dato = dato ^((polinomio_crc8<<64-9)>>i);
            if(dato<256){
                return dato;
            }
        }
        i++;
    }
}