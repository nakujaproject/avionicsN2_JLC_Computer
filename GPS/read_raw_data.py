import io

import pynmea2
import serial

ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=5.0)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

while 1:
    try:
        line = sio.readline()
        value = line.__str__()
        print(value)
        file1 = open("gps_data.txt","a")
        file1.write(value)
        file1.close()
    except serial.SerialException as e:
        print('Device error:{}'.format(e))
        continue
    except UnicodeDecodeError as e:
        continue
