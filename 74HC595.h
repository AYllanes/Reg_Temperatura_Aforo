#ifndef HC595_H
#define	HC595_H

#include <xc.h> 
#define CLK_PD LATCbits.LC2
#define DATA   LATCbits.LC1
#define CLK_SD LATCbits.LC0
unsigned char seg = 0;
void hc595_init(void);
void hc595_envia(unsigned char dato);
void hc595_reset(void);
void hc595_lcd_config(void);
void hc595_lcd_com(unsigned char data);
void hc595_lcd_borrar(void);
void hc595_lcd_w(unsigned char dato);
void hc595_lcd_mensaje(unsigned char *cadena);
void hc595_lcd_xy(const char col,const char fil);
void hc595_lcd_gencar(unsigned char *arreglo,unsigned char direccion);
#endif

