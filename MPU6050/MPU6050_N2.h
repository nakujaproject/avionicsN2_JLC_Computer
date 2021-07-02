#include <Wire.h> /*For I2C communication*/


/*2 MPUS => 0 for one and 1 for other: depends on pin AD0 connection*/
#define REG_I2C_ADDR 0b1101000
/*power management register*/
#define POWER_REG  0x6B
/*Disable sleep mode: set sleep mode = 0*/
#define SLEEP_MODE  0b00000000  /*TODO: Disable temperature*/

/*Accelerometer configuration register*/
#define ACCEL_REG 0x1C
/*Accelerometer range +/- 2gs*/
#define ACCEL_SCALE_RANGE 0b00000000
/*LSB sensitivity per gram forces based on above range*/
#define ACCEL_LSB_SENSITIVITY 16384.0

/*Gyroscope configuration register*/
#define GYRO_REG  0x1B
/*Depends on the RPM => around 40 rpm = +/- 250degs/s*/
#define GYRO_SCALE_RANGE 0x00000000 
/*LSB sensitivity as per the above range*/
#define GYRO_LSB_SENSITIVITY 131.0
/**/
typedef struct RAW_ACCEL
{
    long accelX, accelY, accelZ;
} raw_accel;

typedef struct PROCS_ACCEL
{
    float forceX, forceY, forceZ;
} accel;

typedef struct RAW_GYRO
{
    long gyroX, gyroY, gyroZ;
} raw_gyro;

typedef struct PROCS_GRYRO
{
    float rotX, rotY, rotZ;
} gyro;


void setupMPU();

void get_raw_accel_data();
void get_processed_accel_data();

void get_raw_gyro_data();
void get_processed_gyro_data();

void printData();