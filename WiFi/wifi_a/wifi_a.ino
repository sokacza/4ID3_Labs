#include "wifi_a.h"

void setup() {
  Serial.begin(115200);

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  dht.begin();

  bmp.begin();

  BH1750.begin(BH1750_TO_GROUND);  

}

void loop() {

  sensors_event_t dhtTempEvent, dhtHumEvent, bmpEvent;

  dht.temperature().getEvent(&dhtTempEvent);
  dht.humidity().getEvent(&dhtHumEvent);

  bmp.getEvent(&bmpEvent);
  
  BH1750.start();
  float lux = BH1750.getLux();

  Serial.println("\n-");

  //  TEMPERATURE (DHT11)
  if(!isnan(dhtTempEvent.temperature)){
    Serial.println("Temperature: " + String(dhtTempEvent.temperature) + " degC");
  }
  else{
    Serial.println("Temperature sensor disconnected");
  }

  //  HUMIDITY (DHT11)
  if(!isnan(dhtHumEvent.relative_humidity)){
    Serial.println("Humidity: " + String(dhtHumEvent.relative_humidity) + " %");
  }
  else{
    Serial.println("Humidity sensor disconnected");
  }

  //  PRESSURE (BMP180)
  if(!isnan(bmpEvent.pressure)){
    Serial.println("Pressure: " + String(bmpEvent.pressure) + " hPa");
  }
  else{
    Serial.println("Pressure sensor disconnected");
  }
  //  LIGHT INTENSITY (BH1750)
  if(!isnan(lux)){
    Serial.println("Light Intensity: " + String(lux) + " lux");
  }
  else{
    Serial.println("Light intensity sensor disconnected");
  }
  
  delay(DELAY_BETWEEN_SAMPLES_MS);
  

}
