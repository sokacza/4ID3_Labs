
#   Libraries
from http.server import HTTPServer, BaseHTTPRequestHandler
import time
import json
import pymongo
import paho.mqtt.client as mqtt


#   HTTP Server
HTTP_IP = '0.0.0.0'
HTTP_PORT = 3000

#   MQTT Connection
MQTT_IP = 'test.mosquitto.org'
MQTT_PORT = 1883
MQTT_ROUTE = '/'

#   Database Connection
MONGODB_IP = "mongodb://localhost"
MONGODB_PORT = 27017
MONGODB_ROUTE = '/'


#   Instantiating MQTT and callback functions
def on_connect(client, userdata, flags, rc):
    print(f"Connected to  {rc}")

def on_message(client, userdata, msg):
    print(f"{msg.topic} {msg.payload}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(MQTT_IP, MQTT_PORT, 60)
client.subscribe('Light', 2)

#   Instantiating database connection
mongodb_client = pymongo.MongoClient(f"{MONGODB_IP}:{MONGODB_PORT}{MONGODB_ROUTE}")

#   Handles when a device makes a POST or GET request to HTTP server
class requestHandler(BaseHTTPRequestHandler):
    
    def do_GET(self):        
        if self.path.endswith('/test'):
            self.send_response(200)
            self.send_header('content-type', "text/html")
            self.end_headers()       
            self.wfile.write(f'<html><body><h1>OK\n</h1></body></html>'.encode())


    def do_POST(self):
        if self.path.endswith('/database'):
            #Reading the data sent from microcontroller and formatting it
            content_length = int(self.headers['Content-Length'])
            data = self.rfile.read(content_length)
            self.send_response(200)
            self.end_headers()
            data = str(data)
            first_split_index = data.find('{')
            second_split_index = data.rfind('}')
            data = data[first_split_index: second_split_index+1]

            #Interpreting microcontroller data as JSON
            try:
                json_data = json.loads(data)
                group_name = list(json_data.keys())[0]
                device_id = list(json_data[group_name])[0]
                database = mongodb_client[group_name]
                collection = database[device_id]

                #Inserting into database
                ret = collection.insert_one(json_data[group_name][device_id])
                #Returning data + OK
                self.wfile.write(f'Data:{data}\nDatabase Response: {ret}\nOK\n'.encode())

            except:
                print(f"Could not parse: {data}\nDatabase Response{ret}")
                self.wfile.write(f"Could not process: {data}\nDatabase Response: {ret}\n".encode())            
            
            
        if self.path.endswith('/mqtt'):
            #Reading the data sent from microcontroller and formatting it
            content_length = int(self.headers['Content-Length'])
            data = str(self.rfile.read(content_length))
            self.send_response(200)
            self.end_headers()
            print(data)
            first_split_index = data.find('{')
            second_split_index = data.rfind('}')
            data = data[first_split_index: second_split_index+1]

            #Interpreting microcontroller data as JSON
            try:
                json_data = json.loads(data)
                group_name = list(json_data.keys())[0]
                device_id = list(json_data[group_name])[0]
            
                #Publishing to MQTT
                for key, val in json_data[group_name][device_id].items():
                    ret = client.publish(f'{group_name}/{device_id}/{key}', val.encode("UTF-8"))
                    print(f"{group_name}/{device_id}/{key} -> {val.encode('UTF-8')}, Response: {ret.is_published()}")

                #Returning data + OK
                self.wfile.write(f'{data}\n'.encode())
                self.wfile.write(b'OK')
        
            except:
                print("Could not parse: ", data)
                self.wfile.write(f"Could not process: {data}\nDatabase Response: {ret}\n".encode())
            


def main():
    #Tuple that stores the HTTP server data
    server_address = (HTTP_IP, HTTP_PORT)
    #Instantiate the server object
    server = HTTPServer(server_address, requestHandler)
    #Print useful data to the terminal
    print('\n\n---------------------\
        \nSimple HTTP IoT Server\n---\
        ------------------\n\n')
    print(f'HTTP server running on {HTTP_IP} port {HTTP_PORT}')
    time.sleep(1)
    print('Routes active: \n   -> \\mqtt \n   -> \\database')
    print(f"Connecting to MQTT -> {MQTT_IP}:{MQTT_PORT}")
    time.sleep(1)
    print(f"Connecting to Database -> {MONGODB_IP}:{MONGODB_PORT}{MONGODB_ROUTE}")
    time.sleep(1)
    print("\n\nServer Ready\n")
    #Serve the page until the thread exits
    server.serve_forever()

if __name__ == '__main__':
    main()