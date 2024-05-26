#include "ID1000500A_driver.h"
#include "caip.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32

//Defines
#define INT_DONE    0
#define ONE_FLIT    1
#define ZERO_OFFSET 0
#define STATUS_BITS 8
#define INT_DONE_BIT    0x00000001

/** Global variables declaration (private) */
caip_t *id1000500A_aip;
uint32_t id1000500A_id = 0;
/*********************************************************************/

/** Private function declarations */
static uint32_t id1000500A_getID(uint32_t* id);
static uint32_t id1000500A_clearStatus(void);
/*********************************************************************/

/**Functions*/

/* Driver initialization*/
int32_t id1000500A_init(const char *connector, uint8_t nic_addr, uint8_t port, const char *csv_file)
{
    id1000500A_aip = caip_init(connector, nic_addr, port, csv_file);

    if(id1000500A_aip == NULL){
        printf("CAIP Object not created");
        return -1;
    }
    id1000500A_aip->reset();

    id1000500A_getID(&id1000500A_id);
    id1000500A_clearStatus();

    printf("\nIP Controller created with IP ID: %08X\n\n", id1000500A_id);
    return 0;
}

/* Write data*/
int32_t id1000500A_writeData(uint32_t *data, uint32_t data_size)
{
	id1000500A_aip->writeMem("MdataX", data, data_size, ZERO_OFFSET);
    return 0;
}
/* Read data*/
int32_t id1000500A_readData(uint32_t *data, uint32_t data_size)
{
    id1000500A_aip->readMem("MdataZ", data, data_size, ZERO_OFFSET);
    return 0;
}

/* Start processing*/
int32_t id1000500A_startIP(void)
{
    id1000500A_aip->start();
    return 0;
}

/* Enable interruption notification "Done"*/
int32_t id1000500A_enableINT(void)
{
    id1000500A_aip->enableINT(INT_DONE, NULL);
    printf("\nINT Done enabled");
    return 0;
}

/* Disable interruption notification "Done"*/
int32_t id1000500A_disableINT(void)
{
    id1000500A_aip->disableINT(INT_DONE);
    printf("\nINT Done disabled");
    return 0;
}

/* Show status*/
int32_t id1000500A_status(void)
{
    uint32_t status;
    id1000500A_aip->getStatus(&status);
    printf("\nStatus: %08X", status);
    return 0;
}

/* Wait interruption*/
int32_t id1000500A_waitINT(void)
{
    bool waiting = true;
    uint32_t status;

    while(waiting)
    {
        id1000500A_aip->getStatus(&status);

        if((status & INT_DONE_BIT) > 0)
            waiting = false;

        #ifdef _WIN32
        Sleep(500); // ms
        #else
        sleep(0.1); // segs
        #endif
    }

    id1000500A_aip->clearINT(INT_DONE);

    return 0;
}

/* Finish*/
int32_t id1000500A_finish(void)
{
    id1000500A_aip->finish();
    return 0;
}

/* Convolution processing*/
void conv(uint8_t *X, uint8_t sizeX, uint8_t *Y, uint8_t sizeY, uint16_t *result)
{
    uint8_t result_size = sizeX + sizeY - 1;
    memset(result, 0, result_size * sizeof(uint16_t));

    for (uint8_t i = 0; i < sizeX; i++) {
        for (uint8_t j = 0; j < sizeY; j++) {
            result[i + j] += X[i] * Y[j];
        }
    }
}

/** Private functions */

/* Get ID */
uint32_t id1000500A_getID(uint32_t* id)
{
    id1000500A_aip->getID(id);
    return 0;
}

/* Clear status */
uint32_t id1000500A_clearStatus(void)
{
    for(uint8_t i = 0; i < STATUS_BITS; i++)
        id1000500A_aip->clearINT(i);

    return 0;
}
