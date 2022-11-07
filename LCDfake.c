#include <xc.h>
#include <stdint.h>
#include "LCDfake.h"
#define _XTAL_FREQ 48000000

void LCD_Inicializar(void)
{
    __delay_ms(20);
    TRIS_LCD &= ~((1<<PIN_RS)|(1<<PIN_E)|(1<<PIN_D4)|(1<<PIN_D5)|(1<<PIN_D6)|(1<<PIN_D7));
    LAT_LCD &= ~((1<<PIN_RS)|(1<<PIN_E)|(1<<PIN_D4)|(1<<PIN_D5)|(1<<PIN_D6)|(1<<PIN_D7));
    
    LCD_Comando(0x02);          //Asegura el Cursos del LCD Al inicio (Home)
    LCD_Comando(0x28);          //Configura el LCD a 4 Bits, 2 Lineas Y Fuente de 5*8
    LCD_Comando(0x0C);          //LCD Prendido, Cursor Apagado, Destello Cursor apagado
    LCD_Comando(0x06);          //No rota el mensaje Y se incrementa el contador de direccion  
    LCD_Borrar_Pantalla();
}

void LCD_Comando(char comando)
{
    LAT_LCD &= ~(1<<PIN_RS);
    LCD_Procesar_Dato(comando);
}

void LCD_Procesar_Dato (char dato)
{
    if (dato & (1<<4)) LAT_LCD |=(1<<PIN_D4); else LAT_LCD &=~(1<<PIN_D4);
    if (dato & (1<<5)) LAT_LCD |=(1<<PIN_D5); else LAT_LCD &=~(1<<PIN_D5);
    if (dato & (1<<6)) LAT_LCD |=(1<<PIN_D6); else LAT_LCD &=~(1<<PIN_D6);
    if (dato & (1<<7)) LAT_LCD |=(1<<PIN_D7); else LAT_LCD &=~(1<<PIN_D7);
 
    LAT_LCD |= (1<<PIN_E);
    __delay_us(1);
    LAT_LCD &= ~(1<<PIN_E);
    
    dato = dato << 4;
    
    if (dato & (1<<4)) LAT_LCD |=(1<<PIN_D4); else LAT_LCD &=~(1<<PIN_D4);
    if (dato & (1<<5)) LAT_LCD |=(1<<PIN_D5); else LAT_LCD &=~(1<<PIN_D5);
    if (dato & (1<<6)) LAT_LCD |=(1<<PIN_D6); else LAT_LCD &=~(1<<PIN_D6);
    if (dato & (1<<7)) LAT_LCD |=(1<<PIN_D7); else LAT_LCD &=~(1<<PIN_D7);
    
    LAT_LCD |= (1<<PIN_E);
    __delay_us(1);
    LAT_LCD &= ~(1<<PIN_E);
    __delay_ms(2);
}

void LCD_Imprimir_Caracter(char caracter)
{
    LAT_LCD |= (1<<PIN_RS);
    LCD_Procesar_Dato(caracter);
}

//void putch(unsigned char dato)
//{
//    LCD_Imprimir_Caracter(dato);
//}

void LCD_Imprimir_Cadena(char *cadena)
{
    while(*cadena)
    {
        LCD_Imprimir_Caracter(*cadena);
        cadena++;
    }  
}

void LCD_Ubicar_XY(char eje_x, char eje_y)
{
    unsigned char posicion;
    
    switch(eje_y)
    {
        case 1 : posicion = 0x00 + eje_x - 1; break;
        case 2 : posicion = 0x40 + eje_x - 1; break;
        case 3 : posicion = 0x14 + eje_x - 1; break;
        case 4 : posicion = 0x54 + eje_x - 1; break;
        default: posicion = 0x00 + eje_x - 1; break;
    }
    LCD_Comando(0x80|posicion); 
}

void LCD_Borrar_Pantalla(void)
{
    LCD_Comando(LCD_CLEAR);
}

