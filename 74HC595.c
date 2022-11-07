#include <xc.h>
#include "74HC595.h"
#define _XTAL_FREQ 48000000

void hc595_init(void){
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    CLK_PD = 0;
    DATA = 0;
    CLK_SD = 0;
}
void hc595_envia(unsigned char dato){
    unsigned char aux = 0b10000000;
    unsigned char envio = 0;
    for(unsigned char i = 0; i<8 ; i++){
        envio = ((aux>>i) & dato)>>(7-i);
        __delay_us(5);
        DATA = envio;
        __delay_us(5);
        CLK_PD = 1;
        __delay_us(5);
        CLK_PD = 0;
        __delay_us(5);
    }
    CLK_SD = 1;
    __delay_ms(3);
    CLK_SD = 0;
}
void hc595_reset(void){
    for(unsigned char i = 0; i<8 ; i++){
        DATA = 0;
        CLK_PD = 1;
        __delay_us(5);
        CLK_PD = 0;
        __delay_us(5);
    }
    CLK_SD = 1;
    __delay_ms(30);
    CLK_SD = 0;
}
void hc595_lcd_config(void){
    hc595_reset();
    __delay_ms(30);
    hc595_lcd_com(0x30);
    __delay_ms(3);
    hc595_lcd_com(0x30);
    hc595_lcd_com(0x30);
    hc595_lcd_com(0x30);
    hc595_lcd_com(0x02);
    hc595_lcd_com(0b00101000);
    hc595_lcd_com(0b00001100);
    hc595_lcd_borrar();
    hc595_lcd_com(0x02);
    seg = 0;
}
void hc595_lcd_com(unsigned char dato){
    unsigned char NH = 0;
    unsigned char NL = 0;
    NH = (dato & 0xF0);
    NL = dato<<4;
    hc595_envia(NH);
    hc595_envia(NH|0x04);
    hc595_envia(NH);
    hc595_envia(NL);
    hc595_envia(NL|0x04);
    hc595_envia(NL);
}
void hc595_lcd_borrar(void){
    hc595_lcd_com(0x01);
    seg = 0;
}
void hc595_lcd_w(unsigned char dato){
    unsigned char NH = 0;
    unsigned char NL = 0;
    NH = (dato & 0xF0);
    NL = dato<<4;
    hc595_envia(NH);
    hc595_envia(NH|0x05);
    hc595_envia(NH|0x01); 
    
    hc595_envia(NL);
    hc595_envia(NL|0x05);
    hc595_envia(NL|0x01);  
}
void hc595_lcd_mensaje(unsigned char *cadena){
    unsigned char i = 0;
    while(cadena[i]!=0){
        hc595_lcd_w(cadena[i]);
        i++;
        seg++;
    }
}
void hc595_lcd_xy(const char col,const char fil){
    
    if(fil == 1){
        hc595_lcd_com(0x7F+col);
        seg = seg + col - 1;
    }
    else if(fil == 2){
        hc595_lcd_com(0x80+0x3F+col);
        seg = seg + 0x3F + col;
    }
    else if(fil == 3){
        hc595_lcd_com(0x80+0x13+col);
        seg = seg + 0x13 +col;
    }
    else if(fil == 4){
        hc595_lcd_com(0x80+0x53+col);
        seg = seg + 0x53 +col;
    }
}
void hc595_lcd_gencar(unsigned char *arreglo,unsigned char direccion){
    hc595_lcd_com(0x40+(direccion*8));
    for(unsigned char i = 0; i<8; i++){
        hc595_lcd_w(arreglo[i]);
    }
    hc595_lcd_com(0b10000000+seg);
}