//Libraries
#include <Arduino.h>
#include <Wire.h>
#include <AsyncAPDS9306.h>
//IIC Addresses for Temperature Sensor
#define ADDR (byte)(0x40)
#define TMP_CMD (byte)(0xF3)

//Sample frequency
#define DELAY_BETWEEN_SAMPLES_MS 5000

//Device information
String group_name = "GroupA";
String device_name = "DeviceA";

//Instantiating sensor object and configuration
AsyncAPDS9306 light_sensor;
const APDS9306_ALS_GAIN_t gain = APDS9306_ALS_GAIN_1;
const APDS9306_ALS_MEAS_RES_t time = APDS9306_ALS_MEAS_RES_16BIT_25MS;