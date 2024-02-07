#include "gateway_device.h"

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  Serial.println("connected");
  client.setServer(mqtt_server, 1883);//connecting to mqtt server

  Wire.begin();
  
  Serial2.begin(9600);
  Transceiver.init();
  Transceiver.SetChannel(TRANSCEIVER_CHANNEL);
  Transceiver.PrintParameters();  
  
  //  Initializing IO port for MCP23017 IO expansion bus
  mcp.init();
  mcp.portMode(MCP23017Port::A, 0); // Configuring port A as OUTPUT
  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);  //Resetting port A 

}

void callback(char* topic, byte* payload, unsigned int length) {   
  Serial.println("Callback called");
  
  String data_str = "";
  String topic_str = "";
  for(int i = 0; topic[i] != '\0'; i ++){
    topic_str += (char)topic[i];
  }
  for (unsigned int i = 0; i < length; i++)
  {
    data_str += (char)payload[i];
  }
  Serial.println("Data received:\n   Topic: " + topic_str + "\n   Data: " + data_str + "\n");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!client.connected())
  {
      Serial.println("Reconnecing to MQTT broker");
      client.connect(String(String(group_name) + "_" + String(device_name)).c_str());
        client.setCallback(callback);
      if(client.state() == MQTT_CONNECTED){
        Serial.println("Connected to MQTT broker");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        Serial.println("Wifi Signal Strength: " + String(WiFi.RSSI()) + " dB");
      }
      else{
        Serial.println("Failed to connect, rc = " + client.state());
      }
  }

  client.loop();

  if (Serial2.available() > 1) {
    Serial.println("Receving Data...");
    String incoming_data = Serial2.readString();
    StaticJsonDocument<sizeof(incoming_data) + 200> json_document;
    DeserializationError error = deserializeJson(json_document, incoming_data.c_str());
    const char* field_device_temp = json_document["GroupA"]["FieldDevice"]["Temp"];
    const char* field_device_lum = json_document["GroupA"]["FieldDevice"]["Luminosity"];
    client.publish(String("GroupA/FieldDevice/Temp").c_str(), field_device_temp);
    client.publish(String("GroupA/FieldDevice/Luminosity").c_str(), field_device_lum);
 }
}
