#include "field_Device.h"

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n------------------------\n"
    + group_name + " : " + device_name + "\n------------------------\n\n"); 
  
  Wire.begin();
  Wire.beginTransmission(ADDR);
  Wire.endTransmission();
  delay(300);

  light_sensor.begin(a_gain, a_time);

  Serial.println("Ready for LoRa connection!");
  
  Serial2.begin(9600);

  Transceiver.init();
  Transceiver.SetChannel(TRANSCEIVER_CHANNEL);
  Transceiver.PrintParameters();

}



void loop() {

  if(millis() - start_time > DELAY_BETWEEN_SAMPLES_MS){
    
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
    Serial.println("Temperature: " + String(temp_c) + " degC");

    //Sample light sensor
    AsyncAPDS9306Data light_data = light_sensor.syncLuminosityMeasurement();
  
    //Calculate luminosity
    float lux = light_data.calculateLux();
    Serial.println("Luminosity: " + String(lux) + " Lux");


    //Format data as a JSON string
    String formatted_data = "{ \"" + group_name + "\": { \"" + device_name + "\": { \"Temp\": \"" 
        + String(temp_c) + "\", \"Luminosity\": \"" + String(lux) + "\" } } }" + '\n';
      
    Serial.println("Prepared LoRa message: " + formatted_data);
  
    Serial2.println(formatted_data);
    Serial.println("LoRa sent!");
    start_time = millis();
  }

}
