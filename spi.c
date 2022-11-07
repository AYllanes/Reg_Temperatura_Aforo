#include <xc.h>
#include "spi.h"
#define _XTAL_FREQ 48000000

void spi_master_init(void){
    SSPBUF = 0xFF;
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 0;
    TRISCbits.RC7 = 0;
    TRISAbits.RA5 = 0;
    SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 0;
    SSPCON1bits.CKP = 0;
    SSPCON1bits.SSPM3 = 0;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0;
    SSPCON1bits.SSPEN = 1;
    __delay_ms(50);
}
void spi_slave_init(void){
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISCbits.RC7 = 0;
    TRISAbits.RA5 = 1;
    SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 0;
    SSPCON1bits.CKP = 0;
    SSPCON1bits.SSPM3 = 0;
    SSPCON1bits.SSPM2 = 1;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0;
    SSPCON1bits.SSPEN = 1;
    __delay_ms(50);
}
void spi_write(unsigned char dato){
    PIR1bits.SSPIF = 0;
    SSPBUF = dato;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    __delay_ms(1);
}
unsigned char spi_read(void){
    SSPBUF = 0xFF;
    while(SSPSTATbits.BF == 0);
    return SSPBUF;
}