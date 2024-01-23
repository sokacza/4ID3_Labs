import json
import serial

def main():

    ser = serial.Serial("COM7", 9600)
    while True:   
        serial_json_string=str(ser.readline())  #   Reading serial to newline character '\n'
        first_split_index = serial_json_string.find('{')    #   Start of message
        second_split_index = serial_json_string.rfind('}')  #   End of message
        serial_json_string = serial_json_string[first_split_index: second_split_index+1]
        try:
            data = json.loads(serial_json_string)  
            group_name = list(data.keys())[0]
            device_id = list(data[group_name].keys())[0]
            out = ""
            for key, val in data[group_name][device_id].items():
                out += f'<tr>\n<td>\n{key}\n</td>\n<td>\n{val}\n</td>\n </tr>'
            
             
            f = open("./index.html", "w")
            f.write(f"\n<html>\n<body>\n<table>\
                                \n<tr> \
                                \n<td>{group_name}</td> \
                                \n<td>{device_id}</td> \
                                \n</tr> \
                                    \n{out} \
                            \n</table> \
                        \n</body> \
                    \n</html>\n")  
            f.close()

        except Exception as e:
            print(f"Could not parse: {e}")


if __name__ == '__main__':
    main()




