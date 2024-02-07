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
 //  Initializing IO port for MCP23017 IO expansion bus
  mcp.init();
  mcp.portMode(MCP23017Port::A, 0); // Configuring port A as OUTPUT
  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);  //Resetting port A 
}



void loop() {
  float lux = -1;
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
    lux = light_data.calculateLux();
    Serial.println("Luminosity: " + String(lux) + " Lux");


    //Format data as a JSON string
    String formatted_data = "{ \"" + group_name + "\": { \"" + device_name + "\": { \"Temp\": \"" 
        + String(temp_c) + "\", \"Luminosity\": \"" + String(lux) + "\" } } }" + '\n';
      
    Serial.println("Prepared LoRa message: " + formatted_data);
  
    Serial2.println(formatted_data);
    Serial.println("LoRa sent!");
    start_time = millis();
  }

  if(Serial2.available()){
    char character = Serial2.read();
    if(character == '0'){
      Serial.println("0");
            mcp.digitalWrite(0, 0);
    }
    else if(character == '1'){
      Serial.println("1");
            mcp.digitalWrite(0, 1);
    }
    else if(character == '2'){
      Serial.println("2");
            mcp.digitalWrite(2, 1);
    }
        else if(character == '3'){
      Serial.println("3");
            mcp.digitalWrite(2, 0);
    }
  }

  if(lux != -1 and lux > 200){
    mcp.digitalWrite(1, 1);
  }
  else if (lux != -1 and lux < 200){
    mcp.digitalWrite(1, 0);
  }

}
