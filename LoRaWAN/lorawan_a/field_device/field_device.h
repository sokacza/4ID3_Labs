// Libraries
#include <TheThingsNetwork.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//  Macros
#define DHTPIN 2
#define DHTTYPE DHT11
#define POLLING_PERIOD 2000
#define GROUP_NAME "GroupA"
#define DEVICE_NAME "DeviceA"

DHT_Unified dht(DHTPIN, DHTTYPE);
#define lora_serial Serial1
#define debug_serial Serial

// Set your AppEUI and AppKey
#define FREQUENCY_PLAN TTN_FP_US915
const char *app_eui = "0000000000000000";
const char *app_key = "663B77ED67BA88F79DCF95D770D49350";
TheThingsNetwork ttn(lora_serial, debug_serial, FREQUENCY_PLAN);

unsigned long start_time = millis();
