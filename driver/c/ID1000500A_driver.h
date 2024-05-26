#ifndef __ID1000500A_H__
#define __ID1000500A_H__

#include <stdint.h>

/** Global variables declaration (public) */
/* These variables must be declared "extern" to avoid repetitions. They are defined in the .c file*/
/******************************************/

/** Public functions declaration */

/* Driver initialization*/
int32_t id1000500A_init(const char *connector, uint8_t nic_addr, uint8_t port, const char *csv_file);

/* Write data*/
int32_t id1000500A_writeData(uint32_t *data, uint32_t data_size);

/* Read data*/
int32_t id1000500A_readData(uint32_t *data, uint32_t data_size);

/* Start processing*/
int32_t id1000500A_startIP(void);

/* Enable interruption notification "Done"*/
int32_t id1000500A_enableINT(void);

/* Disable interruption notification "Done"*/
int32_t id1000500A_disableINT(void);

/* Show status*/
int32_t id1000500A_status(void);

/* Wait interruption*/
int32_t id1000500A_waitINT(void);

/* Finish*/
int32_t id1000500A_finish(void);

/* Convolution processing*/
void conv(uint8_t *X, uint8_t sizeX, uint8_t *Y, uint8_t sizeY, uint16_t *result);


#endif // __ID1000500A_H__