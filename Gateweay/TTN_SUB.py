import paho.mqtt.client as mqtt
import json
import time

hum  = 0
temp = 0
prsn = 0
eco2 = 0
tvoc = 0
pm10 = 0
pm2  = 0
o3   = 0

AQI = {'Humidity': 0,
       'Temperature': 0,
       'Pressure': 0,
       'eCO2': 0,
       'TVOC': 0,
       'PM10': 0,
       'PM2.5': 0,
       'Ozone': 0}

 
 
APPID  = 'TTN ID'
PSW    = 'TTN KEY'


def on_connect(mqttc, mosq, obj,rc):
    print("Conectado - Código de resultado: " + str(rc))
    client.subscribe('v3/+/devices/+/up')

# gives message from device
def on_message(mqttc,obj,msg):
    try: 
        
        x = json.loads(msg.payload.decode('utf-8')) 
        now = time.strftime('%Y-%m-%d %H-%M-%S')
        '''
        global hum, temp, prsn, eco2, tvoc, pm10, pm2, o3
        
        hum = x["uplink_message"]["decoded_payload"]["Humidity"]
        temp = x["uplink_message"]["decoded_payload"]["Temperature"]
        prsn = x["uplink_message"]["decoded_payload"]["Pressure"]
        eco2 = x["uplink_message"]["decoded_payload"]["eCO2"]
        tvoc = x["uplink_message"]["decoded_payload"]["TVOC"]
        pm10 = x["uplink_message"]["decoded_payload"]["PM10"]
        pm2 = x["uplink_message"]["decoded_payload"]["PM2_5"]
        o3 = x["uplink_message"]["decoded_payload"]["Ozone"]
        
        print(f"Humidiy: {hum} \nTemperature: {temp}\nPressure: {prsn}\neCO2: {eco2}\nTVOC: {tvoc}\nPM10: {pm10}\nPM2.5: {pm2} \nOzone: {o3}\n")
        '''
        global AQI
        AQI['Humidity'] = x["uplink_message"]["decoded_payload"]["Humidity"]
        AQI['Temperature'] = x["uplink_message"]["decoded_payload"]["Temperature"]
        AQI['Pressure'] = x["uplink_message"]["decoded_payload"]["Pressure"]
        AQI['eCO2'] = x["uplink_message"]["decoded_payload"]["eCO2"]
        AQI['TVOC'] = x["uplink_message"]["decoded_payload"]["TVOC"]
        AQI['PM10'] = x["uplink_message"]["decoded_payload"]["PM10"]
        AQI['PM2.5'] = x["uplink_message"]["decoded_payload"]["PM2_5"]
        AQI['Ozone'] = x["uplink_message"]["decoded_payload"]["Ozone"]
        print(now)
        print(AQI)
        
    except Exception as e:
        print(e)
        pass


client = mqtt.Client()
client.on_connect=on_connect
client.on_message = on_message
client.username_pw_set(APPID, PSW)
client.connect('nam1.cloud.thethings.network',1883)
client.loop_forever()
