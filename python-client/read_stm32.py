# import serial

# # Otwórz port szeregowy
# sen = serial.Serial('/dev/serial0', 115200, timeout=1)

# print('odbieranie danych')

# while True:
    # try:
        # # Odczytaj linię z portu szeregowego, zdekoduj i usuń niepotrzebne spacje
        # line = sen.readline().decode('utf-8', errors='ignore').strip()
        
        # if line:
            # print(line)
    # except KeyboardInterrupt:
        # print("przerwano odczyt.")
        # break

import serial
import json
import paho.mqtt.client as mqtt

# UART
ser = serial.Serial('/dev/serial0', 115200, timeout=1)

# MQTT
#mqttc = mqtt.Client("uart_bridge")
mqttc = mqtt.Client(
	client_id="uart_bridge",
	callback_api_version=mqtt.CallbackAPIVersion.VERSION1
)
mqttc.connect("localhost", 1883)
mqttc.loop_start()

print("UART → MQTT bridge uruchomiony")

while True:
    try:
        line = ser.readline().decode('utf-8', errors='ignore').strip()

        if line:
            data = json.loads(line)  # <- pasuje IDEALNIE

            mqttc.publish(
                topic="boiler/status",
                payload=json.dumps(data),
                qos=0,
                retain=True
            )

    except json.JSONDecodeError:
        print("Niepoprawny JSON:", line)

    except KeyboardInterrupt:
        break
        
