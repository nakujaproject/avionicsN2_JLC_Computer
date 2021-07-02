#include "MPU6050_N2.h"

void setup(){
    Serial.begin(9600);
    Wire.begin();
    setupMPU();
}
void loop(){
    get_raw_accel_data();
    get_processed_accel_data();
    get_raw_gyro_data();
    get_processed_gyro_data();
    printData();
    delay(100);
}