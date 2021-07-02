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

- [ ] Roll, Pitch and Yaw in relation to angle of attack.

- [ ] More...