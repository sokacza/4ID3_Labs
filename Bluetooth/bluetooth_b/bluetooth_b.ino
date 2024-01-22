#include "bluetooth_b.h"


void setup() {
  Serial.begin(9600);
  Serial.print("\n\n------------------------\n"
    + group_name + " : " + device_name + "\n------------------------\n\n"); 

  Wire.begin();
  Wire.beginTransmission(ADDR);
  Wire.endTransmission();
  delay(300);

    bluetooth_serial.begin(group_name + " : " + device_name); 
  Serial.println("Ready for bluetooth connection!");


}


void loop() {
  //Temp sensor
  Wire.beginTransmission(ADDR);
  Wire.write(TMP_CMD);
  Wire.endTransmission();
  delay(100);

  Wire.requestFrom(ADDR, 2);

  char data[2];
  if(Wire.available() == 2){
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  
  float temp = ((data[0] * 256.0) + data[1]);
  float temp_c = ((175.72 * temp) / 65536.0) - 46.85;

  //Sample light sensor
  AsyncAPDS9306Data light_data = light_sensor.syncLuminosityMeasurement();
  
  //Calculate luminosity
  float lux = light_data.calculateLux();

//Format data as a JSON string
  String formatted_data = "{ \"" + group_name + "\": { \"" + device_name + "\": { \"Temp\": \"" + String(temp_c) + "\", \"Luminosity\": \"" + String(lux) + "\" } } }" + '\n';
      
  Serial.println(formatted_data);
  


     //Push the string characters onto the bluetooth output buffer
  for(int i = 0; i < strlen(formatted_data.c_str()) + 1; i++){
    bluetooth_serial.write(formatted_data.c_str()[i]);
  }

  Serial.println("Bluetooth sent!");

  delay(DELAY_BETWEEN_SAMPLES_MS);
}
