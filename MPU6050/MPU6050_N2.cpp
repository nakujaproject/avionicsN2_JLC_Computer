#include "MPU6050_N2.h"

void setupMPU(){
    /* Setup the power mode */

    Wire.beginTransmission(REG_I2C_ADDR);
    Wire.write(POWER_REG);
    Wire.write(SLEEP_MODE);
    Wire.endTransmission();

    /* Setup the gyroscope */
    Wire.beginTransmission(REG_I2C_ADDR);
    Wire.write(GYRO_REG);
    Wire.write(GYRO_SCALE_RANGE);
    Wire.endTransmission();

    /* Setup the accelerometer */

    Wire.beginTransmission(REG_I2C_ADDR);
    Wire.write(ACCEL_REG);
    Wire.write(ACCEL_SCALE_RANGE);
    Wire.endTransmission();
}

void get_raw_accel_data(){
    Wire.beginTransmission(REG_I2C_ADDR);
    Wire.write(0x3B); // starting register for accelerometer readings
    Wire.endTransmission();
    Wire.requestFrom(REG_I2C_ADDR,6); //Request Accel Registers (3B - 40)
    while(Wire.available() < 6);
    raw_accel.accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
    raw_accel.accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
    raw_accel.accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
}
void get_processed_accel_data(){
    accel.forceX = raw_accel.accelX / ACCEL_LSB_SENSITIVITY;
    accel.forceY = raw_accel.accelY / ACCEL_LSB_SENSITIVITY; 
    accel.forceZ = raw_accel.accelZ / ACCEL_LSB_SENSITIVITY;
}

void get_raw_gyro_data(){
    Wire.beginTransmission(REG_I2C_ADDR);
    Wire.write(0x43); //Starting register for Gyroscope readings
    Wire.endTransmission();
    Wire.requestFrom(REG_I2C_ADDR,6); //Request Gyro Registers (43 - 48)
    while(Wire.available() < 6);
    raw_gyro.gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
    raw_gyro.gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
    raw_gyro.gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
}
void get_processed_gyro_data(){
    gyro.rotX = raw_gyro.gyroX / GYRO_LSB_SENSITIVITY;
    gyro.rotY = raw_gyro.gyroY / GYRO_LSB_SENSITIVITY; 
    gyro.rotZ = raw_gyro.gyroZ / GYRO_LSB_SENSITIVITY;
}

void printData(){
    Serial.println("Gyro");
    Serial.print("\t P:");Serial.print(gyro.x);Serial.print(",");
    Serial.print("\t R:");Serial.print(gyro.y);Serial.print(",");
    Serial.print("\t Y:");Serial.print(gyro.z);
    Serial.println();

    Serial.println("Accel");
    Serial.print("\t X:");Serial.print(accel.x);Serial.print(",");
    Serial.print("\t Y:");Serial.print(accel.y);Serial.print(",");
    Serial.print("\t Z:");Serial.print(accel.z);Serial.print(",");
}