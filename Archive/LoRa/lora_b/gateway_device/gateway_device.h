//Libraries
#include "EBYTE.h"
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "MCP23017.h"
#include <Wire.h>

//Pin definitions
#define PIN_RX 16  
#define PIN_TX 17 
#define PIN_M0 27  
#define PIN_M1 26 
#define PIN_AX 25   

//Transceiver setup
#define TRANSCEIVER_CHANNEL 42
EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AX);

const char* group_name = "GroupA";
const char* device_name = "GatewayDevice";

//WiFi login credentials
const char* ssid = "Messi10";
const char* pass = "Spiff2187";
const char* mqtt_server = "test.mosquitto.org"; //mqtt server

WiFiClient espClient;
PubSubClient client(espClient);

#define MCP23017_ADDR 0x20
MCP23017 mcp = MCP23017(MCP23017_ADDR);
