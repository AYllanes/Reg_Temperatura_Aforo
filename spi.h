#ifndef SPI_H
#define SPI_H
#include <xc.h>  
#define _XTAL_FREQ 4000000
void spi_master_init(void);
void spi_slave_init(void);
void spi_write(unsigned char dato);
unsigned char spi_master_read(void);
unsigned char spi_slave_read(void);
#endif	/* XC_HEADER_TEMPLATE_H */