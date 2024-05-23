from ipdi.ip.pyaip import pyaip, pyaip_init

import sys

try:
    connector = '/dev/ttyACM0'
    nic_addr = 1
    port = 0
    csv_file = '/home/a/Documents/HDL/ID1000500A_AlejandroPardo_LeonelGallo/config/ID1000500A_config.csv'

    aip = pyaip_init(connector, nic_addr, port, csv_file)

    aip.reset()

    #==========================================
    # Code generated with IPAccelerator 

    ID = aip.getID()
    print(f'Read ID: {ID:08X}\n')

    STATUS = aip.getStatus()
    print(f'Read STATUS: {STATUS:08X}\n')

    MemX = [0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000003, 0x00000007]

    print('Write memory: MdataX')
    aip.writeMem('MdataX', MemX, 6, 0)
    print(f'MemX Data: {[f"{x:08X}" for x in MemX]}\n')

    MemY = [0x00000003, 0x00000003, 0x00000005, 0x00000006, 0x00000007]

    print('Write memory: MdataY')
    aip.writeMem('MdataY', MemY, 5, 0)
    print(f'MemY Data: {[f"{x:08X}" for x in MemY]}\n')

    Size = [0x000000A6]

    print('Write configuration register: Csize')
    aip.writeConfReg('Csize', Size, 1, 0)
    print(f'Size Data: {[f"{x:08X}" for x in Size]}\n')

    print('Start IP\n')
    aip.start()

    STATUS = aip.getStatus()
    print(f'Read STATUS: {STATUS:08X}\n')

    print('Read memory: MdataZ')
    MemZ = aip.readMem('MdataZ', 10, 0)
    print(f'MemZ Data: {[f"{x:08X}" for x in MemZ]}\n')

    print('Clear INT: 0')
    aip.clearINT(0)

    STATUS = aip.getStatus()
    print(f'Read STATUS: {STATUS:08X}\n')

    #==========================================

    aip.finish()

except:
    e = sys.exc_info()
    print('ERROR: ', e)

    aip.finish()
    raise
