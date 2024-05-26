#include <stdio.h>
#include <stdlib.h>
//#include <conio.h> // getch
#include "ID1000500A.h"

#define SIZEX 10
#define SIZEY 5
#define SIZECONF 1
#define AUX SIZEX+SIZEY-1

int main()
{
    const char *connector = "/dev/ttyACM0";
    uint8_t nic_addr = 1;
    uint8_t port = 0;
    const char *csv_file = "/home/a/Documents/HDL/ID1000500A_AlejandroPardo_LeonelGallo/config/ID1000500A_config.csv";

    if (id1000500A_init(connector, nic_addr, port, csv_file) < NULL)
	{
        printf("Failed to initialize the IP Controller.\n");
        return -1;
    }

	// Show initial ID and status
    id1000500A_status();
	
	// Data to write to MemX
	uint32_t MemX[SIZEX] = {0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000003, 0x00000007, 0x00000006, 0x0000000A, 0x00000005, 0x00000008};
	printf("Write memory: MdataX\n");
    id1000500A_writeData(MemX, SIZEX);
	
	// Data to write to MemY
    uint32_t MemY[SIZEY] = {0x00000003, 0x00000003, 0x00000005, 0x00000006, 0x00000007};
    printf("Write memory: MdataY\n");
    id1000500A_writeData(MemY, SIZEY);
	
	// Configuration register for size
    uint32_t Size[SIZECONF] = {0x000000AA};
    id1000500A_writeData(Size, SIZECONF);
    printf("Write configuration register: Csize\n");
	
	// Start IP
    printf("Start IP\n\n");
    id1000500A_startIP();
	
    // Show status after start
    id1000500A_status();
	
	// Calculate the convolution of MemX and MemY
    uint16_t conv_result[AUX];
    conv(MemX, SIZEX, MemY, SIZEY, conv_result);

    printf("Convolution result: [");
    for (int i = 0; i < AUX; i++) {
        printf("%u", conv_result[i]);
        if (i != AUX-1) {
            printf(", ");
        }
    }
    printf("]\n");

    // Finish
    id1000500A_finish();
	
	printf("\n\nPress any key to close ... ");
	
    return 0;

}