/* 
 * File:   lcd.h
 * Author: Raul
 *
 * Created on 29 de julio de 2019, 03:29 AM
 */

#ifndef LCD_H
#define	LCD_H

#include <xc.h>
#include <stdlib.h>
#include <stdint.h>

/*Declarar etiquetas a los pines de la LCD*/
#define TRIS_LCD TRISD
#define LAT_LCD  PORTD



#define PIN_RS 2
#define PIN_E  3
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7

/*Declarar etiquetas para la lista de comandos para la LCD*/

#define LCD_CLEAR       0X01    //Limpiar pantalla
#define LCD_CURSOR_ON   0X0F    //Cursor Encendido ON
#define LCD_CURSOR_OFF  0X0C    //Cursor Apagado   OFF
#define LCD_LINEA1      0X02    //Primera línea
#define LCD_LINEA2      0XC0    //Segunda línea
#define LCD_LINEA3      0x94    //Tercera línea
#define LCD_LINEA4      0XD4    //Cuarta línea
#define LCD_LEFT        0X10    //Mover cursor izquierda
#define LCD_RIGHT       0X14    //Mover cursor derecha

#define ROT_LEFT        0X18    //Rotar izquierda
#define ROT_RIGHT       0X1C    //Rotar derecha

/************ Declaracion de funciones para la LCD *************/

void LCD_Inicializar(void);                    	//Inicializa LCD
void LCD_Comando(char comando);                //Envia comando

void LCD_Procesar_Dato(char dato);                 //Rutina para enviar dato
void LCD_Imprimir_Cadena(char *cadena);            //Imprime cadena de caracteres
void LCD_Imprimir_Caracter(char caracter);
void LCD_Ubicar_XY(char eje_x, char eje_y);           //Mueve cursor a un XY
void LCD_Borrar_Pantalla(void);



void LCD_integer(int);                      //Imprime un entero

void LCD_cursor(const char);             //Activa o desactiva cursor
void LCD_segunda_linea(void);

void LCD_home(void);
void LCD_custom_char(char loc, char *msg);



#endif	/* LCD_H */