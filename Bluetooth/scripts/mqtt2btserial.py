#   Imported libraries
import serial
import json
import paho.mqtt.client as mqtt
import time


#   Configuring MQTT server and COM
mqtt_ip = None
mqtt_port = None
bluetooth_com_port = None
mqtt_topic = None

mqtt_ip = input("MQTT Broker IP: ")
if(mqtt_ip == None or mqtt_ip == ''): mqtt_ip = 'test.mosquitto.org'

mqtt_port = input("MQTT Broker Port: ")
if(mqtt_port == None or mqtt_port== ''): mqtt_port = 1883

bluetooth_com_port = input("Bluetooth COM (e.g. COM9): ")
if(bluetooth_com_port == None or bluetooth_com_port  == ''): bluetooth_com_port  = 'COM9'

mqtt_topic= input("MQTT Topic to Subscribe to: ")
if(mqtt_topic == None or mqtt_topic== ''): mqtt_topic = "GroupA/DeviceA/LED"

print(f'\n-------\nCONFIGURATION\n-------\nIP: {mqtt_ip}\nPORT: {mqtt_port}\nBT COM: {bluetooth_com_port}')

#   Connecting to serial
print("Connecting to serial: " + bluetooth_com_port)
time.sleep(1)
ser = serial.Serial(bluetooth_com_port, 9600)
print("Bluetooth COM opened")

#   MQTT callback functions
def on_connect(client, userdata, flags, rc):
    print(f"Connected, status = {str(rc)}")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    if msg.topic == mqtt_topic:
        print("Writing to serial...")
        ser.write(f"{str(msg.payload.decode())}\n".encode('utf-8'))
        print("Written.")

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_subscribe = on_subscribe






while True:
    #   Refreshing the client connection
    if(client.is_connected() == False):
        client.connect(mqtt_ip, mqtt_port, 60)
        client.subscribe(mqtt_topic, 0)
    client.loop()   
    

ser.close()
