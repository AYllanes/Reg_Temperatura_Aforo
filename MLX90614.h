#ifndef I2C_H
#define I2C_H
#include <xc.h>  
#define _XTAL_FREQ 48000000

float mlx90614_temp(void);
unsigned char CRC_8(unsigned long long int dato);
void mlx90614_w_eeprom(unsigned char direccion,unsigned int dato);
unsigned long int mlx90614_r_eeprom(unsigned char direccion);
unsigned long int mlx90614_r_ram(unsigned char direccion);
#endif