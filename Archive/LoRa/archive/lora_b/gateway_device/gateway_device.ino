#include "gateway_device.h"

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Transceiver.init();
  Transceiver.SetChannel(TRANSCEIVER_CHANNEL);
  Transceiver.PrintParameters();
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  
 if (Serial2.available() > 1) {
    Serial.println("Receving Data...");
    String incomingData = Serial2.readString();
    Serial.println("PING: " + incomingData);

    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      http.begin(client, serverName);
      
      http.addHeader("Content-Type", "text/plain");        

      int httpResponseCode = http.POST(incomingData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();

    }

  }
}
