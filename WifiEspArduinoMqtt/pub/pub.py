import paho.mqtt.client as mqtt_client
import random
import time
import serial

broker = "broker.emqx.io"

client = mqtt_client.Client(f"lab_{random.randint(10000, 99999)}")
client.connect(broker)
ser = serial.Serial("/dev/ttyACM0", timeout=1)
print("Open connection")

num = ""
isBright = False
ledOn = False
maxBright = 0

while True:
  if ser.in_waiting > 0:
    try:
      data = ser.readline()
      prefix = data[0]
      num = int(''.join(filter(str.isdigit, str(data[1:]))))

      if (prefix == ord('b')):
        isBright = True
      elif (prefix == ord('d')):
        isBright = False

      if (isBright):
        if (maxBright < num):
          maxBright = num
        if (num > maxBright / 2):
          ledOn = True
        else:
          ledOn = False
      else:
        if (num > 20):
          ledOn = True
        else:
          ledOn = False

      if (ledOn):
        print("on")
        client.publish("lab/dungeon/cv9t", "on")
      else:
        print("off")
        client.publish("lab/dungeon/cv9t", "off")
    except ValueError:
      pass

client.disconnect()