#include "wifi_b.h"

void setup() {
  Serial.begin(115200);

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  dht.begin();
  bmp.begin();
  BH1750.begin(BH1750_TO_GROUND);  

  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }


  Serial.println("\n\nWiFi connected");
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());


  client.setServer(brokerAddress, addressPort);
  
}

void reconnect(){

    while(!client.connected()){
      Serial.println("\nAttempting MQTT connection");

      if(client.connect("ESP8266Client")){
         Serial.println("Connected to MQTT server");
         client.subscribe("testTopic");
      }
      else{
        Serial.println("Failed to connect to MQTT server, rc = ");
        Serial.print(client.state());
        delay(2000);
      }
    }
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

  if(!client.loop()){
    client.connect("ESP8266Client");
  } 

  bool ret = client.publish("4ID3_GroupA/temperature", String(dhtTempEvent.temperature).c_str());
  print(ret)
  delay(200);
  client.publish("4ID3_GroupA/humidity", String(dhtHumEvent.relative_humidity).c_str());
  delay(200);
  client.publish("4ID3_GroupA/pressure", String(bmpEvent.pressure).c_str());
  delay(200);
  client.publish("4ID3_GroupA/light_intensity", String(lux).c_str());
  delay(200);
  Serial.println("Published data to MQTT");
  
  delay(DELAY_BETWEEN_SAMPLES_MS);
  
}
