//Libraries
#include "EBYTE.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>

//Pin definitions
#define PIN_RX 16  
#define PIN_TX 17 
#define PIN_M0 27  
#define PIN_M1 26 
#define PIN_AX 25   

//Transceiver setup
#define TRANSCEIVER_CHANNEL 42
EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AX);

//WiFi login credentials
const char* ssid = "GroupA";
const char* password = "12345678";

//HTTP server URL
const char* server_name = "http://172.20.10.3:3000/mqtt";
//const char* server_name = "http://172.20.10.3:3000/database";
