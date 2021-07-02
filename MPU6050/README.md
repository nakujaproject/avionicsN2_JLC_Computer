# MPU6050
This is a 6-axis motion tracking device
* 3-axis gyroscope
* 3-axis accelerometer

Also has

**IMPORTANT** : DMP(Digital Motion processor)
- It is a 16-bit ADC. 
- It accurately reads the change in voltage due to the variation of the fundamental mechanical system
- Stores it in a FIFO buffer.
- turn the interrupt HIGH - This means data is ready to be read from the FIFO buffer.


Operating voltage = 3.3V (has a voltage regulator)

### Pinout diagram

[!Oops Pin out diagram](https://github.com/EricoDeMecha/avionicsv2/MPU6050/images/MPU6050-Pinout.png)

*XDA*  and *XCL* allows for interfacing with other I2C modules
### Possible outputs

1. Quaternion Components [w,x,y,z]
2. Euler angles
3. Yaw,Pitch, and Roll
4. Real world acceleration
5. World Frame Acceleration
6. Tealpot Invent sense values

### Important 

* *Yaw* 
* *Pitch*
* *Roll*

## Code

### Nakuja2 MPU6050 
#### Datasheet

MPU6050 from TDK makers

[MPU6050 Datasheet from TDK makers](https://www.alldatasheet.com/datasheet-pdf/pdf/1132807/TDK/MPU-6050.html)

#### Source code

- [MPU6050_N2.h](https://github.com/EricoDeMecha/avionicsv2/MPU6050/MPU6050_N2.h)

- [MPU6050_N2.cpp](https://github.com/EricoDeMecha/avionicsv2/MPU6050/MPU6050_N2.cpp)

- get raw accelerometer and gyroscope data  using the get_raw_* functions. For configuration, edit define MACROs.
- get processed data based on the default configurations(Accelerometer range +/- 2gs, Gyroscope range  +/- 250degs/s) using the functions get_processed_*

#### Usage

[example.ino](https://github.com/EricoDeMecha/avionicsv2/MPU6050/example.ino) shows how to use the header files


__***Incase hell break loose, go for adafruit setup below***__

### Adafruit MPU6050
Adafruit MPU6050 depends on 
[Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor) ,and [Adafruit BUS IO library](https://github.com/adafruit/Adafruit_BusIO) 

### Local Setup

**Note**  Arduino local setups might vary. Find your arduino ***include directory*** before doing the following...

- Clone the repo to your local machine
- Add all these Adafruit_* directories to your ***include directory*** 
- Move  "MPU6050_avN2.ino" sketch your development  directory
- Open the sketch from your development environment
- Do your MPU6050 thing...

## Progress

- [x] Basic interfacing of MPU6050 with arduino || esp

- [x] Roll, Pitch and Yaw in relation to angle of attack.

- [ ] More...

## Issues

- [ ] MPU6050_N2  begin (Checking for existense of MPU6050 in the connection circuit)
- [ ] Disabling temperature in the MPU define MACRO below to save on power
```cpp
#define REG_I2C_ADDR 0b1101000
``` 