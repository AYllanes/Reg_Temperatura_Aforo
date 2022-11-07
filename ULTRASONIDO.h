#ifndef EUSART_H
#define	EUSART_H
#include <xc.h> // include processor files - each processor file is guarded. 

void ultrasonic1_init(void);
float ultrasonic1_shot(void);
void ultrasonic2_init(void);
float ultrasonic2_shot(void);
void ultrasonic3_init(void);
float ultrasonic3_shot(void);

#endif	/* XC_HEADER_TEMPLATE_H */

