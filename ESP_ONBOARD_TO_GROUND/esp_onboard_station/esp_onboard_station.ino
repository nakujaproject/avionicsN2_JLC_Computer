// WIFI libraries
#include <WiFi.h>
#include <WebServer.h>

// MPU6050 Gyroscope libraries
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;



// WIFI credentials
const char* ssid = "iPIC-WIRELESS";
const char* password = "987654321jica";

// create web server object on port 80
WebServer server(80);

/*
 * =================================SENSORS VARIABLES=================================
 */
// mpu 6050 data
float accel_X, accel_Y, accel_Z, rot_X, rot_Y, rot_Z, temp; // todo: flight computer uses accel_Z mainly
String final_accel_data;

// struct to hold acceleration values 
struct acceleration_data{
  float accel_X, accel_Y, accel_Z;
};


/*
 * ==================================CONNECT TO WIFI====================================
 */
void init_WIFI(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting...");
    delay(1000);
  }

  // todo: use one serial print line
  Serial.print("Connected to "); Serial.print(ssid); Serial.println(); 
  Serial.print("Ip address: "); Serial.print(WiFi.localIP());
}

void init_MPU(){
  
  // initialize mpu6050
  if(!mpu.begin()){
    Serial.println("MPU6050 Not found..."); 
    while(1){
      delay(10); 
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch(mpu.getAccelerometerRange()){
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
    }

    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange()) {
      case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
      case MPU6050_RANGE_500_DEG:
        Serial.println("+- 500 deg/s");
        break;
      case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
      case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
    }

    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth()) {
      case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
      case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
      case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
      case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
      case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
      case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
      case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        break;
    }

    Serial.println("");
    delay(100);
}

/*
 * ===========================READ MPU6050========================================
 */
struct acceleration_data read_acceleration(){
  struct acceleration_data acc; // create an instance of acceleration struct
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // acceleration in x-axis
  acc.accel_X = a.acceleration.x;
  acc.accel_Y = a.acceleration.y;
  acc.accel_Z = a.acceleration.y;

  return acc;
  
}


/*
 * ====================FUNCTIONS TO HANDLE HTTP GET REQUESTS=======================
 */
void handle_on_connect(){
  server.send(200, "text/plain", "Hello client");  // put a function to read respective sensor inplace of sensor_data
  
}

void handle_data(){
  // accel values
  String accel_x = String(read_acceleration().accel_X);
  String accel_y = String(read_acceleration().accel_Y);
  String accel_z = String(read_acceleration().accel_Z);

  final_accel_data = accel_x + accel_y +  accel_z;

  // send acceleration for all axis
  //  server.send(200, "text/plain", "x: " + accel_x + ", y: " + accel_y + ", z: " + accel_z);
  server.send(200, "text/plain", final_accel_data);

}

void handle_not_found(){
  server.send(404, "text/plain", "Not Found");
}


void setup() {
  Serial.begin(115200);
  
  // consider including code to scan for WIFI strength  // include code to print the RSSI value

  // connect to WIFI
  init_WIFI();
  
  //initialize MPU6050
  init_MPU();

  // handle HTTP REQUESTS
  server.on("/", handle_on_connect);
  server.on("/getdata", handle_data);
  
  server.onNotFound(handle_not_found);

  // start server
  server.begin();
  Serial.println("\nHTTP Server started...");

}

void loop() {

  server.handleClient();


}
