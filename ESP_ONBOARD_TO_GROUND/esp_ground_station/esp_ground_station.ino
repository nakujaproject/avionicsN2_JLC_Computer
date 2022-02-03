#include <WiFi.h>
#include <HTTPClient.h>

// connect to same wifi network
const char* ssid = "iPIC-WIRELESS";
const char* password = "987654321jica";

// Server ip address with URL paths. Configure this for each sensor data we want to receive
const char* accel_data_from_server = "http://10.2.43.62/getdata";

String sensor_data; // convert char to string

// set up data fetch interval variables
unsigned long previousMillis = 0;
const long interval = 2000;

// function to connect to WIFI
void init_WIFI(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting...");
    delay(1000);
  }
  
  Serial.print("Connected to WiFi: ");Serial.print(ssid); Serial.println("...");
  Serial.print(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  // connect to wifi
  init_WIFI();
}

void loop() {
 unsigned long currentMillis = millis();
 if(currentMillis - previousMillis >= interval){
  
  if(WiFi.status() != WL_CONNECTED){
    // wifi not connected
    Serial.println("Wifi disconnected...");
  }else{
    // wifi connected. create HTTP request to get data
    sensor_data = request_server_data(accel_data_from_server);
    Serial.println("Acceleration: " + sensor_data);  //change this to send all required data at once
  }
 }

}

String request_server_data(const char* server_name){
  WiFiClient client;
  HTTPClient http;

  // IP address with path
  http.begin(client, server_name);

  // send HTTP POST request from server to client
  int http_response_code = http.GET();

  String payload = "N/A";

  if(http_response_code > 0){
    // Serial.print("HTTP response code:");Serial.print(http_response_code); // optional
    payload = http.getString();
  }else{
    // print error code. logging file can be done here. Send this code to python and create a logger file
    Serial.print("Error code: ");
    Serial.println(http_response_code);
  }

  // free hardware resources being used
  http.end();
  

  // return the fetched data
  return payload;
}
