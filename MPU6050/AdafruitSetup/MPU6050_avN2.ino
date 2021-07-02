#include <Adafruit_MPU6050.h>

//  #include "Adafruit_MPU6050/Adafruit_MPU6050.h"

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_accel, *mpu_gyro;

void setup(){
    Serial.begin(115200); // serial baud rate 
    // 10 ms delay for boot
    while(!Serial){
        delay(10);
    }
    Serial.println("MPU6050...");
    if(!mpu.begin()){ /*MPU connection failed*/
        Serial.println("MPu connection failed");
        while(1){ delay(10); }/*Terminate*/
    }

    Serial.println("MPU found!");

    mpu_accel = mpu.getAccelerometerSensor();
    mpu_accel->printSensorDetails();

    mpu_gyro = mpu.getGyroSensor();
    mpu_gyro->printSensorDetails();
}

void loop(){
    /* Get a new normalized sensor event */
    sensors_event_t accel;
    sensors_event_t gyro;

    mpu_accel->getEvent(&accel);
    mpu_gyro->getEvent(&gyro);

    Serial.println("Accel");
    Serial.print("\t X:");Serial.print(accel.acceleration.x);Serial.print(",");
    Serial.print("\t Y:");Serial.print(accel.acceleration.y);Serial.print(",");
    Serial.print("\t Z:");Serial.print(accel.acceleration.z);Serial.print(",");

    Serial.println("Gyro");
    Serial.print("\t X:");Serial.print(gyro.gyro.x);Serial.print(",");
    Serial.print("\t Y:");Serial.print(gyro.gyro.y);Serial.print(",");
    Serial.print("\t Z:");Serial.print(gyro.gyro.z);
    Serial.println();
    delay(10);
}